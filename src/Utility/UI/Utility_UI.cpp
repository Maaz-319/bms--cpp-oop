#include "../../../include/Utility/UI/Utility_UI.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif
#include <algorithm>

using namespace std;

void Utility_UI::set_console_color(int color)
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    switch(color) {
        case 0: cout << "\033[30m"; break;  // Black
        case 1: cout << "\033[34m"; break;  // Dark Blue
        case 2: cout << "\033[32m"; break;  // Dark Green
        case 3: cout << "\033[36m"; break;  // Dark Cyan
        case 4: cout << "\033[31m"; break;  // Dark Red
        case 5: cout << "\033[35m"; break;  // Dark Magenta
        case 6: cout << "\033[33m"; break;  // Dark Yellow
        case 7: cout << "\033[37m"; break;  // Light Gray
        case 8: cout << "\033[90m"; break;  // Dark Gray
        case 9: cout << "\033[94m"; break;  // Blue
        case 10: cout << "\033[92m"; break; // Green
        case 11: cout << "\033[96m"; break; // Cyan
        case 12: cout << "\033[91m"; break; // Red
        case 13: cout << "\033[95m"; break; // Magenta
        case 14: cout << "\033[93m"; break; // Yellow
        case 15: cout << "\033[97m"; break; // White
        default: cout << "\033[37m"; break; // white
    }
#endif
}

void Utility_UI::reset_console_color()
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
#else
    cout << "\033[0m";
#endif
}

void Utility_UI::print_line(int length = 50)
{
    for (int i = 0; i < length; i++)
    {
        cout << "=";
    }
    cout << endl;
}

void Utility_UI::print_dashed_line(int length = 50)
{
    for (int i = 0; i < length; i++)
    {
        cout << "-";
    }
    cout << endl;
}

void Utility_UI::print_header(const string &title)
{
    system("cls");
    print_line(60);
    cout << "| " << setw(56) << left << title << " |" << endl;
    print_line(60);
    cout << endl;
}

void Utility_UI::print_menu_box(const string &title, const vector<string> &options)
{
    system("cls");

    // Top border
    cout << "+";
    for (int i = 0; i < 58; i++)
        cout << "-";
    cout << "+" << endl;

    // Title
    cout << "|" << setw(30 - title.length() / 2) << "" << title;
    cout << setw(30 - title.length() / 2 - (title.length() % 2) - 2) << "" << "|" << endl;

    // Separator
    cout << "+";
    for (int i = 0; i < 58; i++)
        cout << "-";
    cout << "+" << endl;

    // Options
    for (size_t i = 0; i < options.size(); i++)
    {
        cout << "| [" << (i + 1) << "] " << setw(51) << left << options[i] << "  |" << endl;
    }

    // Bottom border
    cout << "+";
    for (int i = 0; i < 58; i++)
        cout << "-";
    cout << "+" << endl;

    cout << endl;
}

void Utility_UI::print_success_message(const string &message)
{
    cout << endl;
    Utility_UI::set_console_color(Utility_UI::Colors::GREEN);
    print_dashed_line(40);
    cout << "SUCCESS: " << message << endl;
    print_dashed_line(40);
    Utility_UI::reset_console_color();
}

void Utility_UI::print_error_message(const string &message)
{
    cout << endl;
    Utility_UI::set_console_color(Utility_UI::Colors::RED);
    print_dashed_line(40);
    cout << "ERROR: " << message << endl;
    print_dashed_line(40);
    Utility_UI::reset_console_color();
}

void Utility_UI::print_info_box(const string &message)
{
    cout << endl;
    cout << "+";
    for (int i = 0; i < message.length() + 6; i++)
        cout << "-";
    cout << "+" << endl;
    cout << "|   " << message << "   |" << endl;
    cout << "+";
    for (int i = 0; i < message.length() + 6; i++)
        cout << "-";
    cout << "+" << endl;
}

int Utility_UI::take_integer_input(int min, int max, string prompt)
{
    int variable;
    bool valid = false;
    
    while (!valid)
    {
        cout << "Enter " << prompt << " (" << min << " - " << max << "): ";
        if (!(cin >> variable))
        {
            Utility_UI::print_error_message("Invalid input. Please enter a number.");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        }
        else if (variable < min || variable > max)
        {
            Utility_UI::print_error_message("Input out of range.\nPlease enter a number between " + to_string(min) + " and " + to_string(max) + ".");
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining input
        }
        else
        {
            valid = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining input
        }
    }
    return variable;
}

string Utility_UI::take_phone_input()
{
    string variable;
    bool valid = false;

    while (!valid)
    {
        cout << "Enter 11 digit phone number (03XXXXXXXXX): ";
        cin >> variable;

        // Check if the input is a valid phone number (11 digits, starts with 03)
        if (variable.length() != 11 || variable.substr(0, 2) != "03" || !all_of(variable.begin(), variable.end(), ::isdigit))
        {
            Utility_UI::print_error_message("Invalid phone number.\nPlease enter an 11-digit number starting with 03.");
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining input
        }
        else
        {
            valid = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return variable;
}

string Utility_UI::take_string_input(string prompt)
{
    string variable;
    
    while (true)
    {
        cout << "Enter " << prompt << ": ";
        
        if (cin.peek() == '\n') {
            cin.ignore();
        }
        
        getline(cin, variable);

        // Remove leading and trailing whitespace
        variable.erase(variable.begin(), find_if(variable.begin(), variable.end(), [](unsigned char ch) { return !isspace(ch); }));
        variable.erase(find_if(variable.rbegin(), variable.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), variable.end());

        if (!variable.empty())
        {
            return variable;
        }
        
        Utility_UI::print_error_message("Input cannot be empty. Please try again.");
    }
}