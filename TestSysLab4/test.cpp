#include "pch.h" // ���������, ��� � ��� ���� pch.h, ���� ����������� �������������� ���������������� ���������
#include "C:\Users\shomnikovav\source\repos\SysLab4\SysLab4\Bank.h"
#include "C:\Users\shomnikovav\source\repos\SysLab4\SysLab4\Account.h"
#include "C:\Users\shomnikovav\source\repos\SysLab4\SysLab4\Transaction.h"
#include "C:\Users\shomnikovav\source\repos\SysLab4\SysLab4\Bank.cpp"
#include "C:\Users\shomnikovav\source\repos\SysLab4\SysLab4\Account.cpp"
#include "C:\Users\shomnikovav\source\repos\SysLab4\SysLab4\Transaction.cpp"


namespace BankTest {
    void performTransaction(Bank* bank, Transaction* transaction) {
        bank->processTransaction(transaction->getAccountId(), transaction->getAmount(), transaction->isDeposit());
    }

    // ���� 1: �������� ���������� ������� ��� ��������
    TEST(AccountDepositTest, DepositIncreasesBalance) {
        Bank bank;
        Account* account = new Account(0, 1000.0);
        bank.addAccount(account);

        performTransaction(&bank, new Transaction(0, 200.0, true)); // ������� 200
        EXPECT_EQ(account->getBalance(), 1200.0); // �������� ��������� �������

        delete account;
    }

    // ���� 2: �������� ���������� ������� ��� ������ �������
    TEST(AccountWithdrawTest, WithdrawDecreasesBalance) {
        Bank bank;
        Account* account = new Account(0, 1000.0);
        bank.addAccount(account);

        performTransaction(&bank, new Transaction(0, 200.0, false)); // ����� 200
        EXPECT_EQ(account->getBalance(), 800.0); // �������� ��������� �������

        delete account;
    }


    // ���� 3: ������� ������� ����� ����� �������
    TEST(BankTransferTest, TransferBetweenAccounts) {
        Bank bank;
        Account* account1 = new Account(0, 1000.0);
        Account* account2 = new Account(1, 500.0);
        bank.addAccount(account1);
        bank.addAccount(account2);

        performTransaction(&bank, new Transaction(0, 200.0, false)); // ����� 200 �� account1
        performTransaction(&bank, new Transaction(1, 200.0, true)); // ������� 200 � account2

        EXPECT_EQ(account1->getBalance(), 800.0); // �������� ������� account1
        EXPECT_EQ(account2->getBalance(), 700.0); // �������� ������� account2

        delete account1;
        delete account2;
    }

    // ���� 4: �������� ���������� �������� �� ����� �����
    TEST(MultipleTransactionsTest, MultipleDepositsAndWithdrawals) {
        Bank bank;
        Account* account = new Account(0, 1000.0);
        bank.addAccount(account);

        performTransaction(&bank, new Transaction(0, 300.0, true)); // ������� 300
        performTransaction(&bank, new Transaction(0, 200.0, true)); // ������� 200
        performTransaction(&bank, new Transaction(0, 500.0, false)); // ����� 500
        performTransaction(&bank, new Transaction(0, 300.0, false)); // ����� 300
        performTransaction(&bank, new Transaction(0, 100.0, false)); // ������� ������� 100 � ���������� �������

        EXPECT_EQ(account->getBalance(), 600.0); // �������� ��������� �������

        delete account;
    }

    // ���� 5: �������� ���������� ������� �����
    TEST(AccountInitialBalanceTest, InitialBalanceIsSetCorrectly) {
        Account account(0, 500.0);
        EXPECT_EQ(account.getBalance(), 500.0); // �������� ���������� �������
    }

    // ���� 6: �������� ����������� � ���������� ���������
    TEST(AccountMultipleDepositsTest, MultipleDepositsIncreaseBalance) {
        Bank bank;
        Account* account = new Account(0, 0.0);
        bank.addAccount(account);

        performTransaction(&bank, new Transaction(0, 100.0, true)); // ������� 100
        performTransaction(&bank, new Transaction(0, 150.0, true)); // ������� 150
        EXPECT_EQ(account->getBalance(), 250.0); // �������� ������� ����� ���������

        delete account;
    }

    // ���� 7: �������� ����������� ���������� ������� ��� ���������� �������
    TEST(AccountMultipleWithdrawalsTest, MultipleWithdrawalsDecreaseBalance) {
        Bank bank;
        Account* account = new Account(0, 1000.0);
        bank.addAccount(account);

        performTransaction(&bank, new Transaction(0, 100.0, false)); // ����� 100
        performTransaction(&bank, new Transaction(0, 300.0, false)); // ����� 300
        EXPECT_EQ(account->getBalance(), 600.0); // �������� ������� ����� �������

        delete account;
    }



    // ���� 8: �������� ���������� ������������� ������ � ���� �� ������� Transaction
    TEST(TransactionReuseTest, ReusingSameTransaction) {
        Bank bank;
        Account* account = new Account(0, 1000.0);
        bank.addAccount(account);

        Transaction transaction(0, 200.0, true);
        performTransaction(&bank, &transaction); // ������� 200

        EXPECT_EQ(account->getBalance(), 1200.0); // �������� ���������� ����� ������� �������������

        transaction = Transaction(0, 150.0, false); // ��������� �� ������ ��� ����������
        performTransaction(&bank, &transaction); // ����� 150

        EXPECT_EQ(account->getBalance(), 1050.0); // �������� ���������� ����� ������� �������������

        delete account;

    }

    // ���������� ���� 1: ������� � ������������� ������
    TEST(AccountDepositTest, DepositNegativeAmount) {
        Bank bank;
        Account* account = new Account(0, 300.0);
        bank.addAccount(account);

        account->deposit(-100.0); // ������� -100
        EXPECT_EQ(account->getBalance(), 300.0); // ��������, ��� ������ ������� �������

        delete account;
    }

    // ���������� ���� 2: ������� ������ ������� ������, ��� ������
    TEST(AccountWithdrawTest, WithdrawMoreThanBalance) {
        Bank bank;
        Account* account = new Account(0, 300.0);
        bank.addAccount(account);

        bool result = account->withdraw(500.0); // ������� ������� 500
        EXPECT_EQ(result, false); // �������, ��� ����� �� ��� ��������
        EXPECT_EQ(account->getBalance(), 300.0); // ��������, ��� ������ �� ���������

        delete account;
    }

    // ���������� ���� 3: ������� ������� �������� �� ��������������� �����
    TEST(BankInvalidAccountTest, WithdrawFromNonexistentAccount) {
        Bank bank;
        Account* account = new Account(0, 500.0);
        bank.addAccount(account);

        double initialBalance = account->getBalance(); // ��������� ������

        // ������� ������� ���������� �� ������������� ID
        bank.processTransaction(1, 100.0, false); // ������� ������ � ������������ ������� �����

        EXPECT_EQ(account->getBalance(), initialBalance); // ������ �� ������ ����������

        delete account;
    }



    // ���������� ���� 4: ����� ������������� �����
    TEST(AccountWithdrawTest, NegativeWithdrawAmount) {
        Bank bank;
        Account* account = new Account(0, 500.0);
        bank.addAccount(account);

        bool result = account->withdraw(-200.0); // ������� ������� -200
        EXPECT_EQ(result, false); // �������, ��� ����� �� ��� ��������
        EXPECT_EQ(account->getBalance(), 500.0); // ��������, ��� ������ �� ���������

        delete account;
    }
}