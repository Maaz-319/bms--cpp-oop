#include "../../include/Account/Account.h"
#include "../../include/Utility/UI/Utility_UI.h"

Account::Account() : acc_no(""), balance(0.0), type(""), pin(""), owner(nullptr) {}

// Getters
string Account::getAccNo() { return this->acc_no; }
double Account::getBalance() { return this->balance; }
string Account::getType() { return this->type; }
string Account::getPin() { return this->pin; }
Person *Account::getOwner() { return this->owner; }

// Setters
void Account::setAccNo(const string &acc_no) { this->acc_no = acc_no; }
void Account::setBalance(double balance) { this->balance = balance; }
void Account::setType(const string &type) { this->type = type; }
void Account::setPin(const string &pin) { this->pin = pin; }
void Account::setOwner(Person *owner) { this->owner = owner; }

// Transaction methods
void Account::deposit(float amount)
{
}

void Account::withdraw(float amount)
{
}

void Account::transfer(Account *toAccount, float amount)
{
}

void Account::get_common_inputs(Person *acc_holder)
{
    this->setOwner(acc_holder);
    this->setAccNo(Utility_UI::generate_4_digit_random_number());
    this->setPin(Utility_UI::take_pin_input());
}

static void login()
{
    
}

Account::~Account() {}