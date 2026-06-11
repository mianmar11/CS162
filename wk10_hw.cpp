/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: The purpose this program is to create a chain doubly linked list that can:
display, reverse display, append, insert [after, before], find. 

Specification: The doubly linked list uses user defined datatype pointers to communicate
the data between the chain of nodes. Nodes store the data, addresses of its neighbor 
while DLL manages the route and work aroound the nodes to work seemlessly.
*/

#include <iostream>
#include <string>

#include "wk10_class.h"

using namespace std;

int main() {
    DLL dll;
    Node* nodeptr {};       
    int lookUpTarget {};    // Used to look up a target valkue

    // Welcome User
    cout << "Welcome to Doubly Linked List Program." << endl << endl;

    // Display Empty List
    dll.display();

    // Populate List
    cout << "Populating the list..." << endl << endl;
    for (int i = 0; i < 10; i++)
        dll.append(new Node(i));

    // Display List (forward/backwards)
    dll.display();
    dll.display(-1);

    // Insert a node after a node
    cout << "Inserting 22 after 9..." << endl;
    dll.insertAfter(new Node(22), 9);
    dll.display();
    cout << endl;

    // LookUp
    cout << "Enter a value to look up: ";
    cin >> lookUpTarget;
    cout << "Finding Target..." << endl;
    dll.find(lookUpTarget);
    cout << endl << endl;

    // Insert a Node before target 
    cout << "Inserting 9 before 0 and 22 before 5..." << endl;
    dll.insertBefore(new Node(9), 0);
    dll.insertBefore(new Node(22), 5);
    
    // Display List
    dll.display(-1);
    cout << endl;

    cout << "Program Completed Option 2.";

    return 0;
}