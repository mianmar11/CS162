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
const int NAME_LENGTH = 16;
const int ID_LENGTH = 7;
const int CITY_LENGTH = 16;
const int STATE_LENGTH = 14;

// Structs
struct Customer {
    // data members
    char name[NAME_LENGTH] {};      // 15 length name char with ending \0
    char id[ID_LENGTH] {};          // 6 length id (like mhcc) with ending \0
    char city[CITY_LENGTH] {};      // 15 length city name with ending \0
    char state[STATE_LENGTH] {};    // 13 length state name
    char company[NAME_LENGTH] {};   // 15 length company name
    char customer_type {};          // 1 length customer type

    // member function
    void display (ostream& os) {
        static string STATUS[] = {"Wholesale", "Retail"};

        os << left << setw(NAME_LENGTH) << id << setw(NAME_LENGTH) << name << setw(NAME_LENGTH) << city << setw(NAME_LENGTH) 
        << state << setw(NAME_LENGTH) << company << setw(10) << STATUS[customer_type == 'R'] << endl;
    }
};

// Function Declaration
int Initialize(Customer* &);
void Display(Customer* &, int);
void LookUp(Customer* &, int);
void DisplayHeaders(string [], int);

int main() {
    // Init Variables
    string headers[] {"ID", "Name", "City", "State", "Company", "Type"};
    int header_size = 6;
    Customer *customers {nullptr};
    int size {};

    // Welcome User
    cout << "Welcome to Customer Database v1.0." << endl << endl;

    // Populate data
    size = Initialize(customers);

    // Display populated customers
    DisplayHeaders(headers, header_size);
    Display(customers, size);
    
    // Look Up customer
    LookUp(customers, size);

    // Purge data
    size = 0;

    delete[] customers;
    customers = nullptr;

    // Handshake
    cout << "\nProgram Complete." << endl << endl;

    // End Normally
    return 0;
}


// Function Definition
int Initialize(Customer* &arr) {
    const int size {5};            // size of the array
    
    arr = new Customer[] {
        {"Zaw", "847922", "Portland", "Oregon", "Nvidia", 'R'},
        {"Han", "928471", "San Jose", "California", "AMD", 'W'},
        {"Jiya", "205821", "Chicago", "Illinois", "Pinterest", 'R'},
        {"Hoya", "589101", "San Francisco", "California", "OpenAI", 'R'},
        {"Purity", "019231", "New York", "New York", "Dolce & Gabbana", 'W'}, 
    };

    return size;
}

void Display(Customer* &arr, int size) {
    for (int idx=0; idx<size; ++idx) 
        arr[idx].display(cout);
    cout << endl;
}

void LookUp(Customer* &arr, int size) {
    char target[NAME_LENGTH] {};    // target to look up
    int idx {};                     // idx of target
    
    // Prompt User
    cout << "Enter the ID of the customer to look up: ";

    // Get Input
    cin >> setw(NAME_LENGTH) >> target; // hold the limit of user input to name length

    // Search For User
    for (idx=0; idx<size && strcmp(arr[idx].id, target) != 0; ++idx);  // (strcmp() compares two string and returns a bool)
    if (idx < size) // if found
        arr[idx].display(cout);
    else 
        cout << "User ID [" << target << "] not found." << endl;
}

void DisplayHeaders(string arr[], int size) {
    // Loop through the header and display the header
    for (int idx=0; idx<size; idx++) {
        cout << left << setw(NAME_LENGTH) << arr[idx];
    }
    cout << endl << endl;                                                                               
}
