#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<ctime>
using namespace std;

class BankAccount {
public:
    int accountNumber;
    string holderName;
    double balance;
    int pin;

    BankAccount() : accountNumber(0), balance(0.0), pin(0) {}

    void createAccount() {
        cout<<"Enter account number: ";
        cin>>accountNumber;
        cin.ignore();
        cout<<"Enter account holder name: ";
        getline(cin, holderName);
        cout<<"Enter initial balance: ";
        cin>>balance;
        cout<<"Set a 4-digit PIN: ";
        cin>>pin;
        logTransaction("Account opened", balance);
    }

    void display() const {
        cout<<"Account No: "<<accountNumber
             <<"\nName: "<<holderName
             <<"\nBalance: $"<<balance<<"\n";
    }

    void deposit(double amount) {
        balance += amount;
        logTransaction("Deposit", amount);
    }

    void withdraw(double amount) {
        if (amount<=balance) {
            balance-=amount;
            logTransaction("Withdrawal", amount);
        } else {
            cout<<"Insufficient funds!\n";
        }
    }

    void logTransaction(const string& type, double amount) const {
        ofstream file("transactions.txt", ios::app);

        time_t now=time(0);
        tm* ltm=localtime(&now);

        file<<"["<<1900+ltm->tm_year << "-"
            <<(ltm->tm_mon+1<10? "0": "")<<ltm->tm_mon + 1<< "-"
            <<(ltm->tm_mday<10? "0": "")<<ltm->tm_mday<< " "
            <<(ltm->tm_hour<10? "0": "")<<ltm->tm_hour<< ":"
            <<(ltm->tm_min<10? "0": "")<<ltm->tm_min<< ":"
            <<(ltm->tm_sec<10? "0": "")<<ltm->tm_sec<< "] ";

        file<<"Account: "<<accountNumber
            <<" | "<<type
            <<" | Amount: "<<amount
            <<" | New Balance: "<<balance<<"\n";

        file.close();
    }
};

bool verifyPIN(const BankAccount& acc) {
    int inputPIN;
    cout<<"Enter 4-digit PIN: ";
    cin>>inputPIN;
    return inputPIN == acc.pin;
}


void saveAccount(const BankAccount& acc) {
    ofstream file("accounts.txt", ios::app);
    file<<acc.accountNumber<<"\n"
        <<acc.holderName<<"\n"
        <<acc.balance<<"\n"
        <<acc.pin<<"\n";
    file.close();
}


vector<BankAccount> loadAccounts() {
    vector<BankAccount> accounts;
    ifstream file("accounts.txt");
    BankAccount acc;

    while (file>>acc.accountNumber) {
        file.ignore();
        getline(file, acc.holderName);
        file>>acc.balance>>acc.pin;
        file.ignore();
        accounts.push_back(acc);
    }

    file.close();
    return accounts;
}


void saveAllAccounts(const vector<BankAccount>& accounts) {
    ofstream file("accounts.txt");
    for (const auto& acc : accounts) {
        file<<acc.accountNumber<<"\n"
            <<acc.holderName<<"\n"
            <<acc.balance<<"\n"
            <<acc.pin<<"\n";
    }
    file.close();
}

BankAccount* findAccount(vector<BankAccount>& accounts, int accNum) {
    for (auto& acc : accounts) {
        if (acc.accountNumber==accNum)
            return &acc;
    }
    return nullptr;
}

void viewAllAccounts(const vector<BankAccount>& accounts) {
    for (const auto& acc : accounts) {
        cout << "\n-------------------------\n";
        acc.display();
    }
}

int main() {
    vector<BankAccount> accounts = loadAccounts();
    int choice;

    do {
        cout<<"\n--- Bank Menu ---\n"
            <<"1. Open Account\n"
            <<"2. Deposit\n"
            <<"3. Withdraw\n"
            <<"4. View Account\n"
            <<"5. Close Account\n"
            <<"6. View All Accounts\n"
            <<"7. Exit\nChoose: ";
        cin>>choice;

        if (choice == 1) {
            BankAccount newAcc;
            newAcc.createAccount();
            accounts.push_back(newAcc);
            saveAccount(newAcc);
        } else if (choice >= 2 && choice <= 5) {
            int accNum;
            cout<<"Enter account number: ";
            cin>>accNum;
            BankAccount* acc = findAccount(accounts, accNum);

            if (!acc) {
                cout<<"Account not found.\n";
                continue;
            }

            if (!verifyPIN(*acc)) {
                cout<<"Incorrect PIN.\n";
                continue;
            }

            if (choice == 2) {
                double amount;
                cout<<"Enter deposit amount: ";
                cin>>amount;
                acc->deposit(amount);
            } else if (choice == 3) {
                double amount;
                cout<<"Enter withdrawal amount: ";
                cin>>amount;
                acc->withdraw(amount);
            } else if (choice == 4) {
                acc->display();
            } else if (choice == 5) {
                accounts.erase(remove_if(accounts.begin(), accounts.end(),
                                         [accNum](BankAccount& a) { return a.accountNumber == accNum; }),
                               accounts.end());
                cout<<"Account closed.\n";
            }

            saveAllAccounts(accounts);
        } else if (choice == 6) {
            viewAllAccounts(accounts);
        }

    } while (choice != 7);

    return 0;
}
