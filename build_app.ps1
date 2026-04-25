$ErrorActionPreference = 'Stop'

$repoRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$buildDir = Join-Path $repoRoot 'build'

Write-Host "[build] Repo root: $repoRoot"

if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Write-Error '[build] CMake is not available in PATH.'
}

if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Path $buildDir | Out-Null
    Write-Host "[build] Created build directory: $buildDir"
}

Write-Host '[build] Configuring CMake...'
cmake -S $repoRoot -B $buildDir
if ($LASTEXITCODE -ne 0) {
    Write-Error '[build] CMake configure failed. Check Qt6 installation and CMAKE_PREFIX_PATH.'
}

Write-Host '[build] Building project...'
cmake --build $buildDir --config Release
if ($LASTEXITCODE -ne 0) {
    Write-Error '[build] CMake build failed.'
}

Write-Host '[build] Success: OpeningTrainerVectorPiecesPrototype built.'
