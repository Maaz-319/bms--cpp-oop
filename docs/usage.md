# Bank Management System - Usage Guide

## Overview

This guide provides comprehensive instructions for building, running, and using the Bank Management System. The system is a console-based application that provides banking operations including account creation, authentication, deposits, withdrawals, and transfers.

## System Requirements

### Prerequisites
- Windows Operating System
- C++ Compiler (g++ recommended)
- SQLite3 support
- Command Line Interface (CMD or PowerShell)

### Build Dependencies
- GCC/MinGW compiler with C++11 support or later
- SQLite3 library (included in the project)

## Building the Application

### Using the Build Script

The project includes a Windows batch script for easy compilation:

1. Open Command Prompt or PowerShell
2. Navigate to the project root directory
3. Run the build script:

```batch
build.bat
```

### Build Options

The build script provides several options:

1. **Compile only SQLite** - Compiles the SQLite library to object file
2. **Compile only BMS** - Compiles the Bank Management System
3. **Compile both SQLite and BMS** - Complete build process
4. **Exit** - Close the build script

### Manual Build Process

If you prefer to build manually:

```batch
# Create build directory
mkdir build

# Compile SQLite (if not already compiled)
g++ -c include/Utility/dbmanager/sqlite3.c -o include/Utility/dbmanager/sqlite3.o

# Compile the main application
g++ -o build/bms.exe src/main.cpp src/Account/Account.cpp src/Account/Current_Account.cpp src/Person/Person.cpp src/Person/Account_Holder.cpp src/Transaction/Transaction.cpp src/Utility/UI/Utility_UI.cpp include/Utility/dbmanager/sqlite3.o -I./include
```

## Running the Application

### Starting the System

1. Navigate to the build directory:
```batch
cd build
```

2. Run the executable:
```batch
bms.exe
```

### Database Initialization

The application automatically creates the SQLite database and required tables on first run. The database file `data.db` will be created in the build directory.

## User Interface Guide

### Main Menu

Upon starting the application, you will see the main menu with three options:

1. **Login** - Access existing account
2. **Create Account** - Register new account
3. **Exit** - Close the application

### Account Creation

To create a new account:

1. Select "Create Account" from the main menu
2. Provide personal information:
   - Full Name
   - Age
   - Phone Number (validated format)
   - Address
3. Choose account type (Currently only Current Account is available)
4. Set account details:
   - Initial deposit amount
   - 4-digit PIN for security
5. The system generates a unique 4-digit account number

**Example Account Creation Flow:**
```
Account Creation
================
Name: John Doe
Age: 30
Phone No: 1234567890
Address: 123 Main Street
Account Type: Current Account
Initial Deposit: 1000.00
PIN: 1234
Account Created, ID: 1001
```

### Login Process

To access an existing account:

1. Select "Login" from the main menu
2. Enter your 4-digit account number
3. Enter your 4-digit PIN
4. Upon successful authentication, access the dashboard

### Dashboard Operations

After successful login, the dashboard provides these options:

1. **Deposit** - Add money to your account
2. **Withdraw** - Remove money from your account
3. **Transfer** - Send money to another account
4. **Account Info** - View account details
5. **Personal Details** - View personal information
6. **Logout** - Return to main menu

## Banking Operations

### Deposit Money

1. Select "Deposit" from dashboard
2. Enter the amount to deposit
3. Confirm the transaction
4. View updated balance

**Transaction Limits:**
- Minimum deposit: Varies by account type
- Maximum single transaction: Account-specific limit

### Withdraw Money

1. Select "Withdraw" from dashboard
2. Enter the amount to withdraw
3. System validates:
   - Sufficient balance
   - Transaction limits
   - Minimum balance requirements
4. Confirm the transaction

**Validation Rules:**
- Amount must be positive
- Must not exceed available balance
- Must respect one-time transaction limits
- Must meet minimum transaction requirements

### Transfer Money

