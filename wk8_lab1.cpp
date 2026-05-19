/*
Zaw Ye Yaint Naing

Cs162 Spring - Mitch Priestley

Purpose:

Specification:

Credits: 
*/

#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Firm {
    protected: 
    public:
        char company_name[30];
        char city[20];

    public:
        // Firm();      // Default constructor
        // Firm(const)  // Copy Constructor
        // parameterized constructor
        // Getters and setters 
        char* get_city() {return city;};
        void set_city(const char arg_city[]) {strncpy(city, arg_city, sizeof(city) - 1); city[19] = '\0';};
        void display() {cout << "Co. Name: " << company_name << endl << " City: " << city << endl;}
};

// Client "is a" Firm
class Client: public Firm {
    protected:
    public:
        char region; // 'E' for east, 'W' for west 

    public:
        void display() {
            cout << "Client information: " << endl;
            Firm::display();
            cout << "Regoin: " << region << endl;
        }
};

class Vendor: public Firm {
    protected:
    public: 
        int quality; // 1 to 10 rating
};


int main() {
    Client client[4] {
        {"Nike", "Beaverton", 'W'},
        {"Adidas", "Portland", 'W'},
        {"Daimler", "Portland", 'W'},
        {"Patagonia", "Portland", 'W'}
    };

    char choice[30] {}; // stores user's choice of client
    cout << "inheritance Program" << endl << endl;
    cout << "Choose one of the following client firms: " << endl;

    for (Client c: client)
        cout << c.company_name << ' ';
    cout << endl;

    cout << "Your choice: ";

    cin.getline(choice, 30, '\n');
    cout << endl;

    for (Client c: client)
        if (strcmp(c.company_name, choice) == 0)
            c.display();

    return 0;
}