#include <iostream>
#include <string>

using namespace std;

// -----------------------
// Proxy Pattern Examples
// -----------------------

// 1. Protective Proxy: Document access control
class IDocumentReader {
public:
    virtual void unlockPDF(const string& filePath, const string& password) = 0;
    virtual ~IDocumentReader() = default;
};

class RealDocumentReader : public IDocumentReader {
public:
    void unlockPDF(const string& filePath, const string& password) override {
        cout << "[RealDocumentReader] Unlocking PDF at: " << filePath << "\n";
        cout << "[RealDocumentReader] PDF unlocked successfully with password: " << password << "\n";
        cout << "[RealDocumentReader] Displaying PDF content...\n";
    }
};

class User {
public:
    string name;
    bool premiumMembership;
    User(const string& name, bool isPremium) : name(name), premiumMembership(isPremium) {}
};

class DocumentProxy : public IDocumentReader {
    RealDocumentReader* realReader;
    User* user;
public:
    DocumentProxy(User* user) : realReader(new RealDocumentReader()), user(user) {}
    void unlockPDF(const string& filePath, const string& password) override {
        if (!user->premiumMembership) {
            cout << "[DocumentProxy] Access denied for user " << user->name << ". Premium required.\n";
            return;
        }
        realReader->unlockPDF(filePath, password);
    }
    ~DocumentProxy() {
        delete realReader;
    }
};

// 2. Remote Proxy: simulating remote data fetch
class IDataService {
public:
    virtual string fetchData() = 0;
    virtual ~IDataService() = default;
};

class RealDataService : public IDataService {
public:
    RealDataService() {
        cout << "[RealDataService] Initialized (connecting to remote)\n";
    }
    string fetchData() override {
        return "[RealDataService] Data from server";
    }
};

class DataServiceProxy : public IDataService {
    RealDataService* realService;
public:
    DataServiceProxy() : realService(new RealDataService()) {}
    string fetchData() override {
        cout << "[DataServiceProxy] Forwarding request to remote service...\n";
        return realService->fetchData();
    }
    ~DataServiceProxy() {
        delete realService;
    }
};

// 3. Virtual Proxy: lazy-loading expensive resource
class IImage {
public:
    virtual void display() = 0;
    virtual ~IImage() = default;
};

class RealImage : public IImage {
    string filename;
public:
    RealImage(const string& file) : filename(file) {
        cout << "[RealImage] Loading image from disk: " << filename << "\n";
    }
    void display() override {
        cout << "[RealImage] Displaying " << filename << "\n";
    }
};

class ImageProxy : public IImage {
    RealImage* realImage;
    string filename;
public:
    ImageProxy(const string& file) : realImage(nullptr), filename(file) {}
    void display() override {
        if (!realImage) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }
    ~ImageProxy() {
        delete realImage;
    }
};

int main() {
    // Protective Proxy demo
    User* u1 = new User("Rohan", false);
    User* u2 = new User("Rashmi", true);
    cout << "== Rohan tries to unlock PDF ==\n";
    IDocumentReader* docProxy1 = new DocumentProxy(u1);
    docProxy1->unlockPDF("protected.pdf", "pwd123");
    delete docProxy1;
    cout << "\n== Rashmi tries to unlock PDF ==\n";
    IDocumentReader* docProxy2 = new DocumentProxy(u2);
    docProxy2->unlockPDF("protected.pdf", "pwd123");
    delete docProxy2;
    delete u1;
    delete u2;

    cout << "\n";

    // Remote Proxy demo
    cout << "== Fetching data via proxy ==\n";
    IDataService* dataProxy = new DataServiceProxy();
    cout << dataProxy->fetchData() << "\n";
    delete dataProxy;

    cout << "\n";

    // Virtual Proxy demo
    cout << "== Displaying image via proxy ==\n";
    IImage* imgProxy = new ImageProxy("large_photo.jpg");
    imgProxy->display();  // loads and displays
    imgProxy->display();  // displays without loading again
    delete imgProxy;

    return 0;
}
