#include "pch.h" // Убедитесь, что у вас есть pch.h, если используете предварительно скомпилированные заголовки
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

    // Тест 1: Проверка увеличения баланса при депозите
    TEST(AccountDepositTest, DepositIncreasesBalance) {
        Bank bank;
        Account* account = new Account(0, 1000.0);
        bank.addAccount(account);

        performTransaction(&bank, new Transaction(0, 200.0, true)); // Депозит 200
        EXPECT_EQ(account->getBalance(), 1200.0); // Проверка итогового баланса

        delete account;
    }

    // Тест 2: Проверка уменьшения баланса при выводе средств
    TEST(AccountWithdrawTest, WithdrawDecreasesBalance) {
        Bank bank;
        Account* account = new Account(0, 1000.0);
        bank.addAccount(account);

        performTransaction(&bank, new Transaction(0, 200.0, false)); // Вывод 200
        EXPECT_EQ(account->getBalance(), 800.0); // Проверка итогового баланса

        delete account;
    }


    // Тест 3: Перевод средств между двумя счетами
    TEST(BankTransferTest, TransferBetweenAccounts) {
        Bank bank;
        Account* account1 = new Account(0, 1000.0);
        Account* account2 = new Account(1, 500.0);
        bank.addAccount(account1);
        bank.addAccount(account2);

        performTransaction(&bank, new Transaction(0, 200.0, false)); // Вывод 200 из account1
        performTransaction(&bank, new Transaction(1, 200.0, true)); // Депозит 200 в account2

        EXPECT_EQ(account1->getBalance(), 800.0); // Проверка остатка account1
        EXPECT_EQ(account2->getBalance(), 700.0); // Проверка остатка account2

        delete account1;
        delete account2;
    }

    // Тест 4: Проверка нескольких операций на одном счете
    TEST(MultipleTransactionsTest, MultipleDepositsAndWithdrawals) {
        Bank bank;
        Account* account = new Account(0, 1000.0);
        bank.addAccount(account);

        performTransaction(&bank, new Transaction(0, 300.0, true)); // Депозит 300
        performTransaction(&bank, new Transaction(0, 200.0, true)); // Депозит 200
        performTransaction(&bank, new Transaction(0, 500.0, false)); // Вывод 500
        performTransaction(&bank, new Transaction(0, 300.0, false)); // Вывод 300
        performTransaction(&bank, new Transaction(0, 100.0, false)); // Попытка вывести 100 — недостаток средств

        EXPECT_EQ(account->getBalance(), 600.0); // Проверка итогового баланса

        delete account;
    }

    // Тест 5: Проверка начального баланса счета
    TEST(AccountInitialBalanceTest, InitialBalanceIsSetCorrectly) {
        Account account(0, 500.0);
        EXPECT_EQ(account.getBalance(), 500.0); // Проверка начального баланса
    }

    // Тест 6: Проверка способности к нескольким депозитам
    TEST(AccountMultipleDepositsTest, MultipleDepositsIncreaseBalance) {
        Bank bank;
        Account* account = new Account(0, 0.0);
        bank.addAccount(account);

        performTransaction(&bank, new Transaction(0, 100.0, true)); // Депозит 100
        performTransaction(&bank, new Transaction(0, 150.0, true)); // Депозит 150
        EXPECT_EQ(account->getBalance(), 250.0); // Проверка баланса после депозитов

        delete account;
    }

    // Тест 7: Проверка корректного уменьшения баланса при нескольких выводах
    TEST(AccountMultipleWithdrawalsTest, MultipleWithdrawalsDecreaseBalance) {
        Bank bank;
        Account* account = new Account(0, 1000.0);
        bank.addAccount(account);

        performTransaction(&bank, new Transaction(0, 100.0, false)); // Вывод 100
        performTransaction(&bank, new Transaction(0, 300.0, false)); // Вывод 300
        EXPECT_EQ(account->getBalance(), 600.0); // Проверка баланса после выводов

        delete account;
    }



    // Тест 8: Проверка повторного использования одного и того же объекта Transaction
    TEST(TransactionReuseTest, ReusingSameTransaction) {
        Bank bank;
        Account* account = new Account(0, 1000.0);
        bank.addAccount(account);

        Transaction transaction(0, 200.0, true);
        performTransaction(&bank, &transaction); // Депозит 200

        EXPECT_EQ(account->getBalance(), 1200.0); // Проверка результата после первого использования

        transaction = Transaction(0, 150.0, false); // Изменение на другой тип транзакции
        performTransaction(&bank, &transaction); // Вывод 150

        EXPECT_EQ(account->getBalance(), 1050.0); // Проверка результата после второго использования

        delete account;

    }

    // Негативный тест 1: Депозит с отрицательной суммой
    TEST(AccountDepositTest, DepositNegativeAmount) {
        Bank bank;
        Account* account = new Account(0, 300.0);
        bank.addAccount(account);

        account->deposit(-100.0); // Депозит -100
        EXPECT_EQ(account->getBalance(), 300.0); // Проверка, что баланс остался прежним

        delete account;
    }

    // Негативный тест 2: Попытка вывода средств больше, чем баланс
    TEST(AccountWithdrawTest, WithdrawMoreThanBalance) {
        Bank bank;
        Account* account = new Account(0, 300.0);
        bank.addAccount(account);

        bool result = account->withdraw(500.0); // Попытка вывести 500
        EXPECT_EQ(result, false); // Ожидаем, что вывод не был успешным
        EXPECT_EQ(account->getBalance(), 300.0); // Проверка, что баланс не изменился

        delete account;
    }

    // Негативный тест 3: Попытка вывести средства из несуществующего счета
    TEST(BankInvalidAccountTest, WithdrawFromNonexistentAccount) {
        Bank bank;
        Account* account = new Account(0, 500.0);
        bank.addAccount(account);

        double initialBalance = account->getBalance(); // Начальный баланс

        // Попытка создать транзакцию по недопустимому ID
        bank.processTransaction(1, 100.0, false); // Попытка вывода с недопустимым номером счета

        EXPECT_EQ(account->getBalance(), initialBalance); // Баланс не должен измениться

        delete account;
    }



    // Негативный тест 4: Вывод отрицательной суммы
    TEST(AccountWithdrawTest, NegativeWithdrawAmount) {
        Bank bank;
        Account* account = new Account(0, 500.0);
        bank.addAccount(account);

        bool result = account->withdraw(-200.0); // Попытка вывести -200
        EXPECT_EQ(result, false); // Ожидаем, что вывод не был успешным
        EXPECT_EQ(account->getBalance(), 500.0); // Проверка, что баланс не изменился

        delete account;
    }
}