#pragma once
#include "Current_Account.h"
#include "Account.h"
#include <vector>

#include "../Person/Person_factory.h"

class Account_Factory
{
public:
    static Account *create_account(std::vector<std::string> argument_list, Person *person)
    {
        Account *account = nullptr;
        if (argument_list[argument_list.size() - 2] == "Current Account")
        {
            account = new Current_Account();
            account->setAccNo(argument_list[0]);
            account->setBalance(std::stod(argument_list[1]));
            account->setPin(argument_list[2]);
            account->setOwner(person);
        }
        return account;
    }
};