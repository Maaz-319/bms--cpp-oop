# Bank Management System

A C++ Object-Oriented Banking Application.

## Features

### Core Banking Operations
- **Account Management**: Create and manage bank accounts with secure authentication
- **Transaction Processing**: Support for deposits, withdrawals, and money transfers
- **Balance Management**: Real-time balance updates with transaction validation
- **User Authentication**: Secure login system with PIN-based authentication

### Technical Highlights
- **Object-Oriented Design**: Implements inheritance, polymorphism, and encapsulation
- **Database Integration**: SQLite database for persistent data storage
- **Factory Pattern**: Dynamic object creation for accounts and persons
- **Transaction Safety**: Comprehensive validation and error handling
- **Console Interface**: User-friendly text-based interface with input validation

## Architecture

### Class Hierarchy

The system follows a well-structured class hierarchy:

```
Person (Abstract)
└── AccountHolder

Account (Abstract)  
└── Current_Account

Transaction (Static Utility)
DB_Manager (Database Operations)
├── DB_Manager_Person
├── DB_Manager_Account
└── DB_Manager_Transaction

Utility_UI (Interface Utilities)
```

### Database Schema

The system uses three main tables:
- **Person**: Stores user personal information
- **Account**: Manages account details and balances  
- **Transaction**: Logs all banking transactions

## Quick Start

### Prerequisites
- Windows Operating System
- C++ Compiler (g++ recommended)
- SQLite3 support (included)

### Building the Application

1. Clone the repository:
```bash
git clone <repository-url>
cd bms--cpp-oop
```

2. Build using the provided script:
```batch
build.bat
```

3. Run the application:
```batch
cd build
bms.exe
```

### First Time Setup

The application will automatically:
- Create the SQLite database
- Initialize required tables
- Present the main menu for operation

## Usage

### Creating an Account
1. Select "Create Account" from the main menu
2. Provide personal information (name, age, phone, address)
3. Choose account type (Current Account available)
4. Set initial deposit and 4-digit PIN
5. Receive unique 4-digit account number

### Banking Operations
1. Login with account number and PIN
2. Access dashboard with options:
   - **Deposit**: Add money to account
   - **Withdraw**: Remove money with validation
   - **Transfer**: Send money to other accounts
   - **View Details**: Check account and personal information

### Security Features
- PIN-based authentication
- Transaction limit validation
- Balance verification
- Input sanitization

## Documentation

Comprehensive documentation is available in the `docs/` folder:

- **[API Documentation](docs/API.md)**: Complete class reference and method documentation
- **[Usage Guide](docs/usage.md)**: Detailed user guide with examples and troubleshooting

## Project Structure

```
bms--cpp-oop/
├── build/                 # Compiled executables and database
├── docs/                  # Documentation files
├── include/               # Header files
│   ├── Account/          # Account class definitions
│   ├── Person/           # Person class definitions
│   ├── Transaction/      # Transaction management
│   └── Utility/          # Database and UI utilities
├── src/                  # Source code implementation
├── build.bat             # Build script
├── class.txt             # Class hierarchy reference
└── README.md             # This file
```

## Key Components

### Account Management
- Abstract base class `Account` with concrete `Current_Account` implementation
- Factory pattern for dynamic account creation
- PIN-based security with input validation

### Transaction System
- Static `Transaction` class with withdraw, deposit, and transfer operations
- Comprehensive validation including balance checks and transaction limits
- Automatic database logging of all transactions

### Database Layer
- `DB_Manager` class with nested managers for each table
- SQLite integration with prepared statements
- CRUD operations with error handling

### User Interface
- `Utility_UI` class providing console-based interface
- Input validation and formatted output
- Color-coded messages for better user experience

## Design Patterns

The system implements several design patterns:
- **Factory Pattern**: For creating Person and Account objects
- **Template Method Pattern**: In abstract base classes
- **Static Utility Pattern**: For Transaction and UI operations

## Error Handling

Robust error handling includes:
- Exception handling for database operations
- Input validation with user-friendly error messages
- Transaction result structures for operation feedback
- Graceful handling of invalid operations

## Development

### Building from Source
The project uses a batch script for compilation that handles:
- SQLite library compilation
- Source code compilation with proper linking
- Executable generation in build directory

### Extending the System
The modular design allows for easy extension:
- Add new account types by inheriting from `Account`
- Implement new transaction types in the `Transaction` class
- Extend UI functionality through `Utility_UI`

## Technical Specifications

- **Language**: C++
- **Database**: SQLite3
- **Platform**: Windows
- **Architecture**: Object-Oriented with separation of concerns
- **Build System**: Custom batch script with g++ compiler

## License

This project was developed for practice purposes in Object-Oriented Programming principles in C++.

## Author

**Maaz Bin Asif**
- LinkedIn: [@maazbinasif](https://linkedin.com/in/maazbinasif)
- Instagram: [@maaz.binasif](https://instagram.com/maaz.binasif)

For technical questions or suggestions, please refer to the detailed documentation in the `docs/` folder or examine the source code structure.