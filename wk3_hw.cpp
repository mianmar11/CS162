/*

Credits: StackOverflow. cppreference.com
*/

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono_literals;
using namespace this_thread;

void DisplayTxt(string txt);        // Display text at a pace just like in actual games

int main() {
    // Init Variable
    string username;                // Player name
    string locations;               // Locations of the game
    int current_loc {};             // Current location that player is in

    // Welcome User
    cout << "Hello Stranger.." << endl;
    cout << "Your name...?: ";
    getline(cin, username);
    cout << "Hello, " << username << "." << endl;
    cout << "\nWelcome to .{Silver Grit}." << endl;

    cout << "Hello stranger, you are.." << endl;
    cout << "[ENTER To Continue]" << endl;
    
    char dialogue[] = "Aren't you one of those heros that fought the Mighty Evil days before?";

    for (int idx=0; dialogue[idx] != '\0'; idx++) {
        cout << dialogue[idx] << flush;
        sleep_for(20ms);
    }

    cout  << locations[current_loc];

    return 0;
}

void DisplayTxt(char msg[], int speed=20) {
    for (int idx=0; msg[idx] != '\0'; idx++) {
        cout << msg[idx] << flush;
        sleep_for(20ms);
    }
}