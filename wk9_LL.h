// LL.h
#pragma once

#include <string>

struct Tester {
    std::string name;
    int score = 0;
};

struct Node {
    Tester data;
    Node* next = nullptr;
};

class LL {
    protected: 
    public:
        Node* head;
    
    public: 
        LL(): head{} {}; // this partial init auto assign nullptr to head
        ~LL();
        void append(std::string, int);
        void display();
};