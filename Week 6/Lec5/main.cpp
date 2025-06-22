#include <iostream>
#include <unordered_map>
#include <memory>
using namespace std;

class AsteroidType {
public:
    string texture;
    string model;

    AsteroidType(const string& texture, const string& model)
        : texture(texture), model(model) {}
    
    void displayType() const {
        cout << "Type: [Texture: " << texture << ", Model: " << model << "]\n";
    }
};

// Flyweight Factory
class AsteroidTypeFactory {
private:
    unordered_map<string, shared_ptr<AsteroidType>> types;

public:
    shared_ptr<AsteroidType> getType(const string& texture, const string& model) {
        string key = texture + "_" + model;
        if (types.find(key) == types.end()) {
            types[key] = make_shared<AsteroidType>(texture, model);
        }
        return types[key];
    }
};

// Context: Extrinsic state
class Asteroid {
private:
    int x, y, z;
    shared_ptr<AsteroidType> type;

public:
    Asteroid(int x, int y, int z, shared_ptr<AsteroidType> type)
        : x(x), y(y), z(z), type(type) {}

    void render() const {
        cout << "Asteroid at (" << x << "," << y << "," << z << ") ";
        type->displayType();
    }
};

// Usage
int main() {
    AsteroidTypeFactory factory;

    Asteroid a1(10, 20, 30, factory.getType("rocky", "model1"));
    Asteroid a2(15, 25, 35, factory.getType("rocky", "model1"));
    Asteroid a3(5, 10, 20, factory.getType("icy", "model2"));

    a1.render();
    a2.render();
    a3.render();

    return 0;
}
