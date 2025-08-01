@echo off
setlocal EnableDelayedExpansion

echo Bank Management System Build Script
echo ==================================
echo.

:: Ensure build directory exists
if not exist build mkdir build

:menu
echo Select an option:
echo 1. Compile only SQLite (include/Utility/dbmanager/sqlite3.c to sqlite3.o)
echo 2. Compile only BMS (src/*.cpp to build/bms.exe)
echo 3. Compile both SQLite and BMS
echo 4. Exit
set /p choice="Enter choice (1-4): "

if "%choice%"=="1" goto compile_sqlite
if "%choice%"=="2" goto compile_bms
if "%choice%"=="3" goto compile_both
if "%choice%"=="4" goto end
echo Invalid choice! Please select 1, 2, 3, or 4.
pause
goto menu

:compile_sqlite
echo Compiling SQLite...
gcc -c include\Utility\dbmanager\sqlite3.c -o include\Utility\dbmanager\sqlite3.o -I.\include
if %errorlevel% equ 0 (
    echo SQLite compiled successfully! sqlite3.o created.
) else (
    echo SQLite compilation failed!
    pause
    goto menu
)
pause
goto menu

:compile_bms
echo Compiling Bank Management System...
if not exist include\Utility\dbmanager\sqlite3.o (
    echo Error: sqlite3.o not found! Please compile SQLite first ^(option 1^).
    pause
    goto menu
)
if exist build\bms.exe del build\bms.exe
g++ -std=c++17 -I.\include src\main.cpp src\Utility\UI\Utility_UI.cpp src\Person\Person.cpp src\Person\Account_Holder.cpp src\Account\Account.cpp src\Account\Current_Account.cpp src\Transaction\Transaction.cpp include\Utility\dbmanager\sqlite3.o -o build\bms.exe
if %errorlevel% equ 0 (
    echo Build successful! Run build\bms.exe to start the program.
) else (
    echo BMS build failed!
)
pause
goto menu

:compile_both
echo Compiling SQLite and Bank Management System...
echo Compiling SQLite...
gcc -c include\Utility\dbmanager\sqlite3.c -o include\Utility\dbmanager\sqlite3.o -I.\include
if %errorlevel% neq 0 (
    echo SQLite compilation failed!
    pause
    goto menu
)
echo SQLite compiled successfully! sqlite3.o created.
echo Compiling BMS...
if exist build\bms.exe del build\bms.exe
g++ -std=c++17 -I.\include src\main.cpp src\Utility\UI\Utility_UI.cpp src\Person\Person.cpp src\Person\Account_Holder.cpp src\Account\Account.cpp src\Account\Current_Account.cpp src\Transaction\Transaction.cpp include\Utility\dbmanager\sqlite3.o -o build\bms.exe
if %errorlevel% equ 0 (
    echo Build successful! Run build\bms.exe to start the program.
) else (
    echo BMS build failed!
)
pause
goto menu

:end
echo Exiting build script.
endlocal