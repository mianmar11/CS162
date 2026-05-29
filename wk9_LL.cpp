// LL.cpp

#include <iostream>

#include "wk9_LL.h"

using namespace std;

LL :: ~LL() {
    Node* curr = head;
    Node* subsequent = nullptr;

    while (curr) {
        subsequent = curr->next;
        // zerorize
        delete curr;
        curr = nullptr;
        curr= subsequent;
    }
};

void LL::append(string a_name, int a_score) {
    Node* curr = head;
    Node* baby = new Node{a_name, a_score};

    if (!head) // this is the first node 
        head = baby;
    else {
        while (curr->next) // traverse to the end ofthe list
            curr = curr->next;
        curr->next = baby; // update 
    }
}

void LL::display() {
    Node* curr = head;

    while (curr) {
        cout << curr->data.name << " " << curr->data.score << endl;
        curr = curr->next;
    }

    cout << " - end - " << endl << endl;
}