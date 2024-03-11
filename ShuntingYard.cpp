#include <iostream>
#include <string>

using namespace std;

class node {
private:
    char data;
    node* next;
public:
    node(char data) : data(data), next(nullptr) {}
    char getdata() {
        return data;
    }
    void setnext(node* newnext) {
        next = newnext;
    }
    node *getnext(void) {
        return next;
    }
};

class stack {
private:
    node* top;
public:
    stack() : top(nullptr) {}

    void push(char data) {
        node* newnode = new node(data);
        if (top == nullptr) {
            top = newnode;
        } else {
            newnode->setnext(top);
            top = newnode;
        }
    }

    char pop() {
        if (top == nullptr) {
            cout << "stack is empty" << endl;
            return;
        }
        char data = top->getdata();
        node* temp = top;
        top = top->getnext();
        delete temp;
        return data;
    }

    char peek() {
        if (top == nullptr) {
            cout << "stack is empty" << endl;
            return;
        }
        return top->getdata();
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

class queue {
private:
    node* front;
    node* rear;
public:
    queue() : front(nullptr), rear(nullptr) {}

    void enqueue(char data) {
        node* newnode = new node(data);
        if (rear == nullptr) {
            front = newnode;
            rear = newnode;
        } else {
            rear->setnext(newnode);
            rear = newnode;
        }
    }

    char dequeue() {
        if (front == nullptr) {
            cout << "queue is empty" << endl;
            return;
        }
        char data = front->getdata();
        node* temp = front;
        front = front->getnext();
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return data;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

class treenode {
private:
    char data;
    treenode *left;
    treenode *right;
public:
    treenode(char data) : data(data), left(nullptr), right(nullptr) {}

    char getData()
    {
        return data;
    }

    treenode *getLeft()
    {
        return left;
    }

    void setLeft(treenode *newleft)
    {
        left = newleft;
    }

    treenode *getRight()
    {
        return right;
    }

    void setRight(treenode *newright)
    {
        right = newright;
    }
};

// Function prototypes
string shuntingYard(string& infixExpression);
treenode* buildTree(string& postfixExpression);
void printInfix(treenode* node);
void printPrefix(treenode* node);
void printPostfix(treenode* node);

int main() {
    string infixExpression;
    cout << "Enter the mathematical expression in infix notation: ";
    getline(cin, infixExpression);

    string postfixExpression = shunting_yard(infixExpression);
    treenode* expressionTree = build_expressionTree(postfixExpression);

    string input;

    cout << "What do you want to do (infix, prefix, postfix)?" << endl;

    cin >> input;

    if (input.compare("infix") == 0) {
        cout << "Infix notation: ";
        print_infix(expressionTree);
        cout << endl;
    }
    else if (input.compare("prefix") == 0) {
        cout << "Prefix notation: ";
        print_prefix(expressionTree);
        cout << endl;
    }
    else if (input.compare("postfix") == 0) {
        cout << "Postfix notation: ";
        print_postfix(expressionTree);
        cout << endl;
    }
}

string shunting_yard(const string& infixExpression) {
    // Implement the Shunting Yard algorithm
    return "";  // Placeholder
}

treenode* build_expressionTree(const string& postfixExpression) {
    // Implement construction of expression tree
    return nullptr;  // Placeholder
}

void print_infix(treenode* node) {
    // Implement printing infix expression recursively
}

void print_prefix(treenode* node) {
    // Implement printing prefix expression recursively
}

void print_postfix(treenode* node) {
    // Implement printing postfix expression recursively
}
