#include "../../include/Transaction/Transaction.h"
#include "../../include/Utility/UI/Utility_UI.h"

TransactionResult Transaction::withdraw(Account *init_account, Person *person, double amount)
{
    TransactionResult result;
    if (amount < 0.0)
    {
        result.is_successful = false;
        result.message = "Invalid Amount";
    }
    if (result.is_successful && amount > init_account->getOneTimeTransactionLimit())
    {
        result.is_successful = false;
        result.message = "One Time Transaction Limit: Rs." + to_string(init_account->getOneTimeTransactionLimit()) + " Reached";
    }
    if (result.is_successful && amount > init_account->getBalance())
    {
        result.is_successful = false;
        result.message = "Not Enough Balance, Current Balance: Rs." + to_string(init_account->getBalance());
    }
    if (result.is_successful && amount < init_account->getMinimumTransactionLimit())
    {
        result.is_successful = false;
        result.message = "Minimum Transaction Limit: Rs." + to_string(init_account->getMinimumTransactionLimit());
    }
    if (result.is_successful)
    {
        init_account->setBalance(init_account->getBalance() - amount);
        result.message = "Transaction Type: Withdraw\nAccount No. " + init_account->getAccNo() + "\nAmount: Rs." + to_string(amount) + "\nCurrent Balance: " + to_string(init_account->getBalance());
    }
    return result;
}

TransactionResult Transaction::deposit(Account *init_account, Person *person, double amount)
{
    TransactionResult result;
    if (amount < 0.0)
    {
        result.is_successful = false;
        result.message = "Invalid Amount";
    }
    if (result.is_successful && amount > init_account->getOneTimeTransactionLimit())
    {
        result.is_successful = false;
        result.message = "One Time Transaction Limit: Rs." + to_string(init_account->getOneTimeTransactionLimit()) + " Reached";
    }
    if (result.is_successful && amount < init_account->getMinimumTransactionLimit())
    {
        result.is_successful = false;
        result.message = "Minimum Transaction Limit: Rs." + to_string(init_account->getMinimumTransactionLimit());
    }
    if (result.is_successful)
    {
        init_account->setBalance(init_account->getBalance() + amount);
        result.message = "Transaction Type: Deposit\nAccount No. " + init_account->getAccNo() + "\nAmount: Rs." + to_string(amount) + "\nYour Current Balance: " + to_string(init_account->getBalance());
    }
    return result;
}

TransactionResult Transaction::transfer(Account *from_account, Account *to_account, Person *person, double amount)
{
    TransactionResult result;
    if (amount < 0.0)
    {
        result.is_successful = false;
        result.message = "Invalid Amount";
    }
    if (result.is_successful && amount > from_account->getOneTimeTransactionLimit())
    {
        result.is_successful = false;
        result.message = "One Time Transaction Limit: Rs." + to_string(from_account->getOneTimeTransactionLimit()) + " Reached";
    }
    if (result.is_successful && amount > from_account->getBalance())
    {
        result.is_successful = false;
        result.message = "Not Enough Balance, Current Balance: Rs." + to_string(from_account->getBalance());
    }
    if (result.is_successful && amount < from_account->getMinimumTransactionLimit())
    {
        result.is_successful = false;
        result.message = "Minimum Transaction Limit: Rs." + to_string(from_account->getMinimumTransactionLimit());
    }
    if (result.is_successful)
    {
        from_account->setBalance(from_account->getBalance() - amount);
        to_account->setBalance(to_account->getBalance() + amount);
        result.message = "Transaction Type: Transfer\nFrom Account No. " + from_account->getAccNo() + "\nTo Account No. " + to_account->getAccNo() + "\nAmount: Rs." + to_string(amount) + "\nYour Current Balance: " + to_string(from_account->getBalance());
    }
    return result;
}
