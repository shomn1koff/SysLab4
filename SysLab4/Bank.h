#pragma once

#include <vector>
#include "Account.h" // Подключаем заголовок Account

class Bank {
public:
    Bank();
    void processTransaction(int account_id, double amount, bool is_deposit);
    void addAccount(Account* account);

private:
    std::vector<Account*> accounts; // Вектор для хранения указателей на аккаунты
};