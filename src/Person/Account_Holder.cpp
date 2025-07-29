#include "../../include/Person/Account_Holder.h"
#include "../../include/Utility/UI/Utility_UI.h"
#include <iostream>

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

void AccountHolder::display_info()
{
    Utility_UI::print_header("[INFO]: Account Holder " + this->getName());
    std::cout << "Age: " << this->getAge() << std::endl;
    std::cout << "Phone: " << this->getPhone() << std::endl;
    std::cout << "Address: " << this->getAddress() << std::endl;
}

AccountHolder::~AccountHolder()
{
    this->account_holder_count--;
}