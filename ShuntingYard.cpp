#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Node class for a singly linked list
class node {
private:
    char data;
    node* next;
public:
    node(char data) : data(data), next(nullptr) {} // Constructor
    char getdata() { return data; } // Getter for data
    void setnext(node* newnext) { next = newnext; } // Setter for next
    node *getnext(void) { return next; } // Getter for next
};

// Stack class
class stack {
private:
    node* top; // Top of the stack
public:
    stack() : top(nullptr) {} // Constructor

    // Push data onto the stack
    void push(char data) {
        node* newnode = new node(data); // Create a new node
        if (top == nullptr) {
            top = newnode; // If stack is empty, set the new node as top
        } else {
            newnode->setnext(top); // Set the new node's next to current top
            top = newnode; // Update top to the new node
        }
    }

    // Pop data from the stack
    char pop() {
        if (top == nullptr) {
            cout << "stack is empty" << endl; // If stack is empty, print error
            return '\0';
        }
        char data = top->getdata(); // Get data from top node
        node* temp = top; // Store top node in temp
        top = top->getnext(); // Update top to next node
        delete temp; // Delete the original top node
        return data; // Return popped data
    }

    // Peek at the top of the stack
    char peek() {
        if (top == nullptr) {
            cout << "stack is empty" << endl; // If stack is empty, print error
            return '\0';
        }
        return top->getdata(); // Return data from top node
    }

    // Check if stack is empty
    bool isEmpty() { return top == nullptr; }
};

// Queue class
class queue {
private:
    node* front; // Front of the queue
    node* rear; // Rear of the queue
public:
    queue() : front(nullptr), rear(nullptr) {} // Constructor

    // Enqueue data into the queue
    void enqueue(char data) {
        node* newnode = new node(data); // Create a new node
        if (rear == nullptr) {
            front = newnode; // If queue is empty, set front and rear to new node
            rear = newnode;
        } else {
            rear->setnext(newnode); // Set the current rear's next to new node
            rear = newnode; // Update rear to the new node
        }
    }

    // Dequeue data from the queue
    char dequeue() {
        if (front == nullptr) {
            cout << "queue is empty" << endl; // If queue is empty, print error
            return '\0';
        }
        char data = front->getdata(); // Get data from front node
        node* temp = front; // Store front node in temp
        front = front->getnext(); // Update front to next node
        if (front == nullptr) {
            rear = nullptr; // If queue becomes empty, set rear to null
        }
        delete temp; // Delete the original front node
        return data; // Return dequeued data
    }

    // Check if queue is empty
    bool isEmpty() { return front == nullptr; }
};

// TreeNode class for a binary tree
class treenode {
private:
    char data;
    treenode *left;
    treenode *right;
public:
    treenode(char data) : data(data), left(nullptr), right(nullptr) {} // Constructor

    char getData() { return data; } // Getter for data
    treenode *getLeft() { return left; } // Getter for left child
    void setLeft(treenode *newleft) { left = newleft; } // Setter for left child
    treenode *getRight() { return right; } // Getter for right child
    void setRight(treenode *newright) { right = newright; } // Setter for right child
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
    cout << "Enter the mathematical expression: ";
    getline(cin, infixExpression);

    string postfixExpression = shuntingYard(infixExpression); // Convert infix to postfix
    treenode* expressionTree = buildTree(postfixExpression); // Build expression tree

    string input;

    cout << "What do you want to do (infix, prefix, postfix)?" << endl;
    cin >> input;

    // Print the expression tree based on user input
    if (input.compare("infix") == 0) {
        cout << "Infix notation: ";
        printInfix(expressionTree);
        cout << endl;
    } else if (input.compare("prefix") == 0) {
        cout << "Prefix notation: ";
        printPrefix(expressionTree);
        cout << endl;
    } else if (input.compare("postfix") == 0) {
        cout << "Postfix notation: ";
        printPostfix(expressionTree);
        cout << endl;
    }
}

// Operator precedence function
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

// Shunting Yard algorithm to convert infix expression to postfix
string shuntingYard(string& infixExpression) {
    string postfix;
    stack operators;
    queue output;

    // Iterate through the infix expression
    for (char token : infixExpression) {
        if (isalnum(token)) { // If token is operand, enqueue it to output queue
            output.enqueue(token);
        } else if (token == '(') { // If token is '(', push it onto operator stack
            operators.push(token);
        } else if (token == ')') { // If token is ')', pop operators from stack to output until '(' is encountered
            while (!operators.isEmpty() && operators.peek() != '(') {
                output.enqueue(operators.pop());
            }
            operators.pop(); // Discard '('
        } else { // If token is operator
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(token)) {
                output.enqueue(operators.pop()); // Pop operators with higher or equal precedence to output
            }
            operators.push(token); // Push current operator onto stack
        }
    }

    // Empty the operator stack to output
    while (!operators.isEmpty()) {
        output.enqueue(operators.pop());
    }

    // Concatenate elements in output queue to form postfix expression
    while (!output.isEmpty()) {
        postfix += output.dequeue();
    }

    return postfix;
}

// Build expression tree from postfix expression
treenode* buildTree(string& postfixExpression) {
    treenode* root = nullptr;
    treenode* current = nullptr;

    // Iterate through postfix expression
    for (char token : postfixExpression) {
        if (isalnum(token)) { // If token is operand, create a new node and connect it to current node
            treenode* newNode = new treenode(token);
            if (!root) { // If root is not set, set it to the new node
                root = newNode;
            } else {
                current->setRight(newNode);
            }
            current = newNode;
        } else { // If token is operator
            treenode* newNode = new treenode(token);
            if (!current->getLeft()) { // If current node does not have left child, connect root to the left of new node
                newNode->setLeft(root);
                root = newNode;
            } else { // If current node has left child, connect current node's right to new node and update current node
                newNode->setLeft(current->getRight());
                current->setRight(newNode);
            }
            current = newNode;
        }
    }

    return root; // Return the root of the expression tree
}

// Print infix notation of expression tree recursively
void printInfix(treenode* node) {
    if (node) {
        if (node->getLeft() && node->getRight()) {
            cout << "(";
            printInfix(node->getLeft());
            cout << node->getData();
            printInfix(node->getRight());
            cout << ")";
        } else {
            cout << node->getData();
        }
    }
}

// Print prefix notation of expression tree recursively
void printPrefix(treenode* node) {
    if (node) {
        cout << node->getData();
        printPrefix(node->getLeft());
        printPrefix(node->getRight());
    }
}

// Print postfix notation of expression tree recursively
void printPostfix(treenode* node) {
    if (node) {
        printPostfix(node->getLeft());
        printPostfix(node->getRight());
        cout << node->getData();
    }
}
