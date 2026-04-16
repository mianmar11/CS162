/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: This program validates SSN inputs.
*/

#include <iostream>
#include <string>
#include <cctype>
#include <cstring>

using namespace std;

int main() {
    bool valid = true;  // default flag (chage to false if encountered invalid input)
    string ssn;         // Social Security Number (Using int will remove leading 0s)

    // Welcome
    cout << "Welcome to SSN validation program.\n";

    do {
        valid = true;

        // prompt of SSN
        cout << "\nEnter a 9-digit social security number with \n"
                "hyphens in the following format (###-##-####): ";

        // Input SSN
        getline(cin, ssn); // cin will end input when encountered space

        // Confirm not blank or less than or more than 11 characters
        if (ssn.length() != 11) {
            cout << "Error! SSN must be 11 characters including hyphens." << endl;
            valid = false;
        }
        
        // Confirm hyphens 
        else if (ssn[3] != '-' || ssn[6] != '-') {
            cout << "Error! Two hyphens are required!" << endl;
            valid = false;
        }

        // Confirm characters are digits
        else {
            for (int idx: {0, 1, 2, 4, 5, 7, 8, 9, 10}) {
                if (valid && !isdigit(ssn[idx])) {
                    valid = false;
                    cout << "Error! SSN must be numeric!" << endl;
                }
            }
        }
    } while (valid == false);

    // Handshake
    cout << "Accepted! Program Complete." << endl;

    // Purge Data
    memset(&ssn[0], 0, ssn.length());
    valid = false;

    return 0;
}
