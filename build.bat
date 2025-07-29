@echo off
echo Compiling Bank Management System...
if exist build\bms.exe del build\bms.exe
g++ -std=c++17 -I./include src/main.cpp src/Utility/UI/Utility_UI.cpp src/Person/Person.cpp src/Person/Account_Holder.cpp src/Account/Account.cpp src/Account/Current_Account.cpp src/Bank/Bank.cpp -o build/bms.exe
if %errorlevel% equ 0 (
    echo Build successful! Run build/bms.exe to start the program.
) else (
    echo Build failed!
)