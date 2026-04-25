$ErrorActionPreference = 'Stop'

$repoRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$buildDir = Join-Path $repoRoot 'build'
$appName = 'OpeningTrainerVectorPiecesPrototype'

$releaseExe = Join-Path $buildDir "Release/$appName.exe"
$debugExe = Join-Path $buildDir "Debug/$appName.exe"
$plainExe = Join-Path $buildDir "$appName.exe"

if (-not (Test-Path $releaseExe) -and -not (Test-Path $debugExe) -and -not (Test-Path $plainExe)) {
    Write-Host '[run] Executable not found. Running build_app.ps1 first...'
    & (Join-Path $repoRoot 'build_app.ps1')
}

$exePath = $null
if (Test-Path $releaseExe) {
    $exePath = $releaseExe
} elseif (Test-Path $debugExe) {
    $exePath = $debugExe
} elseif (Test-Path $plainExe) {
    $exePath = $plainExe
}

if (-not $exePath) {
    Write-Error "[run] Could not locate $appName executable under build output."
}

Write-Host "[run] Launching: $exePath"
Start-Process -FilePath $exePath -WorkingDirectory (Split-Path -Parent $exePath)
Write-Host '[run] Launch command issued.'
