#include "../../include/Account/Account.h"
#include "../../include/Utility/UI/Utility_UI.h"

Account::Account() : acc_no(""), balance(0.0), type(""), pin(""), owner(nullptr), onetime_transaction_limit(10000.0), minimum_transaction_limit(100.0) {}

// Getters
string Account::getAccNo() { return this->acc_no; }
double Account::getBalance() { return this->balance; }
string Account::getType() { return this->type; }
string Account::getPin() { return this->pin; }
Person *Account::getOwner() { return this->owner; }
double Account::getOneTimeTransactionLimit() { return this->onetime_transaction_limit; }
double Account::getMinimumTransactionLimit() { return this->minimum_transaction_limit; }

// Setters
void Account::setAccNo(const string &acc_no) { this->acc_no = acc_no; }
void Account::setBalance(double balance) { this->balance = balance; }
void Account::setType(const string &type) { this->type = type; }
void Account::setPin(const string &pin) { this->pin = pin; }
void Account::setOwner(Person *owner) { this->owner = owner; }
void Account::setOneTimeTransactionLimit(double amount) { this->onetime_transaction_limit = amount; }
void Account::setMinimumTransactionLimit(double amount) { this->minimum_transaction_limit = amount; }

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