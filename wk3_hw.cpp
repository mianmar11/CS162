/*
Zaw Ye Yaint Naing

CS162 Winter - Mitch Priestley

Purpose: The purpose of this homework is to build a functioning game that 
evokes player's feelings just like they are actaully playing an interactive 
game rather than in command-line game. The main purpose is to introduce 
game feels to the player even in the command line. 

Specification: It involve managing different dialogues, travel advancements
in linear progress, color texts and speed of text rendering. These will 
make the player feel like the game is interacting with them and not just 

Credits: StackOverflow, cppreference.com, W3School, IBM, Microsoft Learn,
Medium, BroCode(YT)
*/

#include <iostream>
#include <iterator> // for getting size of array 
#include <iomanip>
#include <cstring>
#include <string>
#include <chrono> // for chrono_literals
#include <thread> // for this_thread
#include <unordered_map> // hashmap or dictionary

using namespace std;
using namespace chrono_literals;
using namespace this_thread;
using namespace chrono;

// Global Consts
enum DIALOGUE_ORDER {EPILOGUE, MAP, };
enum DIALOGUE_HEADERS {entity, msg, pace, display_entity, is_interactive, wait_time};

unordered_map<string, string> COLORS {
    {"cyan",    "\033[36m"},
    {"yellow",  "\033[33m"},
    {"red",     "\033[31m"},
    {"green",   "\033[32m"},
    {"grey",    "\033[90m"},
    {"bold",    "\033[1m"},
    {"reset",   "\033[0m"}
};

unordered_map<string, milliseconds> DURATIONS {
    {"150", 150ms},
    {"40", 40ms},
    {"35", 35ms},
    {"10", 10ms}
};

// Func Prototypes
void RenderText(const char[], 
    milliseconds duration = 40ms);      // Display text at a pace just like in actual games
void HideOutput(int);                   // Hide the previous output by n number 
string WaitUser();                      // Get User Input and Check with sample 
string ColorText(string, string);       // Colors the text
int GetInput(int, int);                 // Get int user input
void ShowMap(string[], int, int);

// Structs
struct Dialogue {
    string entity;                      // Narrator such as "[NPC]" in color
    string msg;                         // Dialogue of a entity or place
    milliseconds pace = 40ms;           // Render speed 40 milliseconds
    bool display_entity = false;         // display entity name or not
    bool is_interactive = false;        // user interaction
    int wait = 0;                       // seconds to wait before passing to another dialogue

    void display() {
        entity += " ";

        if (display_entity)             // Display entity name
            cout << ColorText(entity, "yellow");
        else 
            cout << left << setw(entity.length()) << " ";

        RenderText(msg.c_str(), pace);  // Render Dialogue
        sleep_for(milliseconds(wait));
        if (is_interactive) WaitUser(); // wait for player interaction
    }
};


int main() {
    // Init Variable
    string username;                        // Player name
    string locations[] {                    // Locations of the game
        "Main", 
        "Village", 
        "Dark Woods", 
        "Underground", 
        "?"};               
    int discovered_locs {0};                // Discovered locations
    int current_loc {0};                    // Current location that player is in
    int previous_loc = current_loc;         // keeps tracks of locations
    bool display_system_dialogue = true;    // false will display entity dialogues

    // Dialogues
    Dialogue entity_dialogues[][20][wait_time] {
        // Epilogue
        {
            {"[NPC]",   "Hello stranger,", 40ms, true},
            {"",        "you are..\n", 80ms, false, true},

            {"[NPC]",   "WAIT....", 80ms, true},
            {"",        "Aren't you one of those heros that fought", 10ms, false},
            {"",        ColorText("Mighty Evil???\n", "red"), 150ms, false, true},

            {"[NPC]",   "Ahhh...\n", 80ms, true, false, 100},
            {"[NPC]",   "My instincts are still correct.\n", 40ms, false, false, 100},
            {"[NPC]",   "But you are not getting anywhere with those " + ColorText("wounds.\n", "red"), 40ms},
            {"[NPC]",   "There is a " + ColorText("village", "cyan") + " nearby. You should visit it.\n", 40ms, false, true},

            {"[NPC]",   "Here,", 50ms, true, false, 300},
            {"",        "take this.", 30ms, false, false, 300},
            {"",        "It will guide you.\n", 40ms, false, true},
            {"<swapToSystem>"}
        },
    };
    Dialogue system_dialogues[][20][wait_time] {
        // Intro/Welcome user
        {
            {"", "Hey Stranger..\n"},
            {"", "Your name...?: \033[32m"},
            {"<getname>"},

            {"", "Hello,"},
            {"<username>", ""},
            {"", "Welcome to \033[36m.{Silver Grit}.\033[0m\n", 40ms, false, true},
            {"<swapToEntity>"}
        },

        {
            {"", "You have acquired the " + ColorText("Map", "yellow") + ".\n", 150ms, false, true},
            {"<displayMap>"},
            {"", "\nEnter the location you like to go: ", 40ms, false, false},
            {"<getInput>", ""}
        },

        // Map Selection Narratives
        {   
            // Same Direction Dialogues
            {"", "Just wandering around?\n", 40ms, false, true, 350},
            {"", "Alright then.\n", 40ms, false, false, 350},
            {"", "Let's wander around.\n", 40ms, false, false, 350},
            {"", "...!\n", 100ms},
            {"", "You have reached the destination!\n"},
            {"<end>"},

            {"", "Are you sure you want to be in the same place?\n", 40ms, false, true, 350},
            {"", "As you wish.\n", 40ms, false, false, 350},
            {"", "Enjoy some views while taking a break.\n", 40ms, false, false, 350},
            {"", "...!\n", 100ms},
            {"", "You have reached the destination!\n"},

            {"", "You do have time before your next adventure huh?\n", 40ms, false, true, 350},
            {"", "Alright.\n", 40ms, false, false, 350},
            {"", "Take your time.\n", 40ms, false, false, 350},
            {"", "...!\n", 100ms},
            {"", "You have reached the destination!\n"},
        }, 

        // New Direction Dialogues
        {
            {"", "New adventure waits ahead!\n", 40ms, false, false, 350},
            {"", "Let's GO!!\n", 40ms, false, false, 350},
            {"", "...!\n", 100ms},
            {"", "You have reached the destination!\n"},
        }
        
    };
    Dialogue *current_dialogue = nullptr;
    string display_mode = "system";
    int entity_dialogue_idx = 0;            // Index of dialogue block
    int system_dialogue_idx = 0;            // Index of dialogue block

    // Display Dialogues
    current_dialogue = &system_dialogues[0][0][0];  // Point to the address of corresponding dialogue
    // current_dialogue->display();
    // system_dialogues[0][0]->display();
    // cout << current_dialogue+ << ' ' << system_dialogues[0][1] << endl;
    // cout << (system_dialogues[0][0]) << endl;
    // (system_dialogues[0][1])->display();
    int *block = &system_dialogue_idx;
    // current_dialogue->display();
    
    while (*block < 3) {                            // Game Order
        for (int line=4; line<20; line++) {         // dialogue
            
            // update current dialogue pointer
            if (display_mode == "system")
                current_dialogue = &system_dialogues[*block][line][0];
            else if (display_mode == "entity")
                current_dialogue = &entity_dialogues[*block][line][0];
            
            // check which dialogue pointer to point to for next dialogue 
            if (current_dialogue->entity == "<swapToEntity>") {
                *block += 1;
                line = -1;
                block = &entity_dialogue_idx;
                display_mode = "entity";
                continue;
            } else if (current_dialogue->entity == "<swapToSystem>") {
                *block += 1;
                line = -1;
                block = &system_dialogue_idx;
                display_mode = "system";
                continue;

            }

            // Game Input 
            if (current_dialogue->entity == "<getname>") {
                
                // Input Username
                getline(cin, username);
                cout << "\033[0m";
                
                // Color Text
                username = ColorText(username, "green");
                HideOutput(15);
                
                // Skips to new loop to prevent from setw() empty on next line
                continue;
            }

            else if (current_dialogue->entity == "<username>") {
                current_dialogue->msg = username + "\n";    // change to output 
                current_dialogue->entity = "";              // delete string 
            }

            else if (current_dialogue->entity == "<displayMap>") {
                ShowMap(locations, current_loc, discovered_locs);
                continue;
            }

            else if (current_dialogue->entity == "<getInput>") {
                current_loc = GetInput(0, discovered_locs+1);
                
                if (current_loc == previous_loc) { // went the same place
                    RenderText("Just wandering around? ", 40ms);
                    sleep_for(350ms);
                    RenderText("Alright then.\n");
                    sleep_for(350ms);
                    RenderText("Let's wander around.\n");
                    sleep_for(350ms);
                    RenderText("...!\n", 1000ms);
                    RenderText("You have reached the destination!\n");

                    ShowMap(locations, current_loc, discovered_locs);
                }
            }

            current_dialogue->display();
        }
        cout << endl;
        *block += 1;
    };
    
    
    return 0;
}


// Purpose: To render a text a each character at a time just like how dialogues are rendered in games
// Specification: It loops through the character array until it reaches to the end or null character
// and print out each character then sleep for 20 milliseconds, then loop again.
// Arguments: Required char array and ending option to end the display with endl or not
void RenderText(const char msg[], milliseconds duration) {
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
int GetInput(int min, int max) {
    int result = 0;

    while (!(cin >> result) || (result < min) || (result >= max)) {
        cin.clear();
        cin.ignore(1024, '\n');
        
        cout << "You cannot go the the location that does not exist!" << endl;
        cout << "Please enter again: ";
    }

    return result;
}

// Purpose: To get any input from user
// Specification: Requests an input from user and returns it
// Arguments: not required
string WaitUser() {
    cout << "[ENTER To Continue]";

    string user_input; // partial init
    getline(cin, user_input);
    
    HideOutput(15);
    return user_input;
}

// Purpose: To color a string using ANSI color code
// Specification: color a text from one of the preset colors from global hashmap and returns it back
// Arguments: required a string text and string color name 
string ColorText(string text, string color) {
    text = COLORS[color] + text + COLORS["reset"];
    return text;
}

void ShowMap(string locations[], int current, int discovered) {
    for (int loc=0; loc<5; loc++) {
        cout << loc << ". ";

        // Display Current Location
        if (current == loc) {
            RenderText(ColorText(locations[loc], "bold").c_str());
            cout << setw(5) << " " << ColorText("(You are here)", "bold"); 
        }

        // Display Location Names
        else if (loc <= discovered)
            RenderText(locations[loc].c_str());
        else
            RenderText(ColorText(locations[loc], "grey").c_str());
        
        cout << endl;
    }
}
