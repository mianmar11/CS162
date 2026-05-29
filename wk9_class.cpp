// Class Implementation file
#include <iomanip>
#include <iostream>
#include <string>

#include "wk9_class.h"

using namespace std;

// Constructors/Destructors
Tester::~Tester() {
    name = string(name.length(), '\0');
    score = 0;
};


// Mutators
void Tester::setName(string newName){
    name = newName;
};

void Tester::setScore(int newScore){
    score = newScore;
};


// Accessors
string Tester::getName(){
    return name;
};

int Tester::getScore(){
    return score;
};


// Functions
void Tester::output(ostream& os){
    os << left << setw(10) << name << ' '
       << left << setw(3) << score << endl;
};
