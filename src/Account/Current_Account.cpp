#include "../../include/Account/Current_Account.h"

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

Current_Account::~Current_Account() {}