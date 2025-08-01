#pragma once
#include "../Person/Person.h"
#include <string>

using namespace std;

class Account
{
protected:
    string acc_no;
    double balance;
    string type;
    string pin;
    Person *owner;
    double onetime_transaction_limit;
    double minimum_transaction_limit;

public:
    Account();

    // Getters
    string getAccNo();
    double getBalance();
    string getType();
    string getPin();
    Person *getOwner();
    double getOneTimeTransactionLimit();
    double getMinimumTransactionLimit();

    // Setters
    void setAccNo(const string &acc_no);
    void setBalance(double balance);
    void setType(const string &type);
    void setPin(const string &pin);
    void setOwner(Person *owner);
    void setOneTimeTransactionLimit(double amount);
    void setMinimumTransactionLimit(double amount);

    void get_common_inputs(Person *acc_holder);
    virtual void get_specific_inputs() = 0;
    virtual void display_info() = 0;

    static void login();

    ~Account();
};