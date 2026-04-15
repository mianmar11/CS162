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
    // string name("Giorno Gorvana"); // (since string is an object, name is an instnace of string object (OOP))

    char city[11] = "Portland"; // (C-string)

    // name = "Zaw Ye Yaint Naing"; // (RHS is a character array which is a C string)

    cout << city << endl;

    // city[0] = "Seattle";

    cout << static_cast<int>(city[7]) << endl; // 'd' of Portland

    cout << static_cast<int>(city[8]) << endl; // the null terminator after the 'd'

    city[0] = 'Z';

    for (int idx = 0; idx < strlen(city); idx++) {
        city[idx] = toupper(city[idx]);
    }

    cout << city << endl;

    city[8] = 'Y';
    city[9] = 'Z';
    city[10] = 'A';
    city[11] = 'B';

    cout << city << endl;

    strcpy(city, "89");

    cout << atoi(city) + 1 << endl;

    return 0;
}
