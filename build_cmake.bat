@echo off
echo [INFO] checking for cmake...
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] 'cmake' not found.
    echo Please run this script from the 'Developer Command Prompt for Visual Studio'.
    echo Search for "Developer Command Prompt" in your Windows Start Menu.
    pause
    exit /b 1
)

if not exist build mkdir build
cd build

echo [INFO] Generating project files...
cmake ..
if %errorlevel% neq 0 (
    echo [ERROR] CMake generation failed.
    pause
    exit /b 1
)

echo [INFO] Building project...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo [ERROR] Build failed.
    pause
    exit /b 1
)

echo [SUCCESS] Build completed successfully.
echo You can run the game: bin\Release\roguelike.exe
pause
