#pragma once

#include <vector>
#include "Account.h" // ���������� ��������� Account

class Bank {
public:
    Bank();
    void processTransaction(int account_id, double amount, bool is_deposit);
    void addAccount(Account* account);

private:
    std::vector<Account*> accounts; // ������ ��� �������� ���������� �� ��������
};