#include "../include/Utility/UI/Utility_UI.h"
#include "../include/Person/Person.h"
#include "../include/Person/Account_Holder.h"
#include "../include/Account/Account.h"
#include "../include/Account/Current_Account.h"

#include <iostream>
#include <vector>
#include <conio.h>
#include <string>

class Bank
{
private:
    void create_new_account()
    {
        Account *account = nullptr;
        std::vector<std::string> types_of_accounts = {"Current Account"};
        AccountHolder account_holder;

        Utility_UI::print_header("Account Creation");

        account_holder.get_common_inputs();
        account_holder.get_specific_inputs();

        int acc_type_choice = Utility_UI::print_menu_box("Account Type", types_of_accounts);
        if (acc_type_choice == 1)
        {
            account = new Current_Account();
        }

        account->get_common_inputs(&account_holder);
        account->get_specific_inputs();

        system("cls");
        account_holder.display_info();
        getch();
        account->display_info();
        getch();
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
            create_new_account();
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