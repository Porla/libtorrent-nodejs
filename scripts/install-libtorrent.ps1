param(
    [ValidateSet("x86", "x64")]
    [string]$Platform = "x64"
)

$ErrorActionPreference = "Stop"
. $(Join-Path $PSScriptRoot functions.ps1)

$AddressModel = 64
$BoostPath = $env:BOOST_ROOT
$Commitish = Get-Content (Join-Path $PSScriptRoot '../libtorrent-commitish')
$OpenSSLPath = $env:OPENSSL_ROOT
$Prefix = "C:\Libraries\Rasterbar-libtorrent\msvc-14.0\$Platform"

if ($Platform -eq "x86") {
    $AddressModel = 32
}

if ($BoostPath -eq "" -or $BoostPath -eq $null) {
    $BoostPath = "C:\Libraries\boost_1_62_0"
}

if ($OpenSSLPath -eq "" -or $OpenSSLPath -eq $null) {
    $OpenSSLPath = "C:\OpenSSL-Win$AddressModel"
}

$b2 = Join-Path $BoostPath 'b2.exe'

Format-Table -InputObject @{ 
    AddressModel = $AddressModel
    b2           = $b2
    BoostPath    = $BoostPath
    Commitish    = $Commitish
    OpenSSLPath  = $OpenSSLPath
    Platform     = $Platform
    Prefix       = $Prefix
}

if (Test-Path $Prefix) {
    Write-BuildMessage "It seems as if Rasterbar-libtorrent is already built. Awesome. Exiting..."
    exit
}

if (!(Test-Path $b2)) {
    Write-BuildMessage "$b2 does not exist. Bootstrapping Boost."
    Push-Location $BoostPath
    cmd /c bootstrap.bat
    Pop-Location
} else {
    Write-BuildMessage "$b2 already exists. Great!"
}

$gitPath = "C:\projects\arvidn-libtorrent"

Start-Process "git" -NoNewWindow -Wait -ArgumentList @(
    "clone",
    "https://github.com/arvidn/libtorrent",
    $gitPath
)

Start-Process "git" -NoNewWindow -Wait -WorkingDirectory $gitPath -ArgumentList @(
    "checkout",
    $Commitish
)

Start-Process $b2 -NoNewWindow -Wait -WorkingDirectory $gitPath -ArgumentList @(
    "install",
    "--prefix=""$Prefix""",
    "toolset=msvc-14.0",
    "address-model=$AddressModel",
    "deprecated-functions=off",
    "ssl=openssl",
    "crypto=libcrypto",
    "link=static",
    "boost-link=static",
    "runtime-link=static",
    "variant=release",
    "-sBOOST_ROOT=$BoostPath",
    "include=""$(Join-Path $OpenSSLPath "include")"""
)

Write-BuildMessage "Rasterbar-libtorrent built!"
