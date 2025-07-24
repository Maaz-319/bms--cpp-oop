#include "Current_Account.h"

Current_Account::Current_Account() : Account()
{
    this->setType("Current Account");
}

void Current_Account::deposit(float amount)
{
    if (amount > 0)
    {
        this->balance += amount;
    }
}

void Current_Account::withdraw(float amount)
{
    if (amount > 0 && amount <= this->balance)
    {
        this->balance -= amount;
    }
}

void Current_Account::transfer(Account *dest_acc, float amount)
{
    if (amount > 0 && amount <= this->balance)
    {
        this->withdraw(amount);
        dest_acc->deposit(amount);
    }
}

Current_Account::~Current_Account() {}