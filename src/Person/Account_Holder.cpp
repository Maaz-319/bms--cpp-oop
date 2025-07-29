#include "Account_Holder.h"

int AccountHolder::account_holder_count = 0;

AccountHolder::AccountHolder() : Person()
{
    this->setType("AccountHolder");
    AccountHolder::account_holder_count++;
}

int AccountHolder::get_count()
{
    return AccountHolder::account_holder_count;
}

void AccountHolder::get_specific_inputs() {}

AccountHolder::~AccountHolder()
{
    this->account_holder_count--;
}