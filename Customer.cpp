// Class Implementation for Customer

#include "Customer.h"
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;


Customer :: Customer() {
    strcpy(id, "1000");
    strcpy(companyName, "Winco\0");
    strcpy(city, "Portland\0");
    strcpy(state, "Oregon\0");
    type = 'W';    // W as wholesale and R as retailer
}

Customer :: Customer(string newid) {
    strcpy(id, newid.c_str());
    strcpy(companyName, "Winco\0");
    strcpy(city, "Portland\0");
    strcpy(state, "Oregon\0");
    type = 'W';    // W as wholesale and R as retailer
}

Customer :: Customer(string newId, string newCompany, string newCity, string newState, char newtype) {
    strcpy(id, newId.c_str());
    strcpy(companyName, newCompany.c_str());
    strcpy(city, newCity.c_str());
    strcpy(state, newState.c_str());
    type = newtype;
}

Customer :: ~Customer() {
    strcpy(id, "");
    strcpy(companyName, "");
    strcpy(city, "");
    strcpy(state, "");
    type = '\0';
}


bool Customer :: matchID(char otherID[]) {
    return strcmp(id, otherID) == 0;
}

string Customer :: getID() {
    return id;
}

void Customer :: output(std::ostream& os) {
    // os << "Hello world";
    // os << this->id << companyName << city << state << type;
    os << left << setw(6) << id << setw(16) << companyName << setw(10) << city
    << setw(10) << state << setw(10) << type;
}
