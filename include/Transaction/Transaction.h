#pragma once
#include "../Account/Account.h"
#include "../Person/Person.h"
#include <string>

struct TransactionResult
{
    bool is_successful = true;
    std::string message = "Transaction Successful";
};

class Transaction
{
private:
    static std::string generate_transaction_id();

public:
    Transaction() = delete;

    static TransactionResult withdraw(Account *account, Person *person, double amount);
    static TransactionResult deposit(Account *account, Person *person, double amount);
    static TransactionResult transfer(Account *from_account, Account *to_account, Person *person, double amount);
};