/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: The purpose of this program is to extract the content from raw weather 
report and make it readable to the users and display it. 

Specification: This program loads the raw weather report, extract required contents
from the file, store them in the arrays, by header source name, then display all 
the weahter reports, followed by their source name. 
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


// Global constants
enum COLUMNS {DATE, LOW, HIGH, RAIN, SUMMARY, SOURCE=17};

const int SOURCES = 10,
    COLS = 18,
    DATES = 18;

const string FILENAME = "weather_forcasts.txt";

// Func Prototypes
void LoadData(string[], string[][DATES][COLS]);


int main() {
    string data[SOURCES][DATES][COLS];
    string headings[COLS];

    LoadData(headings, data);

    // Display weather report
    for (int source = 0; source < SOURCES; source++) {

        cout << "\nSource: " << data[source][0][SOURCE] << endl;

        for (int row=0; row < DATES; row++) {
            cout << data[source][row][DATE] << ": " << data[source][row][LOW] << " to "
                 << data[source][row][HIGH] << " degrees and "
                 << data[source][row][RAIN] << "% chance of rain. Overall, "
                 << data[source][row][SUMMARY] << '.' << endl;
        }
    }
    
    return 0;
}

void LoadData(string hdg[], string arr[][DATES][COLS]) {
    ifstream infile(FILENAME);

    if (!infile)
        exit(1); //
    
    for (int col=0; col<COLS-1; col++) {
        getline(infile, hdg[col], ',') >> ws; // read any excess whitespace
    }
    getline(infile, hdg[COLS-1], '\n') >> ws; // '\n' or chr(13)}

    for (int source=0; source<SOURCES; source++) {
        for (int row=0; row<DATES; row++) {
            for (int col=0; col<COLS-1; col++) {
                getline(infile, arr[source][row][col], ',') >> ws;
            }
            getline(infile, arr[source][row][SOURCE]);
        }
    }
}
