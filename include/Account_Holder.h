#pragma once
#include "Person.h"

class AccountHolder : public Person
{
private:
    static int account_holder_count;

public:
    AccountHolder();
    static int get_count();

    // void get_specific_inputs() override;

    ~AccountHolder();
};
