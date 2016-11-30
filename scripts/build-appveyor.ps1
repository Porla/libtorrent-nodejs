param(
    [string]$NodeVersion,
    [ValidateSet("x64", "x86")]
    [string]$Platform = "x64"
)

$ErrorActionPreference = "Stop"
. $(Join-Path $PSScriptRoot functions.ps1)

# Set up correct Node.js version on AppVeyor
if (Is-AppVeyor) {
    Write-BuildMessage "Installing correct version of Node.js"
    Install-Product node $NodeVersion $Platform

    Write-BuildMessage "Updating npm"
    & npm install -g npm

    Write-BuildMessage "Touching undefined file to avoid a strange bug"
    echo $null >> $(Join-Path $PSScriptRoot "../undefined")
}

$WhichNode = (cmd /c where node) | Out-String
$WhichNpm  = (cmd /c where npm)  | Out-String
$NodeV     = (cmd /c node -v)    | Out-String
$NodeInfo  = (cmd /c node -e "console.log('arch:',process.arch,',argv:',process.argv,'execPath:',process.execPath)") | Out-String

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

Format-Table -Wrap -InputObject @{ 
    Node        = $WhichNode.Trim()
    NodeInfo    = $NodeInfo.Trim()
    NodeVersion = $NodeV.Trim()
    Npm         = $WhichNpm.Trim()
}

Write-BuildMessage "Running npm install"
& npm install --build-from-source

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

Write-BuildMessage "Running tests"
& npm test

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

Write-BuildMessage "Packaging"
& .\node_modules\.bin\node-pre-gyp package

if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

if (Is-AppVeyor) {
    $commit = $env:APPVEYOR_REPO_COMMIT_MESSAGE

    if ($commit -ne "" -and $commit -ne $null -and $commit.StartsWith(":shipit:")) {
        Write-BuildMessage "Shipping binaries!"
        & .\node_modules\.bin\node-pre-gyp publish

        if ($LASTEXITCODE -ne 0) {
            exit $LASTEXITCODE
        }
    }
}
