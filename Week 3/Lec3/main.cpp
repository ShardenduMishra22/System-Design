#include <iostream>
#include <string>

using namespace std;

// Component Interface: defines a common interface for Mario1 and all power-up decorators.
class Character {
public:
    virtual string getAbilities() const = 0;
    virtual ~Character() {}  // Virtual destructor
};

// Concrete Component: Basic Mario1 character with no power-ups.
class Mario1 : public Character {
public:
    string getAbilities() const override {
        return "Mario1";
    }
};

// Abstract Decorator: CharacterDecorator "is-a" Charatcer and "has-a" Character.
class CharacterDecorator : public Character {
protected:
    Character* character;  // Wrapped component
public:
    CharacterDecorator(Character* c){
        this->character = c;
    }

};

// Concrete Decorator: Height-Increasing Power-Up.
class HeightUp : public CharacterDecorator {
public:
    HeightUp(Character* c) : CharacterDecorator(c) { }
    
    string getAbilities() const override {
        return character->getAbilities() + " with HeightUp";
    }
    
};

// Concrete Decorator: Gun Shooting Power-Up.
class GunPowerUp : public CharacterDecorator {
public:
    GunPowerUp(Character* c) : CharacterDecorator(c) { }
    
    string getAbilities() const override {
        return character->getAbilities() + " with Gun";
    }
};

// Concrete Decorator: Star Power-Up (temporary ability).
class StarPowerUp : public CharacterDecorator {
public:
    StarPowerUp(Character* c) : CharacterDecorator(c) { }
    
    string getAbilities() const override {
        return character->getAbilities() + " with Star Power (Limited Time)";
    }
    
    ~StarPowerUp() {
        cout << "Destroying StarPowerUp Decorator" << endl;
    }
};

int main() {
    // is a charectersticks
    Character* mario2 = new HeightUp(new Mario1());

    // has a charectersticks
    Character* mario1 = new Mario1();
    cout << "Basic Character: " << mario1->getAbilities() << endl;

    // Decorate Mario1 with a HeightUp power-up.
    mario1 = new HeightUp(mario1);
    cout << "After HeightUp: " << mario1->getAbilities() << endl;

    // Decorate Mario1 further with a GunPowerUp.
    mario1 = new GunPowerUp(mario1);
    cout << "After GunPowerUp: " << mario1->getAbilities() << endl;

    // Finally, add a StarPowerUp decoration.
    mario1 = new StarPowerUp(mario1);
    cout << "After StarPowerUp: " << mario1->getAbilities() << endl;

    delete mario1;

    return 0;
}