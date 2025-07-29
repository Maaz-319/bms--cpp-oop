#pragma once

#include "Account.h"

class Current_Account : public Account
{
public:
    Current_Account();

    // Override the deposit method to allow deposits
    void deposit(float amount) override;

    // Override the withdraw method to allow withdrawals
    void withdraw(float amount) override;

    // Override the transfer method to allow transfers
    void transfer(Account *dest_acc, float amount) override;

    void get_specific_inputs() override;
    void display_info() override;

    ~Current_Account();
};