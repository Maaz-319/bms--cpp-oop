# Bank Management System API Documentation

## Overview

This document provides comprehensive API documentation for the Bank Management System implemented in C++ using Object-Oriented Programming principles. The system provides a complete banking solution with account management, transaction processing, and data persistence using SQLite.

## Core Classes

### Person Class Hierarchy

#### Person (Abstract Base Class)
The base class for all person types in the system.

**Header File:** `include/Person/Person.h`

**Protected Attributes:**
- `int id` - Unique identifier for the person
- `string name` - Full name of the person
- `int age` - Age of the person
- `string type` - Type of person (e.g., "AccountHolder")
- `string phone` - Contact phone number
- `string address` - Residential address

**Static Members:**
- `static int count` - Total count of Person objects created

**Public Methods:**

```cpp
// Constructors and Destructors
Person();
virtual ~Person();

// Getters
string getName();
int getAge();
string printType();
string getPhone();
string getAddress();
static int getCount();
int getId();

// Setters
void setName(const string &name);
void setAge(int age);
void setType(const string &type);
void setPhone(const string &phone);
void setAddress(const string &address);
void setId(int id);

// Input/Output Methods
void get_common_inputs();
virtual void get_specific_inputs() = 0;
virtual void display_info() = 0;
```

#### AccountHolder Class
Concrete implementation of Person for bank account holders.

**Header File:** `include/Person/Account_Holder.h`

**Static Members:**
- `static int account_holder_count` - Count of AccountHolder objects

**Public Methods:**
```cpp
AccountHolder();
~AccountHolder();
static int get_count();
void get_specific_inputs() override;
void display_info() override;
```

### Account Class Hierarchy

#### Account (Abstract Base Class)
The base class for all account types in the banking system.

**Header File:** `include/Account/Account.h`

**Protected Attributes:**
- `string acc_no` - Unique account number
- `double balance` - Current account balance
- `string type` - Type of account (e.g., "Current")
- `string pin` - 4-digit PIN for authentication
- `Person *owner` - Pointer to the account owner
- `double onetime_transaction_limit` - Maximum single transaction amount
- `double minimum_transaction_limit` - Minimum transaction amount

**Public Methods:**

```cpp
// Constructors and Destructors
Account();
~Account();

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

// Input/Output Methods
void get_common_inputs(Person *acc_holder);
virtual void get_specific_inputs() = 0;
virtual void display_info() = 0;

// Static Methods
static void login();
```

#### Current_Account Class
Concrete implementation of Account for current accounts.

**Header File:** `include/Account/Current_Account.h`

**Public Methods:**
```cpp
Current_Account();
~Current_Account();
void get_specific_inputs() override;
void display_info() override;
```

### Transaction Management

#### TransactionResult Structure
Represents the result of a transaction operation.

**Header File:** `include/Transaction/Transaction.h`

**Members:**
```cpp
struct TransactionResult {
    bool is_successful = true;
    std::string message = "Transaction Successful";
};
```

#### Transaction Class
Static utility class for handling banking transactions.

**Header File:** `include/Transaction/Transaction.h`

**Static Methods:**
```cpp
// Transaction Operations
static TransactionResult withdraw(Account *account, Person *person, double amount);
static TransactionResult deposit(Account *account, Person *person, double amount);
static TransactionResult transfer(Account *from_account, Account *to_account, Person *person, double amount);

// Private Helper Methods
static std::string generate_transaction_id();
```

**Method Details:**

##### withdraw()
Processes a withdrawal transaction from an account.

**Parameters:**
- `Account *account` - The account to withdraw from
- `Person *person` - The person initiating the transaction
- `double amount` - The amount to withdraw

**Returns:** `TransactionResult` with success status and message

**Validation Rules:**
- Amount must be positive
- Amount must not exceed one-time transaction limit
- Account must have sufficient balance
- Amount must meet minimum transaction limit

##### deposit()
Processes a deposit transaction to an account.

**Parameters:**
- `Account *account` - The account to deposit to
- `Person *person` - The person initiating the transaction
- `double amount` - The amount to deposit

**Returns:** `TransactionResult` with success status and message

##### transfer()
Processes a money transfer between two accounts.

**Parameters:**
- `Account *from_account` - The source account
- `Account *to_account` - The destination account
- `Person *person` - The person initiating the transaction
- `double amount` - The amount to transfer

**Returns:** `TransactionResult` with success status and message

### Database Management

#### DB_Manager Class
Manages SQLite database operations for the banking system.

**Header File:** `include/Utility/dbmanager/db_manager.h`

**Constructor:**
```cpp
DB_Manager(const std::string &db_name);
```

**Public Methods:**
```cpp
~DB_Manager();
sqlite3 *get_db() const;
```

#### DB_Manager_Person Class
Nested class for Person table operations.

**Static Methods:**
```cpp
// Table Management
static void create_table(sqlite3 *db);

// CRUD Operations
static int insert_record(sqlite3 *db, const std::string &name, int age, 
                        const std::string &type, const std::string &phone, 
                        const std::string &address);
static bool delete_record(sqlite3 *db, int id);
static bool update_record(sqlite3 *db, int id, const std::string &name, 
                         int age, const std::string &type, 
                         const std::string &phone, const std::string &address);

// Query Operations
static std::vector<std::string> get_column_values(sqlite3 *db, 
                                                 const std::string &column_name);
static std::vector<std::string> get_record_by_column(sqlite3 *db, 
                                                    const std::string &column_name,
                                                    const std::string &value);
```

