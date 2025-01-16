# Bank Management System (C++)
This is a simple Bank Management System built using C++ that allows users to manage accounts, including functionalities like creating accounts, depositing and withdrawing money, displaying account details, and deleting accounts. The system stores account data in a binary file, making it efficient for handling large numbers of accounts.

## Features:
- Create Account: Allows the user to create a new bank account by providing the account number, account holder’s name, and initial balance.
- Deposit Money: Enables depositing an amount into a specified account.
- Withdraw Money: Enables withdrawing an amount from a specified account.
- Balance Inquiry: Displays the balance of a specified account.
- Delete Account: Deletes an account from the system based on the account number.
- Display All Accounts: Displays details of all accounts sorted by account number.
- Persistent Data: The system uses a binary file (accounts.dat) to store and retrieve account information.

## File Operations:
- Writing Account Data: Accounts are written to a binary file when created or updated.
- Reading Account Data: Accounts are read from the binary file for display or modification.
- Deleting an Account: Accounts are deleted from the file by rewriting the data to a temporary file, excluding the account to be deleted.

## Data Structures:
- Account Class: Contains account number, account holder's name, and balance. Includes methods for creating accounts, depositing, withdrawing, and displaying account details.
- Vector: Used to store and manage multiple accounts.

## Sorting:
- Bubble Sort: Accounts are sorted by account number before being displayed.

## How to Use:
- Clone or Download: Clone or download this repository to your local machine.
- Compile: Compile the source code using any C++ compiler (e.g., g++ or Visual Studio).
- Run: Run the executable to interact with the system through a simple text-based menu.

### Example:
- When you run the program, you will be presented with a menu like this:

### How to use:

#### ** BANK MANAGEMENT SYSTEM **
1. Create Account
2. Deposit Money
3. Withdraw Money
4. Balance Inquiry
5. Delete Account
6. Display All Accounts (Sorted)
7. Exit
Select an option (1-7): 

## Requirements:
- C++ Compiler (C++11 or later recommended)
- Basic understanding of file handling in C++

## Files:
- accounts.dat: Binary file used to store account information.
- main.cpp: Source file containing the main implementation of the Bank Management System.