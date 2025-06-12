#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// Interfaces
class DepositOnlyAccount {
public:
    virtual void deposit(double amount) = 0;
    virtual ~DepositOnlyAccount() = default;
};

class WithdrawableAccount : public DepositOnlyAccount {
public:
    virtual void withdraw(double amount) = 0;
};

// Savings
class SavingAccount : public WithdrawableAccount {
private:
    double balance = 0;
public:
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited: " << amount << " in Savings. Balance: " << balance << endl;
    }
    void withdraw(double amount) override {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from Savings. Balance: " << balance << endl;
        } else {
            cout << "Insufficient funds in Savings!\n";
        }
    }
};

// Current
class CurrentAccount : public WithdrawableAccount {
private:
    double balance = 0;
public:
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited: " << amount << " in Current. Balance: " << balance << endl;
    }
    void withdraw(double amount) override {
        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from Current. Balance: " << balance << endl;
        } else {
            cout << "Insufficient funds in Current!\n";
        }
    }
};

// Fixed Term
class FixedTermAccount : public DepositOnlyAccount {
private:
    double balance = 0;
public:
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited: " << amount << " in FixedTerm. Balance: " << balance << endl;
    }
};

// Client
class BankClient {
private:
    vector<WithdrawableAccount*> withdrawable;
    vector<DepositOnlyAccount*> depositOnly;

public:
    BankClient(vector<WithdrawableAccount*> w, vector<DepositOnlyAccount*> d)
        : withdrawable(w), depositOnly(d) {}

    void processTransactions() {
        for (auto* acc : withdrawable) {
            acc->deposit(1000);
            acc->withdraw(500);
        }
        for (auto* acc : depositOnly) {
            acc->deposit(5000);
        }
    }
};

int main() {
    vector<WithdrawableAccount*> withdrawableAccounts = {
        new SavingAccount(),
        new CurrentAccount()
    };

    vector<DepositOnlyAccount*> depositOnlyAccounts = {
        new FixedTermAccount()
    };

    BankClient* client = new BankClient(withdrawableAccounts, depositOnlyAccounts);
    client->processTransactions();

    return 0;
}
