/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: To display the customers and their info. Customer type will display either wholesale customer or retail customer based on 
their status.

Speficiation: The program will populate the customer pointer customersay with customer structs that include: {id, name, city, state, company, 
customer type}, and display them all to the user. It will then use Lookup to find speciific customer by entering 
their user id. It will display the customer's: Name, Id, City, State, Company Name, and Customer type. The customer type will 
display either Retail or Wholesale customer depending on their status data.
*/

#include <cstring>      // memset
#include <iomanip>      // setw
#include <iostream>     
#include <string>

using namespace std;

// Global constants
const int NAME_LENGTH = 15;
const int ID_LENGTH = 7;
const int CITY_LENGTH = 16;
const int STATE_LENGTH = 14;

// Structs
struct Customer {
    // data members
    char name[NAME_LENGTH] {};      // 14 length name char with ending \0
    char id[ID_LENGTH] {};          // 6 length id (like mhcc) with ending \0
    char city[CITY_LENGTH] {};      // 15 length city name with ending \0
    char state[STATE_LENGTH] {};    // 13 length state name
    char company[NAME_LENGTH] {};   // 14 length company name
    char customer_type {};          // 1 length customer type
};

// Function Declaration
int Initialize(Customer* &);
void Display(Customer* &, int);
void LookUp(Customer* &, int);

int main() {
    // Init Variables
    Customer *customers {nullptr};
    int size {};

    // Welcome User
    cout << "Welcome to Customer Database v1.0." << endl << endl;

    // Populate data
    size = Initialize(customers);

    // Display populated customers
    Display(customers, size);
    
    // Look Up customer
    LookUp(customers, size);

    // Purge data
    size = 0;

    delete[] customers;
    customers = nullptr;

    // Handshake
    cout << "\nProgram Complete" << endl << endl;

    // End Normally
    return 0;
}


// Function Definition
int Initialize(Customer* &arr) {
    const int size {5};            // size of the array
    
    arr = new Customer[] {
        {"Zaw", "847922", "Portland", "Oregon", 'R'},
        {"Han", "928471", "San Jose", "California", 'W'},
        {"Jiya", "205821", "Chicago", "Illinois", 'R'},
        {"Hoya", "589101", "San Francisco", "California", 'R'},
        {"Purity", "019231", "New York", "New York", 'W'}, 
    };

    return size;
}

void Display(Customer* &, int) {

}

void LookUp(Customer* &, int) {
    
}
