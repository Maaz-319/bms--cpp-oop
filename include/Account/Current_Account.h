#pragma once

#include "Account.h"

class Current_Account : public Account
{
public:
    Current_Account();

    void get_specific_inputs() override;
    void display_info() override;

    ~Current_Account();
};