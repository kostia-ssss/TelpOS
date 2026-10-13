$ErrorActionPreference = "Stop"

$ProjectRoot = $PSScriptRoot
$Bash = "C:\msys64\usr\bin\bash.exe"
$QEMU = "C:\msys64\ucrt64\bin\qemu-system-x86_64.exe"

if (-not (Test-Path $Bash)) {
    throw "Не знайдено Bash: $Bash"
}

if (-not (Test-Path $QEMU)) {
    throw "Не знайдено QEMU: $QEMU"
}

# Convert the Windows project path to an MSYS2 path.
$MsysProject = $ProjectRoot -replace '^C:', '/c' -replace '\\', '/'

Write-Host "`n=== 1/3: Building TelpOS kernel ===" -ForegroundColor Cyan

$BuildCommand = "export PATH=""/c/msys64/ucrt64/bin:`$PATH""; cd '$MsysProject' && make -f GNUmakefile TOOLCHAIN=llvm"

& $Bash -lc $BuildCommand

if ($LASTEXITCODE -ne 0) {
    throw "Збірка ядра не вдалася. QEMU не запускатиметься."
}

if (-not (Test-Path (Join-Path $ProjectRoot "bin/myos"))) {
    throw "Файл ядра bin/myos не знайдено."
}

Write-Host "`n=== 2/3: Building bootable ISO ===" -ForegroundColor Cyan

& $Bash -lc "cd '$MsysProject' && bash ./build.sh"

if ($LASTEXITCODE -ne 0) {
    throw "Створення ISO не вдалося. QEMU не запускатиметься."
}

$ISO = Join-Path $ProjectRoot "image.iso"

if (-not (Test-Path $ISO)) {
    throw "Файл image.iso не знайдено."
}

Write-Host "`n=== 3/3: Launching TelpOS in QEMU ===" -ForegroundColor Green

& $QEMU -cdrom $ISO -m 512 -boot d