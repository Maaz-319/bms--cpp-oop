#include "../include/Utility/UI/Utility_UI.h"
#include "../include/Person/Person.h"
#include "../include/Person/Account_Holder.h"
#include "../include/Account/Account.h"
#include "../include/Account/Current_Account.h"
#include "../include/Utility/dbmanager/db_manager.h"
#include "../include/Person/Person_factory.h"
#include "../include/Account/Account_factory.h"
#include "../include/Utility/tests/Log.h"
#include "../include/Transaction/Transaction.h"

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <string>
#include <filesystem>
#include <cstdlib>

class Bank
{
private:
    DB_Manager db;
    sqlite3 *db_ptr;

    void transfer_money(Account *from_account, Person *acc_holder)
    {
        system("cls");
        Utility_UI::print_header("Money Transfer");

        double amount = Utility_UI::take_balance_input("Transfer Amount");
        string recipient_acc_no = Utility_UI::take_pin_input("4-digit Recipient Account No");

        std::vector<std::string> recipient_data = DB_Manager::DB_Manager_Account::get_record_by_column(db_ptr, "acc_no", recipient_acc_no);

        if (!recipient_data.empty())
        {
            std::vector<std::string> recipient_person_data = DB_Manager::DB_Manager_Person::get_record_by_column(db_ptr, "id", recipient_data[recipient_data.size() - 1]);

            Person *recipient_person = Person_factory::create_person(recipient_person_data);
            Account *recipient_account = Account_Factory::create_account(recipient_data, recipient_person);

            TransactionResult result = Transaction::transfer(from_account, recipient_account, acc_holder, amount);

            if (result.is_successful)
            {
                Utility_UI::print_success_message(result.message);
                DB_Manager::DB_Manager_Account::update_record(db_ptr, from_account->getAccNo(), from_account->getBalance());
                DB_Manager::DB_Manager_Account::update_record(db_ptr, recipient_account->getAccNo(), recipient_account->getBalance());
            }
            else
            {
                Utility_UI::print_error_message(result.message);
            }

            delete recipient_account;
            delete recipient_person;
        }
        else
        {
            Utility_UI::print_error_message("Recipient account not found!");
        }
        getch();
    }
    void withdraw_money(Account *account, Person *acc_holder)
    {
        system("cls");
        Utility_UI::print_header("Wihdraw");

        double amount = Utility_UI::take_balance_input("Withdraw Amount");

        TransactionResult result = Transaction::withdraw(account, acc_holder, amount);

        if (result.is_successful)
        {
            DB_Manager::DB_Manager_Account::update_record(db_ptr, account->getAccNo(), account->getBalance());
            Utility_UI::print_success_message(result.message);
        }
        else
        {
            Utility_UI::print_error_message(result.message);
        }

        getch();
    }
    void deposit_money(Account *account, Person *acc_holder)
    {
        system("cls");
        Utility_UI::print_header("Deposit");

        double amount = Utility_UI::take_balance_input("Deposit Amount");

        TransactionResult result = Transaction::deposit(account, acc_holder, amount);

        if (result.is_successful)
        {
            DB_Manager::DB_Manager_Account::update_record(db_ptr, account->getAccNo(), account->getBalance());
            Utility_UI::print_success_message(result.message);
        }
        else
        {
            Utility_UI::print_error_message(result.message);
        }

        getch();
    }
    void dashboard(Account *account, Person *acc_holder)
    {
        std::vector<std::string> dashboard_options = {"Deposit", "Withdraw", "Transfer", "Account Info", "Personal Details", "Logout"};
        int choice = 0;
        while (choice != dashboard_options.size())
        {
            system("cls");
            choice = Utility_UI::print_menu_box("Dashboard | " + Utility_UI::get_formatted_date() + " | " + Utility_UI::get_formatted_time(), dashboard_options);
            if (choice == dashboard_options.size())
            {
                return;
            }
            else if (choice == 5)
            {
                system("cls");
                Utility_UI::print_header("Account Info");
                acc_holder->display_info();
                getch();
            }
            else if (choice == 4)
            {
                system("cls");
                Utility_UI::print_header("Personal Info");
                account->display_info();
                getch();
            }
            else if (choice == 3)
            {
                transfer_money(account, acc_holder);
            }
            else if (choice == 2)
            {
                withdraw_money(account, acc_holder);
            }
            else if (choice == 1)
            {
                deposit_money(account, acc_holder);
            }
        }
    }

