/*
DLL.cpp

Zaw Ye Yaint Naing

CS162 Spring 0 Mitch Priestley

Permitted to usue the following code for this weeks homework.
*/

#include <iostream>

using namespace std;

class Node {
    protected: 
        int data;
        Node *next, *prev;
    
    public: 
        Node(): data {}, next {}, prev {} {};
        Node(int arg_data): data {arg_data}, next {}, prev {} {};

        int getData() const {return data;};
        Node* getNext() const {return next;};
        Node* getPrev() const {return prev;};

        void setNext(Node* nextAddress) {next = nextAddress;}
        void setPrev(Node* prevAddress) {prev = prevAddress;}
};

class DLL {
    protected: 
        Node *head, *tail;

    public: 
        DLL(): head{}, tail {} {};
        void append(Node*);
        void display(int direction = 1);
        bool insertAfter(Node*, int);
};

void DLL::append(Node* target) {
    if (target == nullptr)
          return;
        
    target->setNext(nullptr); // end of list 

    if (tail == nullptr) {
        head = target;
        target->setPrev(nullptr);
    }
    else {
        // new node points back to old tail
        target->setPrev(tail);
        // old tail points to new node
        tail->setNext(target);
    }

    tail = target;
}

void DLL::display(int direction) {
    Node* curr {}; // current Node
    
    // direction?
    if (direction == -1)
        cout << "Reverse ";
    
    cout << "List: " << endl;

    if (direction) {
        curr = head;
        while (curr) {
            cout << curr->getData() << ' ' << endl;
            curr = curr->getNext();
        }
    } else {
        curr = tail;
        while (curr) {
            cout << curr->getData() << ' ' << endl;
            curr = curr->getPrev();
        }
    }

    cout << endl;
}

bool DLL::insertAfter(Node* nodePtr, int value) {
    Node* curr = head;

    // find the specified value until reaches the end or not found
    while (curr && curr->getData() != value)
        curr = curr->getNext();

    // If end is reached, then the value was not found (abort insertion)
    if (!curr)
        return false;

    // The specified value was found! The insertion will proceed 
    // Add the new node to the list in one of two ways 
    // case 1 if we are inserting at the end (Append)
    if (curr->getNext() == nullptr)
        append(nodePtr);
    
    // Case 2 (Inserting between existing nodes)
    else {
        nodePtr->setPrev(curr);
        nodePtr->setNext(curr->getNext());
        curr->setNext(nodePtr);
    }

    return true;
}

int main() {
    DLL dll;
    Node *nodePtr;

    cout << "Welocme to our Doubly Linked List Program: " << endl << endl;
    
    cout << "1. We being with an empty list. " << endl;

    dll.display();

    cout << "2. We append a node containing 15 to our list. " << endl;

    nodePtr = new Node(15);

    dll.append(nodePtr);

    dll.display();
    
    cout << "3. We append a node containing 7 to our list. " << endl;

    dll.append(new Node(7));

    dll.display();

    cout << "4. We show our list in reverse." << endl;

    dll.display(-1);

    cout << "5. We append a node containing 18 to our list, the display list "
            "forward and backward." << endl;

    dll.append(new Node(18));

    dll.display();

    dll.display(-1);

    cout << "6. We insert a new node containing 5 after the existing node "
            "with 15, then display the list forward and backward.." << endl;

    nodePtr = new Node(5);

    if (!dll.insertAfter(nodePtr, 15))
        cout << "Insertion after 15 faied." << endl;
    
    dll.display();
    dll.display(-1);

    // Handshake
    cout << "Program Complete." << endl;

    return 0;

}