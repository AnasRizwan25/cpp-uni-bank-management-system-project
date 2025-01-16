#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>  
using namespace std;

class Account {
public:
    int accountNumber;
    string accountHolderName;
    double balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cin.ignore();
        cout << "Enter Account Holder's Name: ";
        getline(cin, accountHolderName);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount() const {
        cout << "Account: " << accountNumber << "\n" << accountHolderName << "\nBalance: $" << balance << endl;
    }
};

void loadAccounts(vector<Account>& accounts) {
    ifstream inFile("accounts.txt");
    Account acc;
    while (inFile >> acc.accountNumber) {
        inFile.ignore();
        getline(inFile, acc.accountHolderName);
        inFile >> acc.balance;
        accounts.push_back(acc);
    }
}

void saveAccounts(const vector<Account>& accounts) {
    ofstream outFile("accounts.txt");
    for (const auto& acc : accounts) {
        outFile << acc.accountNumber << "\n" << acc.accountHolderName << "\n" << acc.balance << "\n";
    }
}

void displayAccount(const vector<Account>& accounts, int accNum) {
    for (const auto& acc : accounts) {
        if (acc.accountNumber == accNum) {
            acc.displayAccount();
            return;
        }
    }
    cout << "Account not found.\n";
}

void modifyAccount(vector<Account>& accounts, int accNum, double amount, bool isDeposit) {
    for (auto& acc : accounts) {
        if (acc.accountNumber == accNum) {
            acc.balance += (isDeposit ? amount : -amount);
            return;
        }
    }
    cout << "Account not found.\n";
}

void deleteAccount(vector<Account>& accounts, int accNum) {
    auto it = remove_if(accounts.begin(), accounts.end(), [accNum](const Account& acc) {
        return acc.accountNumber == accNum;
    });

    if (it != accounts.end()) {
        accounts.erase(it, accounts.end());
        cout << "Account deleted.\n";
    } else {
        cout << "Account not found.\n";
    }
}

int main() {
    vector<Account> accounts;
    loadAccounts(accounts);  

    int choice, accNum;
    double amount;

    while (true) {
        cout << "\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Display Account\n5. Delete Account\n6. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            {
                Account acc;
                acc.createAccount();
                accounts.push_back(acc);
                break;
            }
        case 2:
            cout << "Account Number: "; cin >> accNum;
            cout << "Amount: "; cin >> amount;
            modifyAccount(accounts, accNum, amount, true);
            break;
        case 3:
            cout << "Account Number: "; cin >> accNum;
            cout << "Amount: "; cin >> amount;
            modifyAccount(accounts, accNum, amount, false);
            break;
        case 4:
            cout << "Account Number: "; cin >> accNum;
            displayAccount(accounts, accNum);
            break;
        case 5:
            cout << "Account Number: "; cin >> accNum;
            deleteAccount(accounts, accNum);
            break;
        case 6:
            saveAccounts(accounts); 
            return 0;
        default:
            cout << "Invalid option.\n";
        }
    }
}