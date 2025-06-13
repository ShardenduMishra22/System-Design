#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// ------------------ S: Single Responsibility ------------------
class Product {
public:
    string name;
    double price;

    Product(string name, double price) : name(name), price(price) {}
};

class ShoppingCart {
private:
    vector<Product*> products;

public:
    void addProduct(Product* p) { products.push_back(p); }

    const vector<Product*>& getProducts() { return products; }

    double calculateTotal() {
        double total = 0;
        for (auto p : products) total += p->price;
        return total;
    }
};

class ShoppingCartPrinter {
public:
    void printInvoice(ShoppingCart* cart) {
        cout << "Invoice:\n";
        for (auto p : cart->getProducts()) {
            cout << p->name << " - Rs " << p->price << endl;
        }
        cout << "Total: Rs " << cart->calculateTotal() << endl;
    }
};

// ------------------ D: Dependency Inversion ------------------
class CartPersistence {
public:
    virtual void save(ShoppingCart* cart) = 0;
    virtual ~CartPersistence() = default;
};

class SQLPersistence : public CartPersistence {
public:
    void save(ShoppingCart* cart) override {
        cout << "Saving cart to SQL DB..." << endl;
    }
};

// ------------------ I & L: ISP and LSP ------------------
// ISP: split interfaces
class DepositOnlyAccount {
public:
    virtual void deposit(double amount) = 0;
    virtual ~DepositOnlyAccount() = default;
};

class WithdrawableAccount : public DepositOnlyAccount {
public:
    virtual void withdraw(double amount) = 0;
};

// LSP: valid substitution
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
            cout << "Insufficient funds in Savings!" << endl;
        }
    }
};

class FixedTermAccount : public DepositOnlyAccount {
private:
    double balance = 0;
public:
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited: " << amount << " in FixedTerm. Balance: " << balance << endl;
    }
};

// ------------------ O: Open/Closed Principle ------------------
class InvoiceFormatter {
public:
    virtual void format(ShoppingCart* cart) = 0;
    virtual ~InvoiceFormatter() = default;
};

class PlainTextFormatter : public InvoiceFormatter {
public:
    void format(ShoppingCart* cart) override {
        cout << "Plain Invoice:\n";
        for (auto p : cart->getProducts()) {
            cout << "- " << p->name << ": Rs " << p->price << endl;
        }
        cout << "Total: Rs " << cart->calculateTotal() << endl;
    }
};

class HTMLFormatter : public InvoiceFormatter {
public:
    void format(ShoppingCart* cart) override {
        cout << "<html><body><h1>Invoice</h1><ul>";
        for (auto p : cart->getProducts()) {
            cout << "<li>" << p->name << ": Rs " << p->price << "</li>";
        }
        cout << "</ul><p>Total: Rs " << cart->calculateTotal() << "</p></body></html>" << endl;
    }
};

// ------------------ Main ------------------
int main() {
    // SRP
    ShoppingCart* cart = new ShoppingCart();
    cart->addProduct(new Product("Laptop", 50000));
    cart->addProduct(new Product("Mouse", 2000));
    ShoppingCartPrinter().printInvoice(cart);

    // OCP
    InvoiceFormatter* formatter = new HTMLFormatter();
    formatter->format(cart);

    // DIP
    CartPersistence* storage = new SQLPersistence();
    storage->save(cart);

    // LSP & ISP
    vector<WithdrawableAccount*> withdrawable = {
        new SavingAccount()
    };
    vector<DepositOnlyAccount*> depositOnly = {
        new FixedTermAccount()
    };

    for (auto* acc : withdrawable) {
        acc->deposit(1000);
        acc->withdraw(500);
    }

    for (auto* acc : depositOnly) {
        acc->deposit(5000);
    }

    return 0;
}
