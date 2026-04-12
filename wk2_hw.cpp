/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: 

Specification: 
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

// Global Constants
const string FILENAME = "weather_forcasts.txt";
int SENTINEL = -1;
const int 
    SOURCES = 18,   // number of sources: AccuWeather, BBC Weather, etc...
    DATES = 15,     // Rows of data cases (heading not included)
    COLS = 18,      // Total columns, but actually only display 6 (Date, Low, High, COR, Summary, Source)
    SOURCE_IDX = 17;

// Function Prototypes
void LoadData(string [][DATES][COLS], string []);

int main() {
    // Init Variables
    string headings[COLS];              // Header Name
    string datas[SOURCES][DATES][COLS]; // Collection of Daily Weather Data stored in a Corresponding Source
    int selection = SENTINEL;

    // Load Data
    LoadData(datas, headings);

    // Welcome User
    cout << "Welcome to WeatherPUD, where you get the weather the way you want." << endl;
    cout << "To get your forecast, you will select your choices of source and date." << endl;

    // Get Source Input
    cout << "Please choose a source: " << endl; // Prompt User
    for (int idx = 0; idx < SOURCES; ++idx) { // Display Source
        if (idx % 3 == 0)
            cout << endl;
        cout << setw(2) << right << idx << ". " << datas[idx][0][SOURCE_IDX];
    }
    cout << endl;

    cout << "Your Selection: ";
    cin >> selection;

    cout << "We are adjusting our satellite dish now to intercept weather broadcasts originating from NPR." << endl; 
    cout << "We're doing this just for you!" << endl << endl;
    
    cout << "Please choose the day for which you would like the weather forcast." << endl << endl;

    // Purge Data

    // End Normally
    return 0;
}


void LoadData(string arr[][DATES][COLS], string headings[]) {
    ifstream infile(FILENAME);

    if (!infile)
        exit(1); // exit with error if file not found

    // Get Headings
    for (int col=0; col<COLS-1; col++) {
        getline(infile, headings[col], ',') >> ws;
    }
    getline(infile, headings[COLS-1], '\n') >> ws; // '\n' or chr(13)}

    for (int source=0; source<SOURCES; source++) {

        // Loop through each line (whcih contains sets of datas)
        for (int row=0; row<DATES; row++) {
            // Loop through each set of datas
            for (int col=0; col<COLS-1; col++) {
                getline(infile, arr[source][row][col], ',') >> ws;
            }
            getline(infile, arr[source][row][SOURCE_IDX]); // get source
        }
    }
}
