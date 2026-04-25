/*
Zaw Ye Yaint Naing

CS162 Winter - Mitch Priestley

Purpose: The purpose of this homework is to build a functioning game that 
evokes player's feelings just like they are actaully playing an interactive 
game rather than in command-line game. The main purpose is to introduce 
game feels to the player even in the command line. 

Specification: It involve managing different dialogues, travel advancements
in linear progress, color texts and speed of text rendering. The dialogue 
mechanics uses pointers to make the code dynamic for choosing which dialogues 
to play.

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
#include <random>

using namespace std;
using namespace chrono_literals;
using namespace this_thread;
using namespace chrono;

//////////////////////////////////////////////////////////////////////////////////////////////
// Global Consts
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

//////////////////////////////////////////////////////////////////////////////////////////////
// Func Prototypes
void RenderText(
    const char[], 
    milliseconds duration = 40ms);          // Display text at a pace just like in actual games
void HideOutput(int);                       // Hide the previous output by n number 
string WaitUser();                          // Get User Input and Check with sample 
string ColorText(string, string);           // Colors the text
int GetInput(int, int);                     // Get int user input
void ShowMap(string[], int, int);           // Display Map
int generateRandomInt(int);                 // Generate Random Number
void ShowPlayerOption();                     // Show player mechanics

//////////////////////////////////////////////////////////////////////////////////////////////
// Structs
struct Dialogue {
    string entity;                                  // Narrator such as "[NPC]" in color
    string msg;                                     // Dialogue of a entity or place
    milliseconds pace = 40ms;                       // Render speed 40 milliseconds
    bool display_entity = false;                    // display entity name or not
    bool is_interactive = false;                    // user interaction
    int wait = 0;                                   // seconds to wait before passing to another dialogue

    void display() {
        if (display_entity)                         // Display entity name
            cout << ColorText(entity, "yellow");
        else  if (this->entity.length() != 0)
            cout << left << setw(entity.length()) << " ";

        RenderText(msg.c_str(), pace);              // Render Dialogue
        sleep_for(milliseconds(wait));
        if (is_interactive) WaitUser();             // wait for player interaction
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    // Init Variable
    string username;                                // Player name
    string locations[] {                            // Locations of the game
        "Main", 
        "Village", 
        "?"};               
    int discovered_locs {0};                        // Discovered locations
    int current_loc {0};                            // Current location that player is in
    int previous_loc = current_loc;                 // keeps tracks of locations
    string weapons[4] {
        ColorText("Arch Katana", "blue"), 
        ColorText("Chain & Sickle", "yellow"),
        ColorText("Crimson Oak Stick", "red"),
        ColorText("Heavens' Spear", "cyan")
    };
    int current_weapon = 0;
    bool is_running = true;                         // game state

    // Dialogues
    Dialogue system_dialogues[][20][wait_time] {
        // Order 1
        // Intro/Welcome user
        {   
            {"", "Hey Stranger..\n"},
            {"", "Your name...?: \033[32m"},

            {"<getname>"},

            {"", "Hello, "},
            {"<username>"},

            {"", "Welcome to \033[36m.{Silver Grit}.\033[0m\n", 40ms, false, true},

            {"<switchToEntity>"}
        },

        // Order 3
        {
            {"", ColorText("You have acquired the Map.\n", "cyan"), 80ms, false, true},

            {"<displayMap>"},
            
            {"", "\nEnter the location you like to go: ", 40ms, false, false},
            
            {"<getInput>", ""}
        },

        // Order 4
        // Map Selection Narratives
        {
            {"", "New adventure waits ahead!\n", 40ms, false, false, 350},
            {"", "Let's GO!!\n", 40ms, false, false, 350},
            {"", "...!\n", 1000ms},
            {"", "You have reached the destination!\n", 40ms, false, true},

            {"<switchToEntity>"}
        },

        // Order 6
        {
            {"",    "....!\n", 1000ms, false, false},
            {"",    ColorText("You have been regenerated!\n", "cyan"), 80ms, false, true},

            {"<switchToEntity>"}
        },

        // Order 8
        // Random Weapon Selection
        {
            {"", ColorText("You have acquired " + weapons[generateRandomInt(4)], "cyan") + ".\n", 80ms, false, true},
            
            {"<switchToEntity>"}
        },

        // Order 10
        {
            {"", ColorText("New location discovered.\n", "cyan"), 80ms, false, true},

            {"<updateMap>"},
            {"<displayMap>"},
            {"", "\nEnter the location you like to go: ", 40ms, false, false},

            {"<getInput>"},

            {"", "\n....!\n", 1000ms, false, false},
            {"", "You have reached the destination!\n", 40ms, false, true},

            {"<switchToEntity>"}
        }
    };
    Dialogue entity_dialogues[][20][wait_time] {
        // Order 2
        // Epilogue
        {
            {"[NPC] ",   "Hello stranger, ", 40ms, true},
            {"",        "you are..\n", 80ms, false, true},

            {"[NPC] ",   "WAIT.... ", 80ms, true},
            {"",        "Aren't you one of those heros that fought ", 10ms, false},
            {"",        ColorText("Mighty Evil???\n", "red"), 150ms, false, true},

            {"[NPC] ",   "Ahhh...\n", 80ms, true, false, 100},
            {"[NPC] ",   "My instincts are still correct.\n", 40ms, false, false, 100},
            {"[NPC] ",   "But you are not getting anywhere with those " + ColorText("wounds.\n", "red"), 40ms},
            {"[NPC] ",   "There is a " + ColorText("village", "cyan") + " nearby. You should visit it.\n", 40ms, false, true},

            {"[NPC] ",   "Here, ", 50ms, true, false, 300},
            {"",        "take this. ", 30ms, false, false, 300},
            {"",        "It will guide you.\n", 40ms, false, true},

            {"<switchToSystem>"}
        },

        // Order 5
        // Village
        {
            {"[Village Host] ",     "Ohh my...\n", 80ms, true},
            {"[Village Host] ",     "What had happened to you to look that red with all those wounds? "},
            {"<username>",          "", 40ms, false, true},

            {"[Village Host] ",     "Yeah....\n", 100ms, true},
            {"[Village Host] ",     "They have been destroying everything in their way...\n", 40ms, false, true},
            
            {"[Village Host] ",     "They also took my daughter...\n", 80ms, true},
            {"[Village Host] ",     "I am very worried of her but we are so hopeless....\n", 80ms, false, true},

            {"[Village Host] ",     "Please save her from ", 40ms, true},
            {"",                    ColorText("Thord.\n", "red"), 100ms},
            {"[Village Host] ",     "I beg you please!\n", 40ms, false, true},

            {"[Player] ",           "....\n", 800ms, true, true},

            {"[Village Host] ",     "Does that silence mean ", 40ms, true},
            {"",     ColorText("Yes", "cyan")+"?\n", 40ms, false, true},

            {"[Village Host] ",     "Thank you my son! ", 40ms, true},
            {"",                    "I owe you a lot!\n", 40ms, false, true},
            
            {"[Village Host] ",     "Please rest at our tent, ", 30ms, true, false, 500},
            {"",                    "We will treat your wounds for you.\n", 40ms, false, true},

            {"<switchToSystem>"}
        },

        // Order 7
        {
            {"[Village Host] ", "You should have a ", 40ms, true},
            {"",                ColorText("weapon", "cyan")},
            {"",                " before you go.\n", 40ms, false, true},

            {"[Village Host] ", "We have great smiths and artisans in this village.\n", 40ms, true},
            {"[Village Host] ", "Here, open this chest.\n", 40ms, false, true},

            {"[Village Host] ", "It is a legendary chest that gives the people best weapons that are destined.\n", 40ms, true, true},

            {"<switchToSystem>"}
        },

        // Order 9
        {
            {"[Village Host] ", "What a incredible weapon!\n", 40ms, true},
            {"[Village Host] ", "I have never seen someone gets a weapon this powerful!\n", 40ms, false, true},

            {"[Player] ",       "....\n", 800ms, true, true},
            
            {"[Player] ",       "Where is your daughter?\n", 40ms, true, true},

            {"[Village Host] ", "She is held at the " + ColorText("Crimson Chamber", "red") + ".\n", 40ms, true, true},

            {"[Player] ",       "Wait till I return.\n", 80ms, true, true},

            {"<switchToSystem>"}
        },

        // Order 11
        {
            {"[Thord] ",        ColorText("Who is there!\n", "red"), 40ms, true, true},

            {"[Player] ",       "....\n", 80ms, true, true},
            
            {"[Thord] ",        ColorText("YOU DARE STAY IN SILENCE WHILE I AM ASKING???\n", "red"), 20ms, true},
            {"[Thord] ",        ColorText("PREPARE TO DIE WITH MY ATTACK!\n", "red"), 20ms, false, true},

            {"<giveControl>"}
        }
    };
    
    // Dialogue mechanics
    bool give_control = false;
    int player_choice = 0;
    Dialogue *current_dialogue = nullptr;           // ptr that points to corresponding dialogue
    string display_mode = "system";                 // Display mode used to determine which dialogue to display (system or entity)
    int entity_dialogue_idx = 0;                    // Index of dialogue block
    int system_dialogue_idx = 0;                    // Index of dialogue block

    // Display Dialogues
    current_dialogue = &system_dialogues[0][0][0];  // Point to the address of corresponding dialogue
    int *block = &system_dialogue_idx;              // One Dialoge Block [][]
    
    while (is_running == true) {                    // Game Order
        give_control = false;                       // reset 

        for (int line=0; line<20; line++) {         // dialogue
            
            // Update current dialogue pointer
            if (display_mode == "system")           // grab the system dialogue to display
                current_dialogue = &system_dialogues[*block][line][0];  
            else if (display_mode == "entity")      // grab the entity dialogye to display
                current_dialogue = &entity_dialogues[*block][line][0];
            
            // Check which dialogue pointer to point to for next dialogue 
            if (current_dialogue->entity == "<switchToEntity>") {
                *block += 1;                        // increment system dialogue index
                line = -1;                          // reset dialogue line
                block = &entity_dialogue_idx;       // switch to entity dialogue index
                display_mode = "entity";            // switch display mode to display entity dialogues

                // cout << "Switched to Entity Dialogue, Current Idx: " << *block << endl;

                continue;                           // skips code below
            } else if (current_dialogue->entity == "<switchToSystem>") {
                *block += 1;                        // Increment entity dialogue index      
                line = -1;                          // reset dialoge line
                block = &system_dialogue_idx;       // swich to system diallogue index 
                display_mode = "system";            // swith display mode to display system dialogues
                
                // cout << "Switched to System Dialogue. Current Idx: " << *block << endl;

                continue;                           // skips code below
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

            else if (current_dialogue->entity == "<updateMap>") {
                locations[2] = "Crimson Chamber";
                discovered_locs += 1;
                continue;
            }

            else if (current_dialogue->entity == "<getInput>") {
                current_loc = GetInput(0, discovered_locs+1);
                
                if (current_loc <= previous_loc) {
                    RenderText("You have reached that location already. Choose another one: ");
                    line = line-1;
                    continue;
                }

                previous_loc = current_loc;         // update location
            }

            else if (current_dialogue->entity == "<giveControl>") {
                give_control = true;
                break;
            }

            else if (current_dialogue->entity == "<end>")    {
                is_running = false;
                break;
            }

            current_dialogue->display();
        }

        // Choice of attack and consequences
        while (give_control == true) {
            ShowPlayerOption();
            player_choice = GetInput(0, 2);

            if (player_choice == 0) {
                RenderText("You have deflected his attack and killed in a blink instant!\n", 40ms);
                RenderText((ColorText("Thord", "red")+ " has been defeated!\n").c_str(), 40ms);
                give_control = false;
                is_running = false;
            } else {
                RenderText("You have dodged his attack.\n", 40ms);
                RenderText("Prepare for next attack!\n", 40ms);
            }
        }

        cout << endl;
        *block += 1;    // Increment to next dialogue block
        // cout << (block == &system_dialogue_idx ? "System Dialogue Idx: " :  "Entity Dialogue Idx: ") << *block << endl;
    };
    
    // Handshake
    cout << "Program Complete." << endl;
    
    // End Normally
    return 0;
}

//////////////////////////////////////////////////////////////////

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

    while (!(cin >> result) || (result < min) || (result > max)) {
        cin.clear();
        cin.ignore(1024, '\n');
        
        RenderText("You cannot select that.\n", 20ms);
        RenderText("Please enter again: ");
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
    for (int loc=0; loc<3; loc++) {
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

void ShowPlayerOption() {
    cout << "0. Attack\n1. Dodge\n";
    cout << "Your selection: ";
}

int generateRandomInt(int max) {
    static bool initialized {false};

    static mt19937 generator;  // Mersenne Twister

    // Initialize the random engine if not already done
    if (!initialized) {
        // Use a random device to seed the generator
        random_device rd;
        generator.seed(rd());

        initialized = true;
    }

    uniform_int_distribution<int> distribution(0, max - 1);
    
    return distribution(generator);
}

