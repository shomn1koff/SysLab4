#include "Transaction.h"

Transaction::Transaction(int account_id, double amount, bool is_deposit)
    : account_id(account_id), amount(amount), is_deposit(is_deposit) {}

int Transaction::getAccountId() const {
    return account_id;
}

double Transaction::getAmount() const {
    return amount;
}

bool Transaction::isDeposit() const {
    return is_deposit;
}