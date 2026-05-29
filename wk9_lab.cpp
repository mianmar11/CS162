/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: Specify, Implement, and demostrate a linked list.

Specifciation: Demostrate append and display, showing that we can append and
display node in our linked list (LL). Each node contains a name and score. 
*/

#include <iostream>
#include <string>

#include "wk9_LL.h"

using namespace std;

int main() {
    LL list;

    cout << "Linked List Program." << endl << endl;

    list.append("Abs", 67);
    list.display();

    list.append("Beau", 88);
    list.append("Claude", 99);
    list.display();

    cout << "Program Complete" << endl << endl;
}