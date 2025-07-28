#include "../include/Utility/UI/Utility_UI.h"
#include <iostream>
#include <vector>
#include <conio.h>

class Bank
{
private:
    void create_account()
    {
        Utility_UI::print_header("Account Creation");
    }
    void exit_bank()
    {
        Utility_UI::print_success_message("Thank You for Using Bank Mangement System");
        Utility_UI::print_info_box("Author: Maaz Bin Asif");
        Utility_UI::print_info_box("Linkedin -> @maazbinasif");
        Utility_UI::print_info_box("Instagram -> @maaz.binasif");
        getch();
        return;
    }
    void main_menu()
    {
        int choice{0};
        choice = Utility_UI::print_menu_box("Bank Mangement System", std::vector<string>{"Login", "Create Account", "Exit"});
        if (choice == 3)
        {
            exit_bank();
        }
        else if (choice == 2)
        {
            create_account();
        }
    }

public:
    void run()
    {
        main_menu();
    }
};

int main()
{
    Bank Bank;
    Bank.run();
    return 0;
}