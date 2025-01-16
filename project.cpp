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
    Account() : accountNumber(0), balance(0.0) {}

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

    // Function to return account holder's name
    string getAccountHolderName() const {
        return accountHolderName;
    }

    // Serialization: Function to write account data to file
    void writeToFile(ofstream& outFile) const {
        int nameLength = accountHolderName.length();
        outFile.write(reinterpret_cast<const char*>(&accountNumber), sizeof(accountNumber));
        outFile.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        outFile.write(accountHolderName.c_str(), nameLength);
        outFile.write(reinterpret_cast<const char*>(&balance), sizeof(balance));
    }

    // Deserialization: Function to read account data from file
    void readFromFile(ifstream& inFile) {
        int nameLength;
        inFile.read(reinterpret_cast<char*>(&accountNumber), sizeof(accountNumber));
        inFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        
        char* nameBuffer = new char[nameLength + 1];
        inFile.read(nameBuffer, nameLength);
        nameBuffer[nameLength] = '\0';  // Null-terminate the string
        accountHolderName = string(nameBuffer);
        delete[] nameBuffer;

        inFile.read(reinterpret_cast<char*>(&balance), sizeof(balance));
    }
};

// Function to write account data to file
void writeAccount(const Account& account) {
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }
    account.writeToFile(outFile);
    outFile.close();
}

// Function to read all accounts from the file into a vector
vector<Account> readAccounts() {
    vector<Account> accounts;
    Account account;
    ifstream inFile("accounts.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!\n";
        return accounts;
    }
    while (true) {
        account.readFromFile(inFile);
        if (inFile.eof()) {
            break;  // Stop reading if EOF is reached
        }
        if (inFile) {  // Only add to the vector if reading was successful
            accounts.push_back(account);
        }
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
    if (accounts.empty()) {
        cout << "No accounts available.\n";
        return;
    }

    // Displaying all accounts in sorted order
    for (const auto& account : accounts) {
        account.displayAccount();
    }
}

// Function to display account details by account number
void displayAccount(int accNum) {
    Account account;
    bool found = false;
    ifstream inFile("accounts.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!\n";
        return;
    }
    while (inFile) {
        account.readFromFile(inFile);
        if (inFile && account.getAccountNumber() == accNum) {
            account.displayAccount();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        cout << "Account not found!\n";
    }
}

// Function to deposit money into an account
void depositMoney(int accNum, double amount) {
    vector<Account> accounts = readAccounts();
    bool found = false;
    for (auto& account : accounts) {
        if (account.getAccountNumber() == accNum) {
            account.deposit(amount);
            found = true;
            break;
        }
    }

    if (found) {
        // Write modified accounts back to the file
        ofstream outFile("accounts.dat", ios::binary | ios::trunc);  // Clear file and rewrite
        for (const auto& account : accounts) {
            account.writeToFile(outFile);
        }
        cout << "Deposit successful.\n";
    } else {
        cout << "Account not found!\n";
    }
}

// Function to withdraw money from an account
void withdrawMoney(int accNum, double amount) {
    vector<Account> accounts = readAccounts();
    bool found = false;
    for (auto& account : accounts) {
        if (account.getAccountNumber() == accNum) {
            account.withdraw(amount);
            found = true;
            break;
        }
    }

    if (found) {
        // Write modified accounts back to the file
        ofstream outFile("accounts.dat", ios::binary | ios::trunc);  // Clear file and rewrite
        for (const auto& account : accounts) {
            account.writeToFile(outFile);
        }
        cout << "Withdrawal successful.\n";
    } else {
        cout << "Account not found!\n";
    }
}

// Function to delete an account
void deleteAccount(int accNum) {
    vector<Account> accounts = readAccounts();
    bool found = false;

    // Remove the account from the vector
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getAccountNumber() == accNum) {
            accounts.erase(it);
            found = true;
            break;
        }
    }

    if (found) {
        // Re-write all remaining accounts back to the file
        ofstream outFile("accounts.dat", ios::binary | ios::trunc);  // Clear file and rewrite
        for (const auto& account : accounts) {
            account.writeToFile(outFile);
        }
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
