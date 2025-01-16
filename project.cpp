#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    Account() {}

    // Function to create a new account
    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Account Holder's Name: ";
        cin.ignore();
        getline(cin, accountHolderName);
        cout << "Enter Initial Balance: ";
        cin >> balance;
        cout << "\nAccount created successfully!\n";
    }

    // Function to display account details
    void displayAccount() const {
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    // Function to deposit an amount into the account
    void deposit(double amount) {
        balance += amount;
        cout << "$" << amount << " has been deposited. New balance: $" << balance << endl;
    }

    // Function to withdraw an amount from the account
    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            cout << "$" << amount << " has been withdrawn. New balance: $" << balance << endl;
        }
    }

    // Function to return account number
    int getAccountNumber() const {
        return accountNumber;
    }

    // Function to return balance
    double getBalance() const {
        return balance;
    }

    // Function to set account details from a binary file
    void setAccountDetails(int accNum, string holderName, double accBalance) {
        accountNumber = accNum;
        accountHolderName = holderName;
        balance = accBalance;
    }

    // Function to get account details as a string
    string getAccountDetails() const {
        return "Account Number: " + to_string(accountNumber) + ", " +
               "Account Holder: " + accountHolderName + ", " +
               "Balance: $" + to_string(balance);
    }
};

// Function to write account data to file
void writeAccount(Account& account) {
    ofstream outFile;
    outFile.open("accounts.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char*>(&account), sizeof(Account));
    outFile.close();
}

// Function to read all accounts from the file into a vector
vector<Account> readAccounts() {
    vector<Account> accounts;
    Account account;
    ifstream inFile;
    inFile.open("accounts.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!\n";
        return accounts;
    }
    while (inFile.read(reinterpret_cast<char*>(&account), sizeof(Account))) {
        accounts.push_back(account);
    }
    inFile.close();
    return accounts;
}

// Bubble sort function to sort accounts based on account number
void bubbleSort(vector<Account>& accounts) {
    for (size_t i = 0; i < accounts.size() - 1; ++i) {
        for (size_t j = 0; j < accounts.size() - 1 - i; ++j) {
            if (accounts[j].getAccountNumber() > accounts[j + 1].getAccountNumber()) {
                swap(accounts[j], accounts[j + 1]);
            }
        }
    }
}

// Function to display all accounts
void displayAllAccounts(const vector<Account>& accounts) {
    for (const auto& account : accounts) {
        account.displayAccount();
    }
}

// Function to display account details by account number
void displayAccount(int accNum) {
    Account account;
    bool found = false;
    ifstream inFile;
    inFile.open("accounts.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!\n";
        return;
    }
    while (inFile.read(reinterpret_cast<char*>(&account), sizeof(Account))) {
        if (account.getAccountNumber() == accNum) {
            account.displayAccount();
            found = true;
        }
    }
    inFile.close();
    if (!found) {
        cout << "Account not found!\n";
    }
}

// Function to deposit money into an account
void depositMoney(int accNum, double amount) {
    Account account;
    fstream file;
    bool found = false;
    file.open("accounts.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "File could not be opened!\n";
        return;
    }
    while (!file.eof() && found == false) {
        file.read(reinterpret_cast<char*>(&account), sizeof(Account));
        if (account.getAccountNumber() == accNum) {
            account.deposit(amount);
            int pos = (-1) * static_cast<int>(sizeof(Account));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&account), sizeof(Account));
            found = true;
        }
    }
    file.close();
    if (!found) {
        cout << "Account not found!\n";
    }
}

// Function to withdraw money from an account
void withdrawMoney(int accNum, double amount) {
    Account account;
    fstream file;
    bool found = false;
    file.open("accounts.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "File could not be opened!\n";
        return;
    }
    while (!file.eof() && found == false) {
        file.read(reinterpret_cast<char*>(&account), sizeof(Account));
        if (account.getAccountNumber() == accNum) {
            account.withdraw(amount);
            int pos = (-1) * static_cast<int>(sizeof(Account));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&account), sizeof(Account));
            found = true;
        }
    }
    file.close();
    if (!found) {
        cout << "Account not found!\n";
    }
}

// Function to delete an account
void deleteAccount(int accNum) {
    Account account;
    ifstream inFile;
    ofstream outFile;
    inFile.open("accounts.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!\n";
        return;
    }
    outFile.open("temp.dat", ios::binary);
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&account), sizeof(Account))) {
        if (account.getAccountNumber() != accNum) {
            outFile.write(reinterpret_cast<char*>(&account), sizeof(Account));
        } else {
            found = true;
        }
    }
    inFile.close();
    outFile.close();
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");
    if (found) {
        cout << "Account deleted successfully!\n";
    } else {
        cout << "Account not found!\n";
    }
}

int main() {
    int choice, accNum;
    double amount;
    Account account;

    do {
        cout << "\n\n** BANK MANAGEMENT SYSTEM **\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Balance Inquiry\n";
        cout << "5. Delete Account\n";
        cout << "6. Display All Accounts (Sorted)\n";
        cout << "7. Exit\n";
        cout << "Select an option (1-7): ";
        cin >> choice;

        switch (choice) {
        case 1:
            account.createAccount();
            writeAccount(account);
            break;
        case 2:
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            depositMoney(accNum, amount);
            break;
        case 3:
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;
            withdrawMoney(accNum, amount);
            break;
        case 4:
            cout << "Enter Account Number: ";
            cin >> accNum;
            displayAccount(accNum);
            break;
        case 5:
            cout << "Enter Account Number: ";
            cin >> accNum;
            deleteAccount(accNum);
            break;
        case 6: {
            vector<Account> accounts = readAccounts();
            bubbleSort(accounts);  // Sort the accounts by account number
            displayAllAccounts(accounts);  // Display sorted accounts
            break;
        }
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}