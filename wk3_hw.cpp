/*

Credits: StackOverflow, cppreference.com, W3School, IBM, Microsoft Learn, Medium
*/

#include <iostream>
#include <cstring>
#include <string>
#include <chrono> // for chrono_literals
#include <thread> // for this_thread

using namespace std;
using namespace chrono_literals;
using namespace this_thread;

// Func Prototypes
void RenderText(const char[], 
    char ending = '\n', 
    chrono::milliseconds duration = 40ms);                  // Display text at a pace just like in actual games
void HideOutput(int);                                       // Hide the previous output by n number 
string GetInput();                                          // Get User Input and Check with sample 

int main() {
    // Init Variable
    string username;                // Player name
    string locations;               // Locations of the game
    int current_loc {};             // Current location that player is in

    // Welcome User
    RenderText("Hello Stranger..");
    RenderText("Your name...?: ", '\0');
    getline(cin, username);
    HideOutput(15);

    RenderText("Hello, ", '\0');
    RenderText(username.c_str());       // (Change the string to c string)
    RenderText("Welcome to .{Silver Grit}.");
    
    
    cout << "[ENTER To Continue]";
    GetInput();
    HideOutput(15);

    // Epilogue
    cout << "[NPC] ";
    RenderText("Hello stranger, you are..", '\n', 40ms);
    cout << "[NPC] ";
    RenderText("WAIT.... ", '\0', 150ms);
    RenderText("Aren't you one of those heros that fought Mighty Evil???", '\n', 35ms);
    cout << "[ENTER To Continue]";
    
    cout  << locations[current_loc];

    return 0;
}


// Purpose: To render a text a each character at a time just like how dialogues are rendered in games
// Specification: It loops through the character array until it reaches to the end or null character
// and print out each character then sleep for 20 milliseconds, then loop again.
// Arguments: Required char array and ending option to end the display with endl or not
void RenderText(const char msg[], char ending, chrono::milliseconds duration) {
    for (int idx=0; msg[idx] != '\0'; idx++) {
        cout << msg[idx] << flush;
        sleep_for(duration);
    }
    cout << ending;
}

// Purpose: To hide previous output in the terminal to make it look like it is cleared terminal
// Specification: loops through the number of lines and break a line each loop 
// Arguments: Requires a int num of lines
void HideOutput(int num) {
    for (int idx=0; idx<num; idx++) 
        cout << endl;
}

// Purpose:
// Specification:
// Arguments:
template <typename T>
bool CheckInput(T sample, T target) {
    if (target == sample)
        return 1;
    return 0;
}

string GetInput() {
    string user_input; // partial init
    getline(cin, user_input);
    return user_input;
}
