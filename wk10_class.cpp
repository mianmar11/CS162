// Class Implementation file for Node and DLL 
#include <iostream>
#include <string>

#include "wk10_class.h"

using namespace std;

// Node Class
Node::Node(int argData) {
    prev = nullptr;
    next = nullptr;
    data = argData;
};


// Getters
Node* Node::getNext() const {
    return next;
};

Node* Node::getPrev() const {
    return prev;
};

int Node::getData() const {
    return data;
};


// Setters
void Node::setData(int newData) {
    data = newData;
};

void Node::setNext(Node* newNext) {
    next = newNext;
};

void Node::setPrev(Node* newPrev) {
    prev = newPrev;
};


// DLL Class
void DLL::append(Node* target) {
    if (target == nullptr)
          return;
        
    target->setNext(nullptr); // end of list 

    // Update neighbor's address
    if (tail == nullptr) {
        head = target;
        target->setPrev(nullptr);
    }
    else {
        target->setPrev(tail);
        tail->setNext(target);
    }

    tail = target;
}

void DLL::display(int direction) {
    Node* curr {}; // current Node
    
    if (direction == -1)
        cout << "Reverse ";
    
    cout << "List: " << endl;

    if (direction != -1) {
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

void DLL::find(int target) {
    Node* curr = head;  // current node
    int foundCount = 0; // The number of the target that exists in the list 

    // Find in iteration until it reaches null 
    while (curr) {
        if (curr->getData() == target)
            foundCount++;
        curr = curr->getNext();
    }

    // Display result
    cout << (foundCount ? "Target found." : "Target not found.") << endl;
    cout << foundCount << " number of target," << target << ", exists in the list.";
};

bool DLL::insertBefore(Node* nodePtr, int value) {
    Node* curr = tail;

    // find the specified value until reaches the origin or not found
    while (curr && curr->getData() != value)
        curr = curr->getPrev();

    // If origin is reached, then the value was not found (abort insertion)
    if (!curr)
        return false;

    // The specified value was found! The insertion will proceed 
    // Add the new node to the list in one of two ways 
    // case 1 if we are inserting at the origin
    if (curr->getPrev() == nullptr) {
        
        nodePtr->setPrev(nullptr); // start of the list

        // Update neighbor's address
        nodePtr->setNext(head);
        head->setPrev(nodePtr);

        // Update the head of the list
        head = nodePtr;
    }
    
    // Case 2 (Inserting between existing nodes)
    else {
        nodePtr->setPrev(curr->getPrev());
        nodePtr->setNext(curr);
        curr->getPrev()->setNext(nodePtr);  // need to update the Node as well 
        curr->setPrev(nodePtr);
    }

    return true;
}
