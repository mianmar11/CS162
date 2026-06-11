// Header file for Node class

#pragma once 
#include <iostream>

class Node {
    private:
    public: // temp for testing purposes only 

    protected:
        Node* prev; 
        Node* next;
        int data;

    public:
        Node(): prev{}, next{}, data{} {};
        Node(int argData);

        Node* getNext() const;
        Node* getPrev() const;
        int getData() const;

        void setData(int);
        void setNext(Node* newNext);
        void setPrev(Node* newPrev);
};


class DLL {
    protected: 
        Node* head;
        Node* tail;

    public: 
        DLL(): head{}, tail {} {};
        void append(Node*);
        void display(int direction = 1);
        bool insertAfter(Node*, int);

        void find(int);
        bool insertBefore(Node*, int);
};
