Bank Management System (C++)

Description

A console-based Bank Management System developed in C++ using Object-Oriented Programming (OOP) principles.
This system simulates real-world banking operations with user and admin functionalities, transaction tracking, and a clean modular architecture.

---

Features

User Features

- Secure Login using Account ID & PIN
- Check Account Balance
- Deposit Money (with validation)
- Withdraw Money (with balance check)
- Transfer Funds between accounts
- View Detailed Transaction History (with timestamp & balance)
- Change PIN

Admin Features

- Admin Login (secured)
- Create New Account
- Delete Account
- View All Accounts
- View Total Bank Balance

---

Advanced Features (Interview Level)

- Transaction System with:
  - Type (Deposit / Withdraw / Transfer)
  - Amount
  - Balance After Transaction
  - Timestamp

- Input Validation:
  - Prevent negative deposits
  - Prevent over-withdrawal
  - Handle invalid inputs

- Clean Modular Architecture

- Separation of Concerns (OOP Design)

---

Tech Stack

- C++
- Object-Oriented Programming (OOP)
- STL (Vectors, Strings)
- Modular File Structure

---

Project Structure

Bank Management System/

├── auth/ → Login & Authentication

├── core/ → Banking operations (deposit, withdraw, transfer)

├── data/ → Data management (accounts storage)

├── models/ → Account & Transaction classes

├── ui/ → User & Admin menus

├── utils/ → Helper functions (time, input handling)

├── main.cpp → Entry point

---

How to Run

Compile

g++ main.cpp data/DataManager.cpp ui/MainMenu.cpp ui/UserMenu.cpp ui/AdminMenu.cpp auth/Auth.cpp core/AccountOperations.cpp models/Transaction.cpp utils/helpers.cpp -o main

Run

./main

---

Sample Output

--- Transaction History ---

Deposited Rs. | Rs.500 | Balance: Rs.1500 | Time: Sun Apr 5
Withdrew Rs. | Rs.200 | Balance: Rs.1300 | Time: Sun Apr 5

---

Highlights

- Real-world banking logic implementation
- Strong OOP design (Classes, Encapsulation, Modularity)
- Clean CLI-based UI
- Scalable architecture (ready for SQL/GUI integration)

---

Future Improvements

- Data Persistence (File / SQL Database)
- GUI Interface (Qt / Web-based)
- Advanced Security (Encryption)
- Analytics Dashboard (Admin Insights)

---

Status

User System Completed
Admin Panel Completed
Transaction System Enhanced
Next: Data Persistence + SQL Integration

---

Author

Prantik
(B.Tech CSE Student | Aspiring Software Engineer 🚀)
