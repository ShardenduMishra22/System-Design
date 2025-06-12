#include <iostream>
using namespace std;

class Car {
public:
    virtual void accelerate() = 0;
    virtual void accelerate(int speed) = 0;
    virtual ~Car() {}
};

class ManualCar : public Car {
public:
    void accelerate() override {
        cout << "ManualCar: Accelerate by 20\n";
    }

    void accelerate(int speed) override {
        cout << "ManualCar: Accelerate by " << speed << "\n";
    }
};

int main() {
    Car* car = new ManualCar();

    car->accelerate();
    car->accelerate(50);

    delete car;
    return 0;
}
