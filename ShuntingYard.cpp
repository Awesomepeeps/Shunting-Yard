#include <iostream>
#include <string>
#include <cctype>

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
            return '\0';
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
            return '\0';
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
            return '\0';
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
int precedence(char op);

int main() {
    string infixExpression;
    cout << "Enter the mathematical expression in infix notation: ";
    getline(cin, infixExpression);

    string postfixExpression = shuntingYard(infixExpression);
    treenode* expressionTree = buildTree(postfixExpression);

    string input;

    cout << "What do you want to do (infix, prefix, postfix)?" << endl;

    cin >> input;

    if (input.compare("infix") == 0) {
        cout << "Infix notation: ";
        printInfix(expressionTree);
        cout << endl;
    }
    else if (input.compare("prefix") == 0) {
        cout << "Prefix notation: ";
        printPrefix(expressionTree);
        cout << endl;
    }
    else if (input.compare("postfix") == 0) {
        cout << "Postfix notation: ";
        printPostfix(expressionTree);
        cout << endl;
    }
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^')
        return 3;
    else
        return -1; // Invalid operator
}

string shuntingYard(string& infixExpression) {
    string postfix;
    stack operators;
    queue output;
    for (char token : infixExpression) {
        if (isalnum(token)) {
            output.enqueue(token);
        } else if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (!operators.isEmpty() && operators.peek() != '(') {
                output.enqueue(operators.pop());
            }
            operators.pop(); // Discard '('
        } else {
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(token)) {
                output.enqueue(operators.pop());
            }
            operators.push(token);
        }
    }

    while (!operators.isEmpty()) {
        output.enqueue(operators.pop());
    }

    while (!output.isEmpty()) {
        postfix += output.dequeue();
    }

    return postfix;
}

treenode* buildTree(string& postfixExpression) {
    return nullptr;
}

void printInfix(treenode* node) {
}

void printPrefix(treenode* node) {
}

void printPostfix(treenode* node) {
}
