# 💳 Bank Account Management System (C++)

A C++ console application to manage basic banking operations with PIN security and file-based data storage.

---

## 🔹 Features

- Create a new bank account with account number, name, balance, and 4-digit PIN
- Deposit and withdraw money (with balance checks)
- View individual or all accounts
- Close an account securely
- Log every transaction with date and time
- Save account data in `accounts.txt` and logs in `transactions.txt`

---

## 🔧 Technologies

- Language: C++
- Concepts: OOP (Encapsulation), File Handling, Timestamps
- Libraries: `<iostream>`, `<fstream>`, `<vector>`, `<ctime>`, `<string>`

---

## 🚀 How to Run

```bash
g++ main.cpp -o bank_system
./bank_system
