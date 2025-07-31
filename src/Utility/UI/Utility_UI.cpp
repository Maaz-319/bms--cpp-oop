#include "../../../include/Utility/UI/Utility_UI.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <regex>
#include <string>
#include <random>
#include <limits>
#include <maaz_utills.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <algorithm>

const int delay_ms = 1;

using namespace std;

void Utility_UI::set_console_color(int color)
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    switch (color)
    {
    case 0:
        cout << "\033[30m";
        break; // Black
    case 1:
        cout << "\033[34m";
        break; // Dark Blue
    case 2:
        cout << "\033[32m";
        break; // Dark Green
    case 3:
        cout << "\033[36m";
        break; // Dark Cyan
    case 4:
        cout << "\033[31m";
        break; // Dark Red
    case 5:
        cout << "\033[35m";
        break; // Dark Magenta
    case 6:
        cout << "\033[33m";
        break; // Dark Yellow
    case 7:
        cout << "\033[37m";
        break; // Light Gray
    case 8:
        cout << "\033[90m";
        break; // Dark Gray
    case 9:
        cout << "\033[94m";
        break; // Blue
    case 10:
        cout << "\033[92m";
        break; // Green
    case 11:
        cout << "\033[96m";
        break; // Cyan
    case 12:
        cout << "\033[91m";
        break; // Red
    case 13:
        cout << "\033[95m";
        break; // Magenta
    case 14:
        cout << "\033[93m";
        break; // Yellow
    case 15:
        cout << "\033[97m";
        break; // White
    default:
        cout << "\033[37m";
        break; // white
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

void Utility_UI::print_line(int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << "=";
    }
    cout << endl;
}

void Utility_UI::print_dashed_line(int length)
{
    for (int i = 0; i < length; i++)
    {
        cout << "-";
    }
    cout << endl;
}

// void Utility_UI::print_header(const std::string &title)
// {
//     system("cls");
//     print_line(60);
//     cout << "| " << setw(56) << left << title << " |" << endl;
//     print_line(60);
//     cout << endl;
// }

void Utility_UI::print_header(const std::string &header, int width)
{
    Utility_UI::print_dashed_line(width);
    int space = width / 2 - header.length() / 2;
    cout << "|" << std::string(space, ' ') << header
         << std::string(width - space - header.length() - 2, ' ') << "|\n";
    Utility_UI::print_dashed_line(width);
}

int Utility_UI::print_menu_box(const std::string &title, const std::vector<std::string> &options)
{

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

    return Utility_UI::take_integer_input(1, options.size(), "choice");
}

void Utility_UI::print_success_message(const std::string &message)
{
    string word_to_print = "SUCCESS";
    cout << endl;
    int len = message.length() + word_to_print.length() + 3;
    Utility_UI::set_console_color(Utility_UI::Colors::GREEN);
    print_dashed_line(len);
    Maaz::print_slowly(word_to_print + ": " + message + "\n", delay_ms);
    print_dashed_line(len);
    Utility_UI::reset_console_color();
}

void Utility_UI::print_error_message(const std::string &message)
{
    string word_to_print = "Error";
    cout << endl;
    int len = message.length() + word_to_print.length() + 3;
    Utility_UI::set_console_color(Utility_UI::Colors::RED);
    print_dashed_line(len);
    Maaz::print_slowly(word_to_print + ": " + message + "\n", delay_ms);
    print_dashed_line(len);
    Utility_UI::reset_console_color();
}

void Utility_UI::print_info_box(const std::string &message)
{
    cout << endl;
    cout << "+";
    for (int i = 0; i < message.length() + 6; i++)
        cout << "-";
    cout << "+" << endl;
    Maaz::print_slowly("|   " + message + "   |\n");
    cout << "+";
    for (int i = 0; i < message.length() + 6; i++)
        cout << "-";
    cout << "+" << endl;
}

int Utility_UI::take_integer_input(int min, int max, const std::string &prompt)
{
    int variable;
    bool valid = false;

    while (!valid)
    {
        Maaz::print_slowly("Enter " + prompt + " (" + to_string(min) + " - " + to_string(max) + "): ");
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

// std::string Utility_UI::take_phone_input()
// {
//     std::string variable;
//     bool valid = false;

//     while (!valid)
//     {
//         cout << "Enter 11 digit phone number (03XXXXXXXXX): ";
//         cin >> variable;

//         // Check if the input is a valid phone number (11 digits, starts with 03)
//         if (variable.length() != 11 || variable.substr(0, 2) != "03" || !all_of(variable.begin(), variable.end(), ::isdigit))
//         {
//             Utility_UI::print_error_message("Invalid phone number.\nPlease enter an 11-digit number starting with 03.");
//             cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining input
//         }
//         else
//         {
//             valid = true;
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//         }
//     }
//     return variable;
// }

// string Utility_UI::take_string_input(string prompt)
// {
//     string variable;

//     while (true)
//     {
//         cout << "Enter " << prompt << ": ";

//         if (cin.peek() == '\n')
//         {
//             cin.ignore();
//         }

//         getline(cin, variable);

//         // Remove leading and trailing whitespace
//         variable.erase(variable.begin(), find_if(variable.begin(), variable.end(), [](unsigned char ch)
//                                                  { return !isspace(ch); }));
//         variable.erase(find_if(variable.rbegin(), variable.rend(), [](unsigned char ch)
//                                { return !isspace(ch); })
//                            .base(),
//                        variable.end());

//         if (!variable.empty())
//         {
//             return variable;
//         }

//         Utility_UI::print_error_message("Input cannot be empty. Please try again.");
//     }
// }

std::string Utility_UI::take_string_input(const std::string &prompt, int limit)
{
    std::string input;
    while (true)
    {
        Maaz::print_slowly("Enter " + prompt + ": ");
        std::getline(std::cin, input);

        if (!std::regex_match(input, std::regex("^[A-Za-z ]+$")))
        {
            Utility_UI::print_error_message("Only letters (A-Z, a-z) are allowed in " + prompt);
            continue;
        }
        if (input.length() < 3)
        {
            Utility_UI::print_error_message("Min Length for " + prompt + " is 3");
            continue;
        }
        if (input.length() > static_cast<size_t>(limit))
        {
            Utility_UI::print_error_message("Max Length for " + prompt + " is " + to_string(limit));
            continue;
        }
        break;
    }
    return input;
}

std::string Utility_UI::take_email_input(const std::string &prompt)
{
    std::string input;
    std::regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    while (true)
    {
        Maaz::print_slowly("Enter " + prompt + ": ");
        std::getline(std::cin, input);
        if (!std::regex_match(input, pattern))
        {
            Utility_UI::print_error_message("Invalid " + prompt + " format");
        }
        else
        {
            break;
        }
    }
    return input;
}

std::string Utility_UI::take_phone_input(const std::string &prompt)
{
    std::string input;
    std::regex pattern("^03\\d{9}$");
    while (true)
    {
        Maaz::print_slowly("Enter " + prompt + ": ");
        std::getline(std::cin, input);
        if (!std::regex_match(input, pattern))
        {
            Utility_UI::print_error_message("Invalid " + prompt + " Number");
        }
        else
        {
            break;
        }
    }
    return input;
}

std::string Utility_UI::take_pin_input(const std::string &prompt, int length)
{
    std::string input;
    std::regex pattern("^\\d{4}$");
    while (true)
    {
        Maaz::print_slowly("Enter " + prompt + " (" + to_string(length) + "-digit): ");
        std::getline(std::cin, input);
        if (!std::regex_match(input, pattern))
        {
            Utility_UI::print_error_message("Invalid " + prompt + ". Please try again");
        }
        else
        {
            break;
        }
    }
    return input;
}

std::string Utility_UI::generate_4_digit_random_number()
{
    static std::mt19937 rng(std::random_device{}());     // initialized once
    std::uniform_int_distribution<int> dist(1000, 9999); // 4-digit range
    return std::to_string(dist(rng));
}

double Utility_UI::take_balance_input(const std::string &prompt, double min, double max)
{
    double amount;
    while (true)
    {
        Maaz::print_slowly("Enter " + prompt + " (" + to_string(min) + " - " + to_string(max) + "): ");
        std::cin >> amount;

        // Input failure (non-numeric input)
        if (std::cin.fail())
        {
            std::cin.clear();                                                   // clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            Utility_UI::print_error_message("Please enter a valid number");
            continue;
        }

        // Range check
        if (amount < min || amount > max)
        {
            Utility_UI::print_error_message(prompt + " must be between " + to_string(min) + " and " + to_string(max));
            continue;
        }

        // Successful input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush rest of line
        break;
    }

    return amount;
}

std::string Utility_UI::get_formatted_date()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    std::tm *local_tm = std::localtime(&time_now);

    std::stringstream ss;
    ss << std::put_time(local_tm, "%d %B, %Y"); // e.g., 29 July, 2025
    return ss.str();
}

std::string Utility_UI::get_formatted_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    std::tm *local_tm = std::localtime(&time_now);

    std::stringstream ss;
    ss << std::put_time(local_tm, "%I:%M %p"); // e.g., 07:45 PM
    return ss.str();
}
