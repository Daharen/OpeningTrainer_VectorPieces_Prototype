$repoRoot = Split-Path -Parent $MyInvocation.MyCommand.Path

Write-Host '=== OpeningTrainer Vector Pieces Prototype Diagnostic ==='
Write-Host "Repo path: $repoRoot"
Write-Host "PowerShell version: $($PSVersionTable.PSVersion)"

$gitCmd = Get-Command git -ErrorAction SilentlyContinue
if ($gitCmd) {
    Write-Host "Git version: $(git --version)"
} else {
    Write-Host 'Git version: not found'
}

$cmakeCmd = Get-Command cmake -ErrorAction SilentlyContinue
if ($cmakeCmd) {
    Write-Host "CMake version: $(cmake --version | Select-Object -First 1)"
} else {
    Write-Host 'CMake version: not found'
}

Write-Host '--- Qt-related environment variables ---'
$qtVars = Get-ChildItem Env: | Where-Object {
    $_.Name -match 'QT|QTDIR|CMAKE_PREFIX_PATH|Qt6_DIR'
}
if ($qtVars) {
    $qtVars | ForEach-Object { Write-Host ("{0}={1}" -f $_.Name, $_.Value) }
} else {
    Write-Host 'No Qt-related environment variables detected.'
}

Write-Host '--- Directory tree summary (depth <= 3) ---'
Get-ChildItem -Path $repoRoot -Depth 3 | ForEach-Object {
    $relative = $_.FullName.Replace($repoRoot, '.').TrimStart('\\')
    if ($relative) { Write-Host $relative }
}

Write-Host '--- Key file checks ---'
$keyFiles = @(
    'README.md',
    'CMakeLists.txt',
    'build_app.ps1',
    'run.ps1',
    'diagnostic.ps1',
    'src/main.cpp',
    'src/PieceRenderer.cpp',
    'src/PiecePixmapCache.cpp',
    'src/PreviewWindow.cpp',
    'docs/architecture.md',
    'docs/piece_language.md'
)

foreach ($file in $keyFiles) {
    $exists = Test-Path (Join-Path $repoRoot $file)
    Write-Host ("{0}: {1}" -f $file, $(if ($exists) { 'FOUND' } else { 'MISSING' }))
}

Write-Host '--- Build output checks ---'
$buildDir = Join-Path $repoRoot 'build'
if (Test-Path $buildDir) {
    Write-Host 'build/: FOUND'
    $executables = Get-ChildItem -Path $buildDir -Filter '*.exe' -Recurse -ErrorAction SilentlyContinue
    if ($executables) {
        Write-Host 'Executables found:'
        $executables | ForEach-Object { Write-Host " - $($_.FullName)" }
    } else {
        Write-Host 'No executable found under build/ yet.'
    }
} else {
    Write-Host 'build/: NOT FOUND'
}

Write-Host '=== End Diagnostic ==='
