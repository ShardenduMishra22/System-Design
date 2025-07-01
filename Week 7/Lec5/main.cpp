#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// Forward declaration
class User;

// Mediator Interface
class ChatRoom {
public:
    virtual void registerUser(User* user) = 0;
    virtual void sendMessage(const std::string& message, User* sender) = 0;
    virtual ~ChatRoom() = default;
};

// Abstract Colleague
class User {
protected:
    std::string name;
    ChatRoom* chatRoom;

public:
    User(const std::string& name) : name(name), chatRoom(nullptr) {}
    void setChatRoom(ChatRoom* room) { chatRoom = room; }
    std::string getName() const { return name; }

    virtual void receive(const std::string& message, const std::string& sender) = 0;
    virtual void send(const std::string& message) {
        if (chatRoom)
            chatRoom->sendMessage(message, this);
    }

    virtual ~User() = default;
};

// Concrete Colleague
class ConcreteUser : public User {
public:
    ConcreteUser(const std::string& name) : User(name) {}

    void receive(const std::string& message, const std::string& sender) override {
        std::cout << "[" << name << "'s screen] " << sender << ": " << message << "\n";
    }
};

// Concrete Mediator
class ConcreteChatRoom : public ChatRoom {
private:
    std::vector<User*> users;

public:
    void registerUser(User* user) override {
        users.push_back(user);
        user->setChatRoom(this);
    }

    void sendMessage(const std::string& message, User* sender) override {
        for (User* user : users) {
            if (user != sender)
                user->receive(message, sender->getName());
        }
    }
};

// Main
int main() {
    ConcreteChatRoom chatRoom;

    ConcreteUser user1("Alice");
    ConcreteUser user2("Bob");
    ConcreteUser user3("Charlie");

    chatRoom.registerUser(&user1);
    chatRoom.registerUser(&user2);
    chatRoom.registerUser(&user3);

    user1.send("Hello everyone!");
    user2.send("Hi Alice!");
    user3.send("Hey folks!");

    return 0;
}
