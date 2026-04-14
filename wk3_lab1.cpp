/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose:

Specfication:
*/

#include <iostream> 
#include <string>   // included operator=(char[])
#include <cstring>

using namespace std;

int main() {
    string name("Giorno Gorvana"); // (since string is an object, name is an instnace of string object (OOP))

    char city[11] = "Seattle"; // (C-string)

    name = "Zaw Ye Yaint Naing"; // (RHS is a character array which is a C string)

    cout << city << endl;

    return 0;
}