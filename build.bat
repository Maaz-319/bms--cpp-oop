@echo off
echo Compiling Bank Management System...
if exist build/bms.exe del build/bms.exe
g++ -std=c++17 -I./include src/main.cpp src/Utility/UI/Utility_UI.cpp -o build/bms.exe
if %errorlevel% equ 0 (
    echo Build successful! Run bms.exe to start the program.
) else (
    echo Build failed!
)