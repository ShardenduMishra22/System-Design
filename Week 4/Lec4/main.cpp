#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Component
class FileSystemItem {
public:
    virtual ~FileSystemItem() {}
    virtual void display(int indent = 0) = 0;
};

// Leaf
class File : public FileSystemItem {
    string name;
public:
    File(const string& n) : name(n) {}
    void display(int indent = 0) override {
        cout << string(indent, ' ') << name << "\n";
    }
};

// Composite
class Folder : public FileSystemItem {
    string name;
    vector<FileSystemItem*> children;
public:
    Folder(const string& n) : name(n) {}
    ~Folder() {
        for (auto c : children) delete c;
    }
    void add(FileSystemItem* item) {
        children.push_back(item);
    }
    void display(int indent = 0) override {
        cout << string(indent, ' ') << "+ " << name << "\n";
        for (auto c : children) c->display(indent + 2);
    }
};

// Client
int main() {
    Folder* root = new Folder("root");
    root->add(new File("file1.txt"));
    Folder* sub = new Folder("sub");
    sub->add(new File("subfile.txt"));
    root->add(sub);

    root->display();

    delete root;
    return 0;
}
