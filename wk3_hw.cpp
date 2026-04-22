/*

Credits: StackOverflow. cppreference.com, W3School, IBM, Microsoft Learn
*/

#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono_literals;
using namespace this_thread;

// Func Prototypes
void RenderText(const char[], char ending = '\n');        // Display text at a pace just like in actual games

int main() {
    // Init Variable
    string username;                // Player name
    string locations;               // Locations of the game
    int current_loc {};             // Current location that player is in

    // Welcome User
    RenderText("Hello Stranger..");
    RenderText("Your name...?: ", '\0');
    getline(cin, username);
    RenderText("Hello, ", '\0');
    RenderText(username.c_str());
    RenderText("\nWelcome to .{Silver Grit}.");
    cout << endl;
         
    cout << "Hello stranger, you are.." << endl;
    cout << "[ENTER To Continue]" << endl;
    
    cout  << locations[current_loc];

    return 0;
}

void RenderText(const char msg[], char ending) {
    for (int idx=0; msg[idx] != '\0'; idx++) {
        cout << msg[idx] << flush;
        sleep_for(35ms);
    }
    cout << ending;
}