function Is-AppVeyor {
    return Test-Path Env:\APPVEYOR
}

function Write-BuildMessage {
    param([string]$message)

    Write-Output $message        

    if (Is-AppVeyor) {
        Add-AppveyorMessage -Message $message
    }
}
