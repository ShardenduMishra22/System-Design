#include <iostream>
#include <mutex>
using namespace std;

// =====================================================
// 1. Basic Lazy Singleton (NOT thread-safe)
// =====================================================
class LazySingleton {
private:
    static LazySingleton* instance;
    LazySingleton() { cout << "LazySingleton Constructor\n"; }
public:
    static LazySingleton* getInstance() {
        if (!instance)
            instance = new LazySingleton();
        return instance;
    }
};
LazySingleton* LazySingleton::instance = nullptr;

// =====================================================
// 2. Eager Singleton (created at load time, thread-safe)
// =====================================================
class EagerSingleton {
private:
    static EagerSingleton* instance;
    EagerSingleton() { cout << "EagerSingleton Constructor\n"; }
public:
    static EagerSingleton* getInstance() {
        return instance;
    }
};
EagerSingleton* EagerSingleton::instance = new EagerSingleton();

// =====================================================
// 3. Thread-safe Singleton with always-lock (slow)
// =====================================================
class LockedSingleton {
private:
    static LockedSingleton* instance;
    static mutex mtx;
    LockedSingleton() { cout << "LockedSingleton Constructor\n"; }
public:
    static LockedSingleton* getInstance() {
        lock_guard<mutex> lock(mtx);
        if (!instance)
            instance = new LockedSingleton();
        return instance;
    }
};
LockedSingleton* LockedSingleton::instance = nullptr;
mutex LockedSingleton::mtx;

// =====================================================
// 4. Thread-safe Singleton (Double-Checked Locking)
// =====================================================
class DCLSingleton {
private:
    static DCLSingleton* instance;
    static mutex mtx;
    DCLSingleton() { cout << "DCLSingleton Constructor\n"; }
public:
    static DCLSingleton* getInstance() {
        if (!instance) {
            lock_guard<mutex> lock(mtx);
            if (!instance)
                instance = new DCLSingleton();
        }
        return instance;
    }
};
DCLSingleton* DCLSingleton::instance = nullptr;
mutex DCLSingleton::mtx;

// =====================================================
// 5. No Singleton (new object every time)
// =====================================================
class NoSingleton {
public:
    NoSingleton() { cout << "NoSingleton Constructor\n"; }
};

// =====================================================
// Main Demo
// =====================================================
int main() {
    cout << "\n-- Lazy Singleton --\n";
    LazySingleton* ls1 = LazySingleton::getInstance();
    LazySingleton* ls2 = LazySingleton::getInstance();
    cout << "Same instance? " << (ls1 == ls2) << "\n";

    cout << "\n-- Eager Singleton --\n";
    EagerSingleton* es1 = EagerSingleton::getInstance();
    EagerSingleton* es2 = EagerSingleton::getInstance();
    cout << "Same instance? " << (es1 == es2) << "\n";

    cout << "\n-- Locked Singleton --\n";
    LockedSingleton* lks1 = LockedSingleton::getInstance();
    LockedSingleton* lks2 = LockedSingleton::getInstance();
    cout << "Same instance? " << (lks1 == lks2) << "\n";

    cout << "\n-- DCL Singleton --\n";
    DCLSingleton* dcl1 = DCLSingleton::getInstance();
    DCLSingleton* dcl2 = DCLSingleton::getInstance();
    cout << "Same instance? " << (dcl1 == dcl2) << "\n";

    cout << "\n-- No Singleton --\n";
    NoSingleton* n1 = new NoSingleton();
    NoSingleton* n2 = new NoSingleton();
    cout << "Same instance? " << (n1 == n2) << "\n";

    return 0;
}