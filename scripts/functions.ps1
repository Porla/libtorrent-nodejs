function Is-AppVeyor {
    return Test-Path Env:\APPVEYOR
}

function Is-AppVeyorVersionTag {
    if (Test-Path Env:\APPVEYOR_REPO_TAG_NAME) {
        $tag = $env:APPVEYOR_REPO_TAG_NAME

        if ($tag -eq "" -or $tag -eq $null) {
            return $false
        }

        return $tag.StartsWith("v")
    }
}

function Write-BuildMessage {
    param([string]$message)

    Write-Output $message        

    if (Is-AppVeyor) {
        Add-AppveyorMessage -Message $message
    }
}
