# Bank Management System
This project is a simple Bank Management System that allows the creation, management, and deletion of bank accounts. The system is implemented in C++ and performs basic banking operations such as:

## Creating an account
- Depositing money
- Withdrawing money
- Checking balance
- Deleting an account
- The data for each account is stored in a binary file, and all the operations are done using file handling.

# Features:
- Create Account: Allows the user to create a new account by entering an account number, account holder's name, and initial balance.
- Deposit Money: Allows the user to deposit a specified amount of money into their account.
- Withdraw Money: Allows the user to withdraw a specified amount of money from their account, checking for sufficient balance.
- Balance Inquiry: Displays the details of an account, including the account number, holder's name, and balance.
- Delete Account: Deletes an account by its account number and removes it from the file storage.

## How It Works:
- Account Class: This class defines a bank account with private variables like account number, holder's name, and balance. It contains methods to deposit, withdraw, display details, and manipulate account information.

- File Handling: All account details are saved in a binary file (accounts.dat) so that the data is persistent even after the program exits. Accounts are added, updated, or deleted based on user actions.

- Operations: Each banking operation (create, deposit, withdraw, balance check, delete) is managed through user input and file read/write operations.

## Files Used:

- accounts.dat: This file stores the binary data of all the accounts.
- temp.dat: This temporary file is used for deleting accounts and managing data changes.