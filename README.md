Bank Management System (C++ CLI)

Overview

This project is a command-line based Bank Management System implemented in C++ with MySQL integration. It simulates core banking operations such as account management, secure authentication, and financial transactions.

The system is designed using a modular architecture and demonstrates practical usage of database connectivity, structured programming, and real-world banking logic.

---

Objectives

- To implement a real-world banking workflow in a CLI environment
- To integrate C++ applications with a relational database (MySQL)
- To demonstrate secure configuration using environment variables
- To practice modular and scalable software design

---

Features

User Functionalities

- Login using Account ID and PIN
- View account balance
- Deposit money into account
- Withdraw money with validation checks
- Transfer funds between accounts
- View detailed transaction history

Admin Functionalities

- Admin authentication (hardcoded or configurable)
- View all accounts
- Monitor transactions
- Manage user accounts

---

System Architecture

The application follows a modular layered structure:

UI Layer (Menus)
↓
Business Logic (Core Operations)
↓
Data Layer (DataManager)
↓
Database (MySQL)

Module Breakdown

- "ui/" → Handles user interaction and menus
- "core/" → Contains banking operations logic
- "data/" → Manages database interactions
- "database/" → Handles DB connection
- "models/" → Defines data structures
- "auth/" → Authentication logic
- "utils/" → Helper utilities

---

Technologies Used

- Programming Language: C++
- Database: MySQL
- Database Interface: MySQL C API
- Environment Handling: ".env" configuration
- Platform: CLI (Command Line Interface)

---

Database Design

Table: "accounts"

CREATE TABLE accounts (
account_id VARCHAR(20) PRIMARY KEY,
name VARCHAR(100),
balance DOUBLE,
pin INT
);

Table: "transactions"

CREATE TABLE transactions (
id INT AUTO_INCREMENT PRIMARY KEY,
account_id VARCHAR(20),
type VARCHAR(50),
amount DOUBLE,
balance DOUBLE,
timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);

---

Sample Data

INSERT INTO accounts VALUES
('ABCD1234','PRANTIK',2002,2006),
('EFGH5678','PARTH',73510,1234);

---

Prerequisites

Before running the project, ensure the following are installed:

- C++ Compiler (g++ via MinGW or equivalent)
- MySQL Server
- MySQL Workbench (optional, for GUI)
- Git (optional)

---

Installation and Setup

Step 1: Clone Repository

git clone <https://github.com/Prantik400/Bank-Management-System-CPP>

cd Bank-Management-System-CPP

---

Step 2: Configure Database

1. Open MySQL Workbench
2. Create database:

CREATE DATABASE bank_system;
USE bank_system;

3. Create tables using schema provided above

4. Insert sample data

---

Step 3: Configure Environment Variables

Create a ".env" file in the root directory:

DB_HOST=localhost
DB_USER=root
DB_PASS=your_password
DB_NAME=bank_system
DB_PORT=3306

Ensure ".env" is added to ".gitignore".

---

Step 4: Build and Run

chmod +x run.sh
./run.sh

---

Execution Flow

1. Application starts and connects to MySQL database
2. Displays main menu
3. User selects login type (User/Admin)
4. Based on authentication, appropriate menu is shown
5. Operations are performed and stored in database
6. Transaction history is updated in real time

---

Screenshots

Create a folder named "screenshots/" and include images:

../screenshots/mainMenu.png
../screenshots/userMenuTransactionHistory.png
../screenshots/adminMenuAllAccounts.png

---

Security Considerations

- Database credentials are stored using environment variables
- ".env" file is excluded via ".gitignore"
- No sensitive credentials are hardcoded in source code
- Input validation is applied for financial operations

---

Limitations

- CLI-based interface (no GUI)
- No encryption for PIN storage (can be improved)
- Admin authentication is basic
- No concurrency handling

---

Future Enhancements

- Graphical User Interface (GUI or Web App)
- Password hashing and encryption
- REST API integration
- Docker containerization
- Multi-user concurrency handling
- Support for NoSQL databases

---

Learning Outcomes

This project demonstrates:

- Integration of C++ with MySQL
- Real-world transaction handling
- Modular software design
- Use of environment variables for secure configuration
- Debugging and cross-platform compatibility

---

Author

Prantik

---

License

This project is for educational purposes and can be modified or extended as needed.