#### DB_Manager_Account Class
Nested class for Account table operations.

**Static Methods:**
```cpp
// Table Management
static void create_table(sqlite3 *db);

// CRUD Operations
static void insert_record(sqlite3 *db, const std::string &acc_no, 
                         double balance, const std::string &type,
                         const std::string &pin, int owner_id);
static bool delete_record(sqlite3 *db, const std::string &acc_no);
static bool update_record(sqlite3 *db, const std::string &acc_no, 
                         double new_balance);

// Query Operations
static std::vector<std::string> get_column_values(sqlite3 *db, 
                                                 const std::string &column_name);
static std::vector<std::string> get_record_by_column(sqlite3 *db, 
                                                    const std::string &column_name,
                                                    const std::string &value);
static bool account_exists(sqlite3 *db, const std::string &acc_no);
```

#### DB_Manager_Transaction Class
Nested class for Transaction table operations.

**Static Methods:**
```cpp
// Table Management
static void create_table(sqlite3 *db);

// CRUD Operations
static int insert_record(sqlite3 *db, const std::string &initiator_acc_no,
                        const std::string &destination_acc_no,
                        const std::string &timestamp, double amount,
                        double tax_amount, const std::string &type);
static bool delete_record(sqlite3 *db, int transaction_id);
static bool update_record(sqlite3 *db, int transaction_id,
                         const std::string &initiator_acc_no,
                         const std::string &destination_acc_no,
                         const std::string &timestamp, double amount,
                         double tax_amount, const std::string &type);

// Query Operations
static std::vector<std::string> get_column_values(sqlite3 *db, 
                                                 const std::string &column_name);
static std::vector<std::string> get_record_by_column(sqlite3 *db, 
                                                    const std::string &column_name,
                                                    const std::string &value);
```

### User Interface Utilities

#### Utility_UI Class
Static utility class providing console-based user interface functions.

**Header File:** `include/Utility/UI/Utility_UI.h`

**Static Methods:**

```cpp
// Display Methods
static void print_line(int length = 50);
static void print_dashed_line(int length = 50);
static void print_header(const std::string& header, int width = 60);
static int print_menu_box(const std::string &title, 
                         const std::vector<std::string> &options);
static void print_success_message(const std::string &message);
static void print_error_message(const std::string &message);
static void print_info_box(const std::string &message);

// Console Formatting
static void set_console_color(int color);
static void reset_console_color();

// Input Methods
static int take_integer_input(int min, int max, const std::string &prompt);
static std::string take_phone_input(const std::string &prompt = "Phone No");
static std::string take_string_input(const std::string &prompt, int limit = 100);
static std::string take_email_input(const std::string &prompt = "Email");
static std::string take_pin_input(const std::string &prompt = "PIN", int length = 4);
static double take_balance_input(const std::string &prompt);

// Utility Methods
static std::string get_formatted_date();
static std::string get_formatted_time();
```

### Factory Classes

#### Person_factory Class
Factory class for creating Person objects.

**Header File:** `include/Person/Person_factory.h`

**Static Methods:**
```cpp
static Person* create_person(const std::vector<std::string> &person_data);
```

#### Account_Factory Class
Factory class for creating Account objects.

**Header File:** `include/Account/Account_factory.h`

**Static Methods:**
```cpp
static Account* create_account(const std::vector<std::string> &account_data, 
                              Person *owner);
```

## Database Schema

### Person Table
```sql
CREATE TABLE IF NOT EXISTS Person (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    age INTEGER,
    phone TEXT,
    address TEXT,
    type TEXT
);
```

### Account Table
```sql
CREATE TABLE IF NOT EXISTS Account (
    acc_no TEXT PRIMARY KEY,
    balance REAL NOT NULL,
    pin TEXT NOT NULL,
    type TEXT NOT NULL,
    owner_id INTEGER NOT NULL,
    FOREIGN KEY (owner_id) REFERENCES Person(id)
);
```

### Transaction Table
```sql
CREATE TABLE IF NOT EXISTS [Transaction] (
    transaction_id INTEGER PRIMARY KEY AUTOINCREMENT,
    initiator_acc_no TEXT NOT NULL,
    destination_acc_no TEXT NOT NULL,
    timestamp TEXT NOT NULL,
    amount REAL NOT NULL,
    tax_amount REAL NOT NULL,
    type TEXT NOT NULL,
    FOREIGN KEY (initiator_acc_no) REFERENCES Account(acc_no),
    FOREIGN KEY (destination_acc_no) REFERENCES Account(acc_no)
);
```

## Error Handling

The system uses several error handling mechanisms:

1. **Exception Handling:** Database operations throw `std::runtime_error` exceptions
2. **TransactionResult Structure:** Transaction operations return structured results
3. **Input Validation:** UI utilities validate user inputs
4. **Database Constraints:** Foreign key constraints ensure data integrity

## Thread Safety

The current implementation is designed for single-threaded use. The SQLite database operations are thread-safe by default, but the application logic does not implement additional thread synchronization mechanisms.

> This Documentation is AI-generated and may not cover all edge cases or specific implementation details. Always refer to the source code for the most accurate information.