#pragma once

class Transaction {
public:
    Transaction(int account_id, double amount, bool is_deposit);
    int getAccountId() const;
    double getAmount() const;
    bool isDeposit() const;

private:
    int account_id;
    double amount;
    bool is_deposit;
};