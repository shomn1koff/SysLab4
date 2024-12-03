#include "Account.h"

Account::Account(int id, double initial_balance) : id(id), balance(initial_balance) {}

void Account::deposit(double amount) {
    balance += amount;
}

bool Account::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

double Account::getBalance() const {
    return balance;
}