1. Select "Transfer" from dashboard
2. Enter transfer amount
3. Enter recipient's 4-digit account number
4. System validates both accounts
5. Confirm the transfer
6. Both accounts are updated automatically

**Transfer Process:**
```
Money Transfer
==============
Transfer Amount: 500.00
4-digit Recipient Account No: 1002
Transaction Successful
From: Account 1001
To: Account 1002
Amount: Rs.500.00
```

### View Account Information

Select "Account Info" to view:
- Account number
- Current balance
- Account type
- Transaction limits

Select "Personal Details" to view:
- Name and personal information
- Contact details
- Account holder status

## Input Validation

The system implements comprehensive input validation:

### Phone Number Validation
- Must be 10 digits
- Numbers only
- No special characters

### PIN Validation
- Exactly 4 digits
- Numbers only
- Secure input (characters hidden)

### Amount Validation
- Positive numbers only
- Decimal support for currency
- Range validation based on limits

### String Input Validation
- Length limits enforced
- Required field validation
- Sanitized input handling

## Transaction History

All transactions are automatically logged to the database with:
- Unique transaction ID
- Timestamp
- Transaction type (Deposit/Withdraw/Transfer)
- Amount and tax information
- Account details

## Error Handling

The system provides clear error messages for common scenarios:

### Authentication Errors
- "Account not found!" - Invalid account number
- "Invalid PIN!" - Incorrect PIN entered

### Transaction Errors
- "Not Enough Balance" - Insufficient funds
- "One Time Transaction Limit Reached" - Exceeds single transaction limit
- "Minimum Transaction Limit" - Below minimum amount
- "Invalid Amount" - Negative or invalid amount

### System Errors
- Database connection issues
- File system errors
- Memory allocation problems

## Security Features

### Authentication
- 4-digit account number
- 4-digit PIN protection
- Session-based access control

### Data Protection
- SQLite database with ACID properties
- Input sanitization
- Secure PIN entry (hidden characters)

### Transaction Security
- Account validation before transfers
- Balance verification
- Transaction limits enforcement

## Database Management

### Database Location
- Development: `build/data.db`
- Contains all user and transaction data

### Database Backup
To backup your data:
1. Locate the `data.db` file in the build directory
2. Copy to secure location
3. Restore by replacing the database file

### Database Structure
The system uses three main tables:
- **Person** - User personal information
- **Account** - Account details and balances
- **Transaction** - Transaction history

## Troubleshooting

### Common Issues

**Build Errors:**
- Ensure g++ compiler is installed and in PATH
- Verify all source files are present
- Check for syntax errors in recent changes

**Runtime Errors:**
- Database file permissions
- Insufficient disk space
- Corrupted database file

**Application Crashes:**
- Check console for error messages
- Verify database integrity
- Restart application

### Debug Mode

For debugging, compile with debug flags:
```batch
g++ -g -DDEBUG -o build/bms_debug.exe [source files]
```

### Log Files

The system includes a logging utility in `include/Utility/tests/Log.h` for development debugging.

## Best Practices

### Account Management
- Use strong 4-digit PINs
- Remember your account number
- Keep personal information updated

### Transaction Safety
- Verify recipient account numbers
- Double-check transaction amounts
- Monitor account balance regularly

### System Maintenance
- Regular database backups
- Keep build environment updated
- Monitor disk space usage

## Extending the System

### Adding New Account Types
1. Create new class inheriting from Account
2. Implement required virtual methods
3. Update Account_Factory for creation
4. Add to menu options

### Adding New Transaction Types
1. Add methods to Transaction class
2. Update database schema if needed
3. Implement UI components
4. Add validation rules

### Custom UI Components
Extend Utility_UI class with new methods for enhanced user experience.

## Support and Maintenance

For technical issues or feature requests:
- Review the API documentation
- Check the class hierarchy in `class.txt`
- Examine source code for implementation details
- Test changes in development environment

> This Documentation is AI-generated and may not cover all edge cases or specific implementation details. Always refer to the source code for the most accurate information.