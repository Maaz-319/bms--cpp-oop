#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

class Utility {
public:
    static void print_line(int);
    static void print_dashed_line(int);
    static void print_header(const string& title);
    static void print_menu_box(const string& title, const vector<string>& options);
    static void print_success_message(const string& message);
    static void print_error_message(const string& message);
    static void print_info_box(const string& message);
    static void set_console_color(int color);
    static void reset_console_color();
    static int take_integer_input(int min, int max, string prompt);
    static string take_phone_input();
    static string take_string_input(string prompt);
    Utility() = delete;

    enum Colors {
        BLACK = 0,
        DARK_BLUE = 1,
        DARK_GREEN = 2,
        DARK_CYAN = 3,
        DARK_RED = 4,
        DARK_MAGENTA = 5,
        DARK_YELLOW = 6,
        LIGHT_GRAY = 7,
        DARK_GRAY = 8,
        BLUE = 9,
        GREEN = 10,
        CYAN = 11,
        RED = 12,
        MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15
    };
};

#endif