    void login()
    {
        system("cls");
        std::vector<std::string> account_data;
        std::vector<std::string> person_data;
        Person *account_holder = nullptr;
        Account *account = nullptr;

        Utility_UI::print_header("Log In to your Account");
        string acc_no = Utility_UI::take_pin_input("Account No", 4);
        account_data = DB_Manager::DB_Manager_Account::get_record_by_column(db_ptr, "acc_no", acc_no);

        if (!account_data.empty())
        {
            string user_entered_pin = Utility_UI::take_pin_input();
            if (account_data[account_data.size() - 3] == user_entered_pin)
            {
                person_data = DB_Manager::DB_Manager_Person::get_record_by_column(db_ptr, "id", account_data[account_data.size() - 1]);

                if (!person_data.empty())
                {
                    account_holder = Person_factory::create_person(person_data);
                    if (account_holder != nullptr)
                    {
                        account = Account_Factory::create_account(account_data, account_holder);
                        if (account != nullptr)
                        {
                            dashboard(account, account_holder);
                        }
                    }
                }
            }
            else
            {
                Utility_UI::print_error_message("Invalid PIN!");
            }
        }
        else
        {
            Utility_UI::print_error_message("Account not found!");
        }

        if (account != nullptr)
            delete account;
        if (account_holder != nullptr)
            delete account_holder;
        getch();
    }

    void create_new_account()
    {
        Person *account_holder = new AccountHolder();
        Account *account = nullptr;
        system("cls");
        std::vector<std::string> types_of_accounts = {"Current Account"};

        Utility_UI::print_header("Account Creation");

        account_holder->get_common_inputs();
        account_holder->get_specific_inputs();

        int person_id = DB_Manager::DB_Manager_Person::insert_record(db_ptr, account_holder->getName(), account_holder->getAge(), "AccountHolder", account_holder->getPhone(), account_holder->getAddress());

        int acc_type_choice = Utility_UI::print_menu_box("Account Type", types_of_accounts);
        if (acc_type_choice == 1)
        {
            account = new Current_Account();
        }
        account_holder->setId(person_id);

        account->get_common_inputs(account_holder);
        account->get_specific_inputs();

        DB_Manager::DB_Manager_Account::insert_record(db_ptr, account->getAccNo(), account->getBalance(), account->getType(), account->getPin(), account->getOwner()->getId());
        Utility_UI::print_success_message("Account Created, ID: " + account->getAccNo());
        getch();
        delete account_holder;
        delete account;
        system("cls");
    }

    void exit_bank()
    {
        system("cls");
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
        std::vector<string> main_menu_options = {"Login", "Create Account", "Exit"};

        while (choice != main_menu_options.size())
        {
            system("cls");
            choice = Utility_UI::print_menu_box("Bank Mangement System", main_menu_options);
            if (choice == 3)
            {
                exit_bank();
                break;
            }
            else if (choice == 2)
            {
                create_new_account();
            }
            else if (choice == 1)
            {
                login();
            }
        }
    }

public:
    Bank(const std::string &db_path) : db(db_path)
    {
        db_ptr = db.get_db();

        // Create tables
        DB_Manager::DB_Manager_Person::create_table(db_ptr);
        DB_Manager::DB_Manager_Account::create_table(db_ptr);
        DB_Manager::DB_Manager_Transaction::create_table(db_ptr);
    }

    void run()
    {
        main_menu();
    }
};

std::string get_executable_directory(const char *argv0)
{
    std::filesystem::path p = std::filesystem::absolute(argv0);
    return p.parent_path().string();
}

int main(int argc, char *argv[])
{
    std::string exeDir = get_executable_directory(argv[0]) + "\\data.db";
    std::cout << "Database path: " << exeDir << std::endl;

    try
    {
        Bank bank(exeDir);
        bank.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}