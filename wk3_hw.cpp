/*

Credits: StackOverflow, cppreference.com, W3School, IBM, Microsoft Learn, Medium, BroCode(YT)
*/

#include <iostream>
#include <cstring>
#include <string>
#include <chrono> // for chrono_literals
#include <thread> // for this_thread
#include <unordered_map> // hashmap or dictionary

using namespace std;
using namespace chrono_literals;
using namespace this_thread;

// Global Consts
unordered_map<string, string> COLORS {
    {"cyan",    "\033[36m"},
    {"yellow",  "\033[33m"},
    {"red",     "\033[31m"},
    {"green",   "\033[32m"},
    {"white",   "\033[97m"},
    {"reset",   "\033[0m"}
};

unordered_map<string, chrono::milliseconds> durations {
    {"150", 150ms},
    {"40", 40ms},
    {"35", 35ms}
};

// Func Prototypes
void RenderText(const char[], 
    chrono::milliseconds duration = 40ms);                  // Display text at a pace just like in actual games
void HideOutput(int);                                       // Hide the previous output by n number 
string Continue();                                          // Get User Input and Check with sample 
string ColorText(string, string);                                    // Colors the text

int main() {
    // Init Variable
    string username;                // Player name
    string locations;               // Locations of the game
    int current_loc {};             // Current location that player is in

    // Welcome User
    // HideOutput(15);

    // RenderText("Hello Stranger..\n");
    // RenderText("Your name...?: \033[33m");
    // getline(cin, username);
    // cout << "\033[0m";
    // username = ColorText(username, "green");      // Add color to player name
    // HideOutput(15);

    // RenderText("Hello, ");
    // RenderText(username.c_str());       // (Change the string to c string)
    // RenderText("\nWelcome to \033[36m.{Silver Grit}.\033[0m\n");
    
    // Continue();


    // Epilogue
    string dialogues[][4] {
        {"Hello stranger, you are..\n", "40", "enter"},
        {"WAIT.... \n", "150", "continue"},
        {"Aren't you one of those heros that fought Mighty Evil???\n", "35", "enter"},
        {"You are getting nowhere with those wounds.\n", "40", "enter"},
        {"There is a village nearby. You should visit it.\n", "40", "enter"},
        {"Here ", "50", "continue"},
        {"take this. ", "50", "continue"},
        {"It will guide you.\n", "40", "enter"}
    };

    for (int idx=0; idx<8; idx++) {
        if (dialogues[idx][2] == "continue") cout << ColorText("[NPC] ", "yellow");
        RenderText(dialogues[idx][0].c_str(), durations[dialogues[idx][1]]);
        if (dialogues[idx][2] == "enter") Continue();
    }

    return 0;
}


// Purpose: To render a text a each character at a time just like how dialogues are rendered in games
// Specification: It loops through the character array until it reaches to the end or null character
// and print out each character then sleep for 20 milliseconds, then loop again.
// Arguments: Required char array and ending option to end the display with endl or not
void RenderText(const char msg[], chrono::milliseconds duration) {
    for (int idx=0; msg[idx] != '\0'; idx++) {
        cout << msg[idx] << flush;
        sleep_for(duration);
    }
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

// Purpose: To get any input from user
// Specification: Requests an input from user and returns it
// Arguments: not required
string Continue() {
    cout << "[ENTER To Continue]";

    string user_input; // partial init
    getline(cin, user_input);
    
    HideOutput(15);
    return user_input;
}

string ColorText(string text, string color) {
    text = COLORS[color] + text + COLORS["reset"];
    return text;
}
