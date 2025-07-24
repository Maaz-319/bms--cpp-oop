#pragma once
#include "Person.h"
#include <string>

class Account
{
protected:
    string acc_no;
    float balance;
    string type;
    string pin;
    Person *owner;

public:
    Account();

    // Getters
    virtual string getAccNo();
    virtual float getBalance();
    virtual string getType();
    virtual string getPin();
    virtual Person *getOwner();

    // Setters
    virtual void setAccNo(const string &acc_no);
    virtual void setBalance(float balance);
    virtual void setType(const string &type);
    virtual void setPin(const string &pin);
    virtual void setOwner(Person *owner);

    // Transaction methods
    virtual void deposit(float amount) = 0;
    virtual void withdraw(float amount) = 0;
    virtual void transfer(Account *dest_acc, float amount) = 0;

    ~Account();
};