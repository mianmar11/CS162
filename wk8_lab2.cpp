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
        char company_name[31];
        char city[21];

    public:
        // Firm();      // Default constructor
        // Firm(const)  // Copy Constructor
        // parameterized constructor
        Firm(const char* name, const char* city_name) {
            strncpy(company_name, name, 30);
            company_name[30] = '\n';

            strncpy(city, city_name, sizeof(city) - 1);
            city[21] = '\0';
        }

        // Getters and setters 
        const char* get_city() {return city;};
        void set_city(const char arg_city[]) {
            strncpy(city, arg_city, sizeof(city) - 1); 
            city[21] = '\0';
        };
        
        virtual void display() {cout << right << setw(15) << "Co. Name: " << company_name << endl << right << setw(15) << "City: " << city << endl;}
};

// Client "is a" Firm
class Client: public Firm {
    protected:
    public:
        char region; // 'E' for east, 'W' for west 
        Client(const char* name, const char* city_name, char reg): 
            Firm(name, city_name), region {reg} {}

    public:
        void display() {
            cout << "Client information: " << endl;
            Firm::display();
            cout << right << setw(15) << "Regoin: " << region << endl;
        }
};

class Vendor: public Firm {
    protected:
    public: 
        int quality; // 1 to 10 rating
        Vendor(const char* name, const char* city_name, int qual): 
            Firm(name, city_name), quality {qual} {};
};


int main() {
    Client client[4] {
        {"Nike", "Beaverton", 'W'},
        {"Adidas", "Portland", 'W'},
        {"Daimler", "Portland", 'W'},
        {"Patagonia", "Portland", 'W'}
    };
    Firm* f {};
    Vendor vendor {"Coca-Cola", "Atlanta", 2};

    char choice[31] {}; // stores user's choice of client by name

    // Welcome user
    cout << "inheritance Program" << endl << endl;

    // Prompt user
    cout << "Choose one of the following client firms: " << endl;
    for (Client c: client)
        cout << c.company_name <<' ';
    cout << endl;

    cout << "Your choice: ";
    cin >> setw(31) >> choice;
    cout << endl;

    for (Client c: client)
        if (strncasecmp(c.company_name, choice, sizeof(choice) - 1) == 0)
            c.display();

    f = &client[2]; // f = new firm;
    f->display();   // use -> if using pointer variable to a object (dereferences the object, then calls the function)

    // cout << endl;
    // (*f).display(); // dereferences the object then calls the function 

    cout << endl;
    // vendor.display();
    f = &vendor;
    f->display();

    return 0;
}