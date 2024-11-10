#include <iostream>
#include <string>
#include "MyVector.h"

using namespace std;

struct Violation
{
    string violationType;

    Violation() : violationType("") {}
    Violation(const string& vtype) : violationType(vtype) {}
};

class Node
{
public:
    Node() : right(nullptr), left(nullptr) {}
    Node(const Violation& v, const string& carNum) : right(nullptr), left(nullptr), numberCars(carNum) { violations.push_back(v); }

    Node* getRight() const { return right; }
    Node* getLeft() const { return left; }
    string getNumberCars() { return numberCars; }

    void setRight(Node* right) { this->right = right; }
    void setLeft(Node* left) { this->left = left; }
    void setNumberCars(const string& carNum) { numberCars = carNum; }

    void pushViolation(const Violation& val);
    vector<Violation> getViolations() { return violations; }
private:
    Node* right;
    Node* left;
    string numberCars;
    vector<Violation> violations;
};

void Node::pushViolation(const Violation& val)
{
    violations.push_back(val);
}

class Tree
{
public:
    void insert(const Violation& violation, const string& numberCars);
    void DBprint() const;
    void printDataByCarNumber(const string& carNum) const;
    void printDataInRange(const string& startNum, const string& endNum) const;
private:
    Node* root;
    void DBprint(Node* cur) const;
    void insert(Node* cur, const Violation& violation, const string& numberCars);
    Node* findNodeByCarNumber(Node* cur, const string& carNum) const;
    void printDataInRange(Node* cur, const string& startNum, const string& endNum) const;
public:
    Tree() : root(nullptr) {}
};

void Tree::insert(const Violation& violation, const string& numberCars)
{
    if (root)
    {
        insert(root, violation, numberCars);
    }
    else {
        root = new Node(violation, numberCars);
    }
}

void Tree::DBprint() const
{
    if (root)
    {
        DBprint(root);
    }
}

void Tree::insert(Node* cur, const Violation& violation, const string& numberCars)
{
    if (numberCars < cur->getNumberCars())
    {
        if (cur->getLeft())
        {
            insert(cur->getLeft(), violation, numberCars);
        }
        else {
            cur->setLeft(new Node(violation, numberCars));
        }
    }
    else if (numberCars > cur->getNumberCars())
    {
        if (cur->getRight())
        {
            insert(cur->getRight(), violation, numberCars);
        }
        else {
            cur->setRight(new Node(violation, numberCars));
        }
    }
    else {
        cur->pushViolation(violation);
    }
}

void Tree::DBprint(Node* cur) const
{
    if (cur)
    {
        cout << endl;
        DBprint(cur->getLeft());
        cout << "Car number: " << cur->getNumberCars() << endl;
        cout << "Violations: ";
        for (const auto& it : cur->getViolations())
        {
            cout << it.violationType << " ";
        }
        cout << endl;
        DBprint(cur->getRight());
        cout << endl;
    }
}

void Tree::printDataByCarNumber(const string& carNum) const
{
    Node* foundNode = findNodeByCarNumber(root, carNum);
    if (foundNode)
    {
        cout << "Car number: " << foundNode->getNumberCars() << endl;
        cout << "Violations: ";
        for (const auto& it : foundNode->getViolations())
        {
            cout << it.violationType << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No data found for car number " << carNum << endl;
    }
}

Node* Tree::findNodeByCarNumber(Node* cur, const string& carNum) const
{
    if (cur == nullptr || cur->getNumberCars() == carNum)
    {
        return cur;
    }

    if (carNum < cur->getNumberCars())
    {
        return findNodeByCarNumber(cur->getLeft(), carNum);
    }
    else
    {
        return findNodeByCarNumber(cur->getRight(), carNum);
    }
}

void Tree::printDataInRange(const string& startNum, const string& endNum) const
{
    printDataInRange(root, startNum, endNum);
}

void Tree::printDataInRange(Node* cur, const string& startNum, const string& endNum) const
{
    if (cur == nullptr)
    {
        return;
    }

    if (startNum < cur->getNumberCars())
    {
        printDataInRange(cur->getLeft(), startNum, endNum);
    }

    if (startNum <= cur->getNumberCars() && endNum >= cur->getNumberCars())
    {
        cout << "Car number: " << cur->getNumberCars() << endl;
        cout << "Violations: ";
        for (const auto& it : cur->getViolations())
        {
            cout << it.violationType << " ";
        }
        cout << endl;
    }

    if (endNum > cur->getNumberCars())
    {
        printDataInRange(cur->getRight(), startNum, endNum);
    }
}

int main() {
    Tree tree;
    Violation v1("DTP");
    Violation v2("Speed");
    Violation v3("Parking");
    Violation v4("Red");
    Violation v5("Drunk");

    tree.insert(v1, "AM5555AM");
    tree.insert(v2, "AM7777AM");
    tree.insert(v3, "AM3333AM");
    tree.insert(v4, "AM7777AM");
    tree.insert(v5, "AM7777AM");

    cout << "Full Information:" << endl;
    tree.DBprint();

    cout << endl << "Print information for AM7777AM" << endl;
    tree.printDataByCarNumber("AM7777AM");

    cout << endl << "Print information from AM5555AM to AM7777AM: " << endl;
    tree.printDataInRange("AM5555AM", "AM7777AM");
}
