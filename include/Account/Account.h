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

public:
    Account();

    // Getters
    virtual string getAccNo();
    virtual double getBalance();
    virtual string getType();
    virtual string getPin();
    virtual Person *getOwner();

    // Setters
    virtual void setAccNo(const string &acc_no);
    virtual void setBalance(double balance);
    virtual void setType(const string &type);
    virtual void setPin(const string &pin);
    virtual void setOwner(Person *owner);

    // Transaction methods
    virtual void deposit(float amount) = 0;
    virtual void withdraw(float amount) = 0;
    virtual void transfer(Account *dest_acc, float amount) = 0;

    void get_common_inputs(Person * acc_holder);
    virtual void get_specific_inputs() = 0;
    virtual void display_info() = 0;

    ~Account();
};