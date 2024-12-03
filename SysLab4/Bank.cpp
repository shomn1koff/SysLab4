#include "Bank.h"
#include <iostream>

Bank::Bank() {}

void Bank::processTransaction(int account_id, double amount, bool is_deposit) {
    if (account_id < 0 || account_id >= accounts.size()) {
        std::cerr << "Invalid account ID: " << account_id << std::endl;
        return;
    }

    Account* account = accounts[account_id];
    if (is_deposit) {
        account->deposit(amount);
    }
    else {
        if (!account->withdraw(amount)) {
            std::cerr << "Insufficient funds in account ID: " << account_id << std::endl;
        }
    }
}

void Bank::addAccount(Account* account) {
    accounts.push_back(account); // Добавление аккаунта в вектор
}