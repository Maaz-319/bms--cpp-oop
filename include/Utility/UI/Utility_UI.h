#pragma once

#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <limits>

class Utility_UI
{
public:
    static void print_line(int length = 50);
    static void print_dashed_line(int length = 50);
    static void print_header(const std::string& header, int width = 60);
    static int print_menu_box(const std::string &title, const std::vector<std::string> &options);
    static void print_success_message(const std::string &message);
    static void print_error_message(const std::string &message);
    static void print_info_box(const std::string &message);
    static void set_console_color(int color);
    static void reset_console_color();
    static int take_integer_input(int min, int max, const std::string &prompt);
    // static std::string take_phone_input();
    static std::string take_phone_input(const std::string &prompt = "Phone No");
    static std::string take_string_input(const std::string &prompt, int limit = 100);
    static std::string take_email_input(const std::string &prompt = "Email");
    static std::string take_pin_input(const std::string &prompt = "PIN", int length = 4);
    static std::string generate_4_digit_random_number();
    static double take_balance_input(const std::string &prompt="Amount", double min = 1.0, double max = 1e6);
    Utility_UI() = delete;

    enum Colors
    {
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