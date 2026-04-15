/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: This purpose of this program is to get the weather report from a specific
date from a specific source. It will display these weather reports such as: 
date, low, high, chance of rain, summary, source. 

Specification: This program loads weather data from the pre-existing file, display 
the list of sources of each report to user, prompt user to choose source, display
the list of dates of each report data to user, prompt user to choose the date, then
display the weather report of (Date, Low, High, COR, Summary, Source).

Credits: StackOverflow, CS161 Lab, 
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
    COLS_NUM = 6,   // Number of cols to display
    SOURCE_IDX = 17;

// Function Prototypes
void LoadData(string [][DATES][COLS], string []);
void GetSource(int &, string [][DATES][COLS]);
void GetDate(int &, string [][COLS]);
void DisplayReport(string [], string [][DATES][COLS], int, int);
void GetInput(int &, int);

int main() {
    // Init Variables
    string* headings = new string[COLS];// Header Name
    string datas[SOURCES][DATES][COLS]; // Collection of Daily Weather Data stored in a Corresponding Source
    int target_source = SENTINEL;
    int target_date = SENTINEL;

    // Load Data
    LoadData(datas, headings);

    // Welcome User
    cout << "Welcome to WeatherPUD, where you get the weather the way you want." << endl << endl;
    
    // Get Source Input
    GetSource(target_source, datas);

    // Get Date Input
    GetDate(target_date, datas[target_source]);

    // Display Weather Report 
    DisplayReport(headings, datas, target_source, target_date);

    // Purge Data 
    target_date = target_source = SENTINEL;

    memset(headings, 0, COLS * sizeof(string));
    delete[] headings; 
    headings = nullptr; 

    for (int source = 0; source < SOURCES; source++) {
        for (int date = 0; date < DATES; date++) {
            for (int data = 0; data < COLS; data++) {
                datas[source][date][data] = string(datas[source][date][data].length(), ' ');
                memset(datas[source][date][data].data(), 0, datas[source][date][data].capacity());
            }
        }
    }

    // End Normally
    return 0;
}

// Purpose: Laod the contents from text file into the array
// Speciifcation: loop contents from first line first to store headings, then 
//                loop each lines and each contents
// Arguments: Required 3D data array and 1D headings array
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

// Purpose: Validate the user input to make sure that they are entering correct data type and answer
// Specification: This function will check if the user entered correct datatype in a loop and then check
// if it is within the range of the answers 
// Arguments: Required int input and range
void GetInput(int &input, int max_range) {

    // Validate datatype 
    while (!(cin >> input) || (input < 0) || (input >= max_range)) {
        cout << "Error! Invalid Input. \nPlease re-enter a integer: ";
        cin.clear();
        cin.ignore(1024, '\n');
    }
}

// Purpose: To get the source from user for accessing dates
// Speciifcation: Display the list of sources, prompt user and get user input for specific source
// Arguments: Required int target source and 3D data array
void GetSource(int &target, string arr[][DATES][COLS]) {
    // Prompt User
    cout << "To get your forecast, you will select your choices of source and date." << endl;
    cout << "Please choose a source: " << endl; // Prompt User

    // Display a list of Weather Sources
    for (int source = 0; source < SOURCES; ++source) { 
        if (source % 3 == 0)
            cout << endl;
        cout << right << setw(2) << source << ". " << left << setw(22) << arr[source][0][SOURCE_IDX];
    }
    cout << endl;

    // Get Input
    cout << "\nYour selection: ";
    GetInput(target, SOURCES);
    cout << endl;

    cout << "We are adjusting our satellite dish now to intercept weather broadcasts originating from " << arr[target][0][SOURCE_IDX] << "." << endl; 
    cout << "We're doing this just for you!" << endl << endl;

}

// Purpose: To get the date from user for weather report
// Speciifcation: Display the list of dates, prompt user and get user input for specific date
// Arguments: Required int passed-by-reference target date and 3D string array
void GetDate(int &target, string date_arr[][COLS]) {
    cout << "Please choose the day for which you would like the weather forcast:" << endl;

    for (int date = 0; date < DATES; date++) {
        if (date % 5 == 0)
            cout << endl;
        cout << right << setw(2) << date << ". " << left << setw(12) << date_arr[date][0];
    }
    cout << endl;

    cout << "\nYour selection: ";
    GetInput(target, DATES);
    cout << endl;
    
    cout << "Weather Report from " << date_arr[0][SOURCE_IDX] << " concerning " << date_arr[target][0] << "..." << endl << endl; 
}

// Purpose: To display selected weather data
// Speciifcation: Loops through 5 first cols and display, then seperatly display last source col
// Arguments: Required 1D headings array, 3D string array, source and date
void DisplayReport(string headings[], string arr[][DATES][COLS], int source, int date) {
    for (int idx=0; idx<COLS_NUM-1; idx++) {
        cout << right << setw(22) << *(headings + idx) << ": " << left << setw(10) << arr[source][date][idx] << endl;
    }
    cout << right << setw(22) << *(headings + SOURCE_IDX) << ": " << left << setw(10) << arr[source][date][SOURCE_IDX] << endl;
}
