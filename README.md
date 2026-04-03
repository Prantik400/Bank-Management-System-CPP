# Bank Management System (C++)

## Description

A console-based Bank Management System developed in C++ using Object-Oriented Programming principles.
It allows users to securely perform banking operations such as deposit, withdrawal, transfer, and transaction tracking.

## Features

- Secure Login using PIN
- Check Balance
- Deposit Money
- Withdraw Money
- Transfer Funds
- Transaction History
- Change PIN
- Modular Code Structure

## Tech Stack

- C++
- Object-Oriented Programming (OOP)
- STL

## Project Structure

- auth/ → Login system
- data/ → Data handling
- core/ → Banking operations
- ui/ → Menus
- models/ → Account structure
- utils/ → Helper functions

## How to Run

Compile:
g++ main.cpp data/DataManager.cpp ui/MainMenu.cpp ui/UserMenu.cpp auth/Auth.cpp core/AccountOperations.cpp -o main

Run:
./main

## Status

Day 2 Completed
Admin Panel Coming Next...

## Future Improvements

- Admin Panel
- Database Integration (SQL)
- GUI Interface
