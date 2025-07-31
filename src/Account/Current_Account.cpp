#include "../../include/Account/Current_Account.h"
#include "../../include/Utility/UI/Utility_UI.h"
#include "../../include/Person/Person.h"
#include <iostream>

Current_Account::Current_Account() : Account()
{
    this->setType("Current Account");
}

void Current_Account::deposit(float amount)
{
}

void Current_Account::withdraw(float amount)
{
}

void Current_Account::transfer(Account *dest_acc, float amount)
{
}

void Current_Account::get_specific_inputs()
{
    this->setBalance(Utility_UI::take_balance_input("Initial Amount(min: 25000)", 25000.0));
}

void Current_Account::display_info()
{
    std::cout << "Account No. " << this->getAccNo() << std::endl;
    std::cout << "Type: " << this->getType() << std::endl;
    std::cout << "Balance: " << this->getBalance() << std::endl;
    std::cout << "Owner: " << this->getOwner()->getName() << std::endl;
}

Current_Account::~Current_Account() {}