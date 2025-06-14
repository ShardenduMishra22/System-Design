#include <iostream>
using namespace std;

// ---------- Product Interfaces ----------
class Burger {
public:
    virtual void prepare() = 0;
    virtual ~Burger() {}
};

class GarlicBread {
public:
    virtual void prepare() = 0;
    virtual ~GarlicBread() {}
};

// ---------- Concrete Products ----------
class BasicBurger : public Burger {
public:
    void prepare() override { cout << "Preparing Basic Burger\n"; }
};

class PremiumBurger : public Burger {
public:
    void prepare() override { cout << "Preparing Premium Burger\n"; }
};

class BasicGarlicBread : public GarlicBread {
public:
    void prepare() override { cout << "Preparing Basic Garlic Bread\n"; }
};

// ==============================
// 1. SIMPLE FACTORY
// ==============================
class SimpleBurgerFactory {
public:
    Burger* createBurger(string type) {
        if (type == "basic") return new BasicBurger();
        if (type == "premium") return new PremiumBurger();
        return nullptr;
    }
};

// ==============================
// 2. FACTORY METHOD
// ==============================
class BurgerFactory {
public:
    virtual Burger* createBurger(string type) = 0;
};

class SinghBurgerFactory : public BurgerFactory {
public:
    Burger* createBurger(string type) override {
        if (type == "basic") return new BasicBurger();
        if (type == "premium") return new PremiumBurger();
        return nullptr;
    }
};

// ==============================
// 3. ABSTRACT FACTORY
// ==============================
class MealFactory {
public:
    virtual Burger* createBurger(string type) = 0;
    virtual GarlicBread* createGarlicBread(string type) = 0;
};

class SinghMealFactory : public MealFactory {
public:
    Burger* createBurger(string type) override {
        if (type == "basic") return new BasicBurger();
        if (type == "premium") return new PremiumBurger();
        return nullptr;
    }

    GarlicBread* createGarlicBread(string type) override {
        if (type == "basic") return new BasicGarlicBread();
        return nullptr;
    }
};

// ==============================
// MAIN – All 3 Patterns Demo
// ==============================
int main() {
    cout << "=== Simple Factory ===\n";
    SimpleBurgerFactory simple;
    Burger* b1 = simple.createBurger("premium");
    b1->prepare();

    cout << "\n=== Factory Method ===\n";
    BurgerFactory* methodFactory = new SinghBurgerFactory();
    Burger* b2 = methodFactory->createBurger("basic");
    b2->prepare();

    cout << "\n=== Abstract Factory ===\n";
    MealFactory* absFactory = new SinghMealFactory();
    Burger* b3 = absFactory->createBurger("basic");
    GarlicBread* g1 = absFactory->createGarlicBread("basic");
    b3->prepare();
    g1->prepare();

    return 0;
}
