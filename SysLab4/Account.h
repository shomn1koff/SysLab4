#pragma once

class Account {
public:
    Account(int id, double initial_balance);
    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;

private:
    int id;
    double balance;
};