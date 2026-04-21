// Adventure Engine : For text-based adventure game files
// Adventure.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: Mitch Priestley
// Created 11/25/2019 (C++ version)  Originally created in 11/15/1980 and written in Pascal.
// Rev. 11/30/19, 12/19/22

#include <iostream>
#include <iomanip>
#include <fstream>

#include <string>
#include <stdio.h>
#include <ctype.h>
#include <windows.h>												// To use Sleep(ms).
#include <stdlib.h>													// To use rand().
#include <algorithm>												// To use all_of
//#include <boost.h>												// To use include_all

#define WITH(x) { \
        auto &_ = x;

#define END_WITH() }

using namespace std;

//CONST
	const bool T = true;
	const bool F = false;
		  bool DEBUG = F;											// Overridden by data file
		  bool VERBOSE = F;											// Overridden by data file
		  bool TRACE_LOCATION = F;									// Overridden by data file
		  bool PRIVILEGED = F;										// Overridden by data file
	const int MAX_LOCATIONS = 500;									// Maximum map size
	const int MAX_ROOMS = 500;										// Maximum number of locations that can have names
	const int MAX_OBJECTS = 500;									// Objects can have points, weights and be required, e.g., to perform verbs
	const int MAX_STATES_FOR_OBJECTS = 10;							// e.g., wet, dry, ablaze; or dull, shiny
	const int MAX_OBSTACLES = 500;									// Obstacles block the way of the player until eliminated
	const int MAX_VERBS = 500;										// Verbs are two-word phrases that manipluate the scene if the player holds the required object
	const int MAX_INPUT_SYNONYMS = 500;								// Input Synonyms are various ways the player might phrase something and still be recognized as matching a Verb, Response, etc.
	const int MAX_ENTRIES_PER_INPUT_SYNONYM = 20;					// Many synonomous phrases can be specified
	const int MAX_RESPONSES = 500;									// Includes hints, which are stored as a continuation of the responses array
	const int Q_CATEGORIES = 11;									// 11 categories are specified in the datafile with 11 specific headings
	const int Q_DIRECTIONS = 4;										// There are four built-in directions in the map
	const int Q_CONDITIONS = 4;
	const string categoryText[Q_CATEGORIES] = { "<params>", "<map_size>", "<rooms>", "<objects>", "<obstacles>", "<input_synonyms>", "<verbs>", "<responses>", "<hints>", "<output_synonyms>", "<locations>" };
	const string directionText[Q_DIRECTIONS + 1] = { "north", "south", "east", "west", "null_direction" };
	const string COMMENT_DELIMITER_STRING = "@";					// The datafile can have comments at the end of lines and they will be stripped away
	const int Q_MESSAGES = 1;										// There is a welcome message at the start of the game
	const char TAB = 9;												// ASCII 9 is a tab character, used as a delimiter in the data file, but stripped away
	const char EOL = 10;											// ASCII 10 is the end-of-line (EOL) character
	const char CLS = 12;											// To clear screen on some (Unix) systems
	const char SPACE = 32;											// ASCII 32 is the space, which separates words
	const char QUOTE = 34;											// ASCII 34 is a double quotation mark
	const char COMMENT_DELIMITER = 64;								// ASCII 64 is an at-sign (@) character, used in the datafile to begin comments that are to be ignored by the computer
	const size_t STRING_NOT_FOUND = string::npos;					// using a predefined constant from #include'd <string> to tell when a find fails (npos or "no position" is returned to the program from the find method)
	const int PLAYERS_POSSESSION = 0;								// Location 0 for objects means the object is in the player's possession.
	const int NO_REQUIREMENT = 0;									// 0 means no required location, object, or obstacle for a feature to work.
	const int NOWHERE = 0;											// A link to location 0 means there is no link to anywhere. This is how the map specifies a direction that a player can't go.
	const int NOT_FOUND = 0;										// "Find" functions return 0 if search item is not found.
	const int PROHIBITED_OBJECT = 1;								// Same value as ordinal of MISSING_OBJECT (see conditions, below)
	const int PROHIBITED_OBSTACLE = 2;								// Same value as ordinal of MISSING_OBSTACLE (see conditions, below)
																	// Features can depend upon a required or prohibited object or obstacle in order to be enabled, as specified in the data file.
																	// The objects or obstacles are referred to by their number. If the number is positive, it is required; negative, prohibited.

//TYPE
	enum categories { PARAMS, MAP_SIZE, ROOMS, OBJECTS, OBSTACLES, INPUT_SYNONYMS, VERBS, RESPONSES, HINTS, OUTPUT_SYNONYMS, LOCATIONS };
	enum directions { NORTH, SOUTH, EAST, WEST, NULL_DIRECTION };
	enum conditions { WRONG_LOCATION, MISSING_OBJECT, MISSING_OBSTACLE, SUCCESS };
	enum messages { WELCOME };
	enum left$OptionType { EXCLUSIVE, INCLUSIVE };

	struct objects
	{
		string name = "";
		int location = 0;
		int points = 0;
		int weight = 0;
		string state[MAX_STATES_FOR_OBJECTS + 1] = { "" };
		string short_desc[MAX_STATES_FOR_OBJECTS + 1] = { "" };
		string description[MAX_STATES_FOR_OBJECTS + 1] = { "" };
		string set_state_command[MAX_STATES_FOR_OBJECTS + 1][2]= { "" };
		int set_condition[MAX_STATES_FOR_OBJECTS + 1] = { 0 };
		int absorbed_object[MAX_STATES_FOR_OBJECTS + 1] = { 0 };
		int current_state = 1;
	};

	struct obstacles
	{
		int location = 0;
		string name = "";
		string description = ""; 
	};

	struct input_synonyms
	{
		int req_loc = 0;
		int req_obj = 0;
		int req_state = 0;
		string first[MAX_ENTRIES_PER_INPUT_SYNONYM] = { "" };
		string second[MAX_ENTRIES_PER_INPUT_SYNONYM] = { "" };
	};	
	
	struct verbs
	{
		string first = "", second = "";
		int req_loc = 0, req_obj = 0, req_obs = 0;
		string feedback[Q_CONDITIONS] = { "" };
		int old_loc[2] = { 0 }, new_loc[2] = { 0 };		// Can move player from x1 to y1 OR x2 to y2; if x1 or x2 is 0, meaning "anywhere" then the move is unconditional; negative, from anywhere but there.
		int new_obj_loc = 0, new_obs_loc = 0;			// The required object can be moved. E.g., a burnt match can be sent to oblivion (-1).
		int bonus_obj = 0, bonus_obj_loc = 0;			// A verb can cause an object to appear at any location; if location 0, then in the player's possession.
	};

	struct responses
	{
		string first, second;							// Specific two-word phrases typed by the user activate responses, as specified in the data file.
		int req_loc;									// Responses might work only at specific location (e.g., 49), or anywhere but that location (e.g., -49), or can work anywhere (0).
		int req_obj;									// Responses might work only if a required object is (positive #, or is not, negative #) present or in the player's possession; otherwise 0 is specified.
		int req_state;									// Reponses might work only if the required object is in the specified required state (e.g., only dry sticks will burn).
		string feedback;								// If all required conditions are met (if any), then the player receives the feedback in response to the player's matching two word phrase.
	};

	struct locations									// The map is a set of locations, each one with a set of links to other locations, one link for each direction N, S, E, W.
	{
		string room_name = "";							// The data file can give some rooms names.
		int link[Q_DIRECTIONS] = { 0 };					// Data for adjacency of map locations. 0 means there is nowhere that a direction links to.
		string description = "";						// Every location has a description that the player gets to read, describing where they are.
	};

	// typedef responses hints;							// Hints have the same structure as responses
														// In fact, hints are simply stored as responses

	struct cmds
	{
		string raw = "" ;								// The original command string typed by the player is retained.
		string refined =  "" ;							// The user  input is refined through synonyms.
	};




//VAR
string message[Q_MESSAGES] = { "" };					// Welcome message, etc.
directions dir;
conditions condition;
objects object[MAX_OBJECTS];
obstacles obstacle[MAX_OBSTACLES];
input_synonyms input_synonym[MAX_INPUT_SYNONYMS];
verbs verb[MAX_VERBS];
responses response[MAX_RESPONSES];
locations location[MAX_LOCATIONS];
ifstream data_file;
int current_location = 1, last_location = NOWHERE;
cmds cmd[2];
int quan[Q_CATEGORIES] = { 0 };							// Stores the count of items in each category
int max_ttl_points;

//FUNCTION PROTOTYPES
bool initialize();
string ucase(string str);
bool match(string rule, string attempt);
bool match_location(int req_loc);
bool match_location(objects obj);
bool match_object(int req_obj);
bool match_state(int req_obj, int req_state);
directions find_direction(string str);
bool find_set_state_command(string str1, string str2, int &obj_idx, int &state_idx);
int find_verb(string str1, string str2);
int find_response(string str1, string str2);
bool is_direction(string str);
bool is_adjacent(int where);
int obs(int where);
int find_room(string str);
void get_word(ifstream& infile, string& word);
void describe(int where);
void checkscore();
void test();
void skip_white_space(ifstream& infile);
string left$(string s, int len);
string left$(string s, string delimiter, left$OptionType = EXCLUSIVE);
string right$(string s, int len);
string capitalize(string s);
string trim(string s, char c = ' ');
string rtrim(string s, char c = ' ');
string lexiSpeechNoNesting(string S);
int    lexiSpeechDepth(string S);
string lexiSpeechDeepest(string S);
string lexiSpeech(string S);
string CPerson(string S, int fromPerson, int toPerson);
string WordReplace(string pText, string pSearchString, string pReplacementString);
string reflect(string S);
void split(string Expression, string Delimiter, size_t Limit, string Str[], size_t& count);
void remove_comment(string& str);
void typeOut(string s);
void typeOutln(string s);




int main()
{
	char dummy_ch;
	int obj_idx;

	if (!initialize()) {
		cout << "Failure during initialization.";
		return 1;
	}
	cout << "Initialization successful. \n\n";
	current_location = 1;

	do
	{
		if (current_location < 0 || current_location > MAX_LOCATIONS)
		{
			cout << "\n\nGame over.\n";
			return 0;
		}

		if (current_location != last_location)
			describe(current_location);

		typeOut("\n>");														// PROMPT

		cin >> cmd[0].raw;
		while (cin.peek() == SPACE)
			cin.get(dummy_ch);
		if (cin.peek() != EOL)
		{
			cin >> cmd[1].raw;
			if (cmd[1].raw.back() == '.' || cmd[1].raw.back() == '!')
				cmd[1].raw.pop_back();
		}
		else
			cmd[1].raw = "";
		cout << endl;

		cmd[0].refined = cmd[0].raw;
		if (cmd[1].raw == "")
			cmd[1].refined = ".";
		else
			cmd[1].refined = cmd[1].raw;
		for (int idx = 1; idx <= quan[INPUT_SYNONYMS]; idx++)  // problem here always checking negative subscripts!
		{
			WITH(input_synonym[idx])

				if (_.req_loc > 0 && _.req_loc != current_location || _.req_loc < 0 && -_.req_loc == current_location)
					continue;
				if (_.req_obj > 0)
				{
	//				if (object[_.req_obj].location != PLAYERS_POSSESSION && object[_.req_obj].location != current_location)
						if (!match_location(object[_.req_obj]))
							continue;
					if (_.req_state > 0 && object[_.req_obj].current_state != _.req_state
						|| _.req_state < 0 && object[_.req_obj].current_state == -_.req_state)
						continue;
				}
				if (_.req_obj < 0)
	//				if (object[-_.req_obj].location == PLAYERS_POSSESSION || object[-_.req_obj].location == current_location)
						if (match_location(object[-_.req_obj]))
							continue;
				for (int syn_idx = 1; syn_idx < MAX_ENTRIES_PER_INPUT_SYNONYM; syn_idx++)
					if (match(input_synonym[idx].first[syn_idx], cmd[0].refined) && match(input_synonym[idx].second[syn_idx], cmd[1].refined))
						// APPLY SYNONYM BECAUSE LOCATION, OBJECT, AND OBJECT STATE CONDITIONS ALL ARE MET
					{
						if (DEBUG && VERBOSE)
							cout << "Synonym Match: " 
							<< "'" << input_synonym[idx].first[syn_idx] << " " << input_synonym[idx].second[syn_idx] << "' ==> "
							<< "'" << input_synonym[idx].first[0] << " " << input_synonym[idx].second[0] << "'"
							<< endl;
						if (input_synonym[idx].first[0] != "*")
							cmd[0].refined = input_synonym[idx].first[0];
						if (input_synonym[idx].second[0] != "*")
							cmd[1].refined = input_synonym[idx].second[0];
					}
			END_WITH();
		}
		//echo
		if (DEBUG)
			cout << cmd[0].refined << " " << cmd[1].refined << endl;

		int destination = find_room(cmd[0].refined + ((cmd[1].refined != ".") ? " " + cmd[1].refined : ""));
		if (DEBUG && (VERBOSE || destination != 0))
			cout << "(That room is loc " << destination << ")" << endl;

		int resp_idx = find_response(cmd[0].refined, cmd[1].refined);
		int obj_idx, state_idx;
		bool state_command = find_set_state_command(cmd[0].refined, cmd[1].refined, obj_idx, state_idx);


		if (match("LOC", cmd[0].raw) && PRIVILEGED)
		{
			if (cmd[1].raw.length() > 0 && std::all_of(cmd[1].raw.begin(), cmd[1].raw.end(), isdigit))
			{
				int loc_number = stoi(cmd[1].raw);
				if (loc_number >= 1 && loc_number < MAX_LOCATIONS)
				{
					current_location = loc_number;
					if (loc_number > quan[LOCATIONS])
						cout << "Warning: This location is beyond the " << quan[LOCATIONS] << " that have been defined. \n";
				}
				else
					cout << "Error: That location is outside the valid range. \n";
			}
			else
				cout << "Error: Location # must be numeric. \n";
		}
		else if (find_verb(cmd[0].refined, cmd[1].refined) > 0)								// It's a verb!
		{
			int verb_idx = find_verb(cmd[0].refined, cmd[1].refined);
			if (verb[verb_idx].req_obj > 0 && object[verb[verb_idx].req_obj].location != PLAYERS_POSSESSION && object[verb[verb_idx].req_obj].location != current_location)
				typeOutln(verb[verb_idx].feedback[MISSING_OBJECT]);
			else if (verb[verb_idx].req_obj < 0 && object[-verb[verb_idx].req_obj].location == PLAYERS_POSSESSION && object[-verb[verb_idx].req_obj].location != current_location)
				typeOutln(verb[verb_idx].feedback[PROHIBITED_OBJECT]);
			else if (verb[verb_idx].req_obs > 0 && obstacle[verb[verb_idx].req_obs].location != current_location && !is_adjacent(obstacle[verb[verb_idx].req_obs].location))
				typeOutln(verb[verb_idx].feedback[MISSING_OBSTACLE]);
			else if (verb[verb_idx].req_obs < 0 && (obstacle[-verb[verb_idx].req_obs].location == current_location || is_adjacent(obstacle[-verb[verb_idx].req_obs].location)))
				typeOutln(verb[verb_idx].feedback[PROHIBITED_OBSTACLE]);
			else if (verb[verb_idx].req_loc > 0 && verb[verb_idx].req_loc != current_location && !is_adjacent(verb[verb_idx].req_loc))
				typeOutln(verb[verb_idx].feedback[WRONG_LOCATION]);
			else if (verb[verb_idx].req_loc < 0 && -verb[verb_idx].req_loc == current_location)
				typeOutln(verb[verb_idx].feedback[WRONG_LOCATION]);
			else																		// Perform the verb! (have obj, obst exists, correct loc)
			{
				object[verb[verb_idx].req_obj].location = verb[verb_idx].new_obj_loc;	// Zero means into Player's Possession
				if (verb[verb_idx].new_obs_loc != 0)									// Zero means no change to obstacle location; -1 means oblivion
					obstacle[verb[verb_idx].req_obs].location = verb[verb_idx].new_obs_loc;
				if (verb[verb_idx].old_loc[0] == current_location || verb[verb_idx].old_loc[0] == 0 && verb[verb_idx].new_loc[0] != 0)		// Loc 0 is a wildcard (if there's a dest.)
					current_location = verb[verb_idx].new_loc[0];
				else if (verb[verb_idx].old_loc[1] == current_location || verb[verb_idx].old_loc[1] == 0 && verb[verb_idx].new_loc[1] != 0)
					current_location = verb[verb_idx].new_loc[1];
				if (verb[verb_idx].bonus_obj != 0)
					if (verb[verb_idx].bonus_obj > 0)
						object[verb[verb_idx].bonus_obj].location = verb[verb_idx].bonus_obj_loc;
					else if (verb[verb_idx].bonus_obj < 0 && (object[-verb[verb_idx].bonus_obj].location == PLAYERS_POSSESSION || object[-verb[verb_idx].bonus_obj].location == current_location))
						object[verb[verb_idx].bonus_obj].location = verb[verb_idx].bonus_obj_loc;
				// Above, a negative object is taken away from player or vicinity (or moved from vicinity to player)
				typeOutln(verb[verb_idx].feedback[SUCCESS]);
			}
		}
		else if (resp_idx > 0 
			&& match_location(response[resp_idx].req_loc) 
			&& match_object(response[resp_idx].req_obj) 
			&& match_state(response[resp_idx].req_obj, response[resp_idx].req_state))	// Response case with conditions met (loc, obj, obj state)
		{		
				typeOutln(response[resp_idx].feedback);
		}
		else if (state_command)
		{
			
			if (!match_location(object[obj_idx]))
				typeOutln("{I am not seeing any|I don't see any|I don't find any|You find no|You don't have any} " + object[obj_idx].name + "{| here}!");
			else if (!match_location(object[object[obj_idx].absorbed_object[state_idx]].location))
				typeOutln("{I am not seeing any|I don't see any|I don't find any|You find no|You don't have any} " + object[object[obj_idx].absorbed_object[state_idx]].name + "{| here!}");
			else
			{
				string your_or_the = (object[obj_idx].location == PLAYERS_POSSESSION) ? "your " : "the ";
				if (object[obj_idx].current_state == state_idx)
				{
					string your_or_the = (object[obj_idx].location == PLAYERS_POSSESSION) ? "your " : "the ";
					string opt1 = ("The state of " + your_or_the + object[obj_idx].name + " is already " + object[obj_idx].state[state_idx] + "!");

					string opt2 = ("You already find " + your_or_the + object[obj_idx].name + " to be " + object[obj_idx].state[state_idx] + "!");
					typeOutln("{" + opt1 + "|" + opt2 + "}");

				}
				else if (object[obj_idx].set_condition[state_idx] > 0 && object[obj_idx].current_state != object[obj_idx].set_condition[state_idx])
					typeOutln("{Sorry|Well|Nope}, " + your_or_the + object[obj_idx].name
						+ " {must first be|must be} " + object[obj_idx].state[object[obj_idx].set_condition[state_idx]]
						+ " {before being|in order to be} " + object[obj_idx].state[state_idx] + ".");
				else if (object[obj_idx].set_condition[state_idx] < 0 && object[obj_idx].current_state == -object[obj_idx].set_condition[state_idx])
					typeOutln("The " + object[obj_idx].name
						+ " cannot be " + object[obj_idx].state[state_idx] + ","
						+ " because the current state of " + your_or_the + object[obj_idx].name + " is " + object[obj_idx].state[object[obj_idx].current_state] + ".");
				else
				{
					// APPLY STATE CHANGE
					if (object[object[obj_idx].absorbed_object[object[obj_idx].current_state]].location == -obj_idx)
						object[object[obj_idx].absorbed_object[object[obj_idx].current_state]].location = current_location;
					object[obj_idx].current_state = state_idx;
					string opt1 = ("The state of " + your_or_the + object[obj_idx].name + " is now " + object[obj_idx].state[state_idx] + ".");
					string opt2 = ("You now find " + your_or_the + object[obj_idx].name + " to be " + object[obj_idx].state[state_idx] + ".");
					string opt3 = (capitalize(your_or_the) + object[obj_idx].name + " became " + object[obj_idx].state[state_idx] + "!");
					typeOutln("{" + opt1 + "|" + opt2 + "|" + opt3 + "}");
					if (object[obj_idx].absorbed_object[state_idx] > 0)
						if (object[obj_idx].absorbed_object[state_idx] <= quan[OBJECTS])
							object[object[obj_idx].absorbed_object[state_idx]].location = -obj_idx;			// Absorbed into object #obj_idx

				}
			}
		}
		else if (match("CLS", cmd[0].refined))												// CLS Use two methods
		{
			cout << CLS;
			system("cls");
		}
		else if (match("LOOK", cmd[0].refined) || match("DESCRIBE", cmd[0].refined))		// LOOK, DESCRIBE
			describe(current_location);
		else if (match("GET", cmd[0].refined) || match("TAKE", cmd[0].refined) || match("GRAB", cmd[0].refined))	// GET, TAKE, GRAB
		{
			if (cmd[1].refined == "" || cmd[1].refined == ".")
				typeOutln("{You have to|I need you to|I can't help you if you don't} {tell me|specify|indicate|say|type|include} what to get!");
			else if (match("ALL", cmd[1].refined) || match("EVERYTHING", cmd[1].refined))
			{
				int count = 0;
				for (obj_idx = 1; obj_idx <= quan[OBJECTS]; obj_idx++)
				{
					if (object[obj_idx].location == current_location && object[obj_idx].weight != -1)
					{
						typeOutln("Getting " + object[obj_idx].name + ".");
						object[obj_idx].location = PLAYERS_POSSESSION;
						count++;
					}
				}
				if (count == 0) typeOutln("{There is nothing {|here }to get!|There isn't anything {|here }to get!} \n");
			}
			else
			{
				for (obj_idx = 1; obj_idx <= quan[OBJECTS]; obj_idx++)
					if (match(object[obj_idx].name, cmd[1].refined))
						break;
				if (obj_idx <= quan[OBJECTS] && match(object[obj_idx].name, cmd[1].refined))
					if (object[obj_idx].location == current_location)
						if (object[obj_idx].weight == -1)
							typeOutln("The " + object[obj_idx].name + " cannot be {carried|lifted|taken|gotten}!");
						else
						{

							{
								object[obj_idx].location = PLAYERS_POSSESSION;					// Location 0 represents being in the player's possession
								typeOutln("OK.");
							}
						}
					else if (object[obj_idx].location == PLAYERS_POSSESSION)
						typeOutln("You already {have|got|did get|picked up|grabbed|collected|are holding|are carrying|are in possession of} the " + object[obj_idx].name + "!");
					else
						typeOutln("{I don't see any|I am not seeing any|I don't find any|You find no|You see no|You don't see any|You don't find any|First, you would need to find some kind of|You haven't yet found any|You would need to search out some kind of|First, you would need to locate the|You are mistaken to think you have found the} " + cmd[1].raw + "{| here}.");
				else typeOutln("I don't know what that is.");
			}
			checkscore();
		}
		else if (match("DROP", cmd[0].refined) || match("LEAVE", cmd[0].refined))			// DROP, LEAVE
			if (cmd[1].refined == "" || cmd[1].refined == ".")
				typeOutln("{You have to|I need you to|I can't help you if you don't} {tell me|specify|indicate|say|type|include} what you want to drop!  ");
			else if (match("ALL", cmd[1].refined) || match("EVERYTHING", cmd[1].refined))
			{
				int count = 0;
				for (obj_idx = 1; obj_idx <= quan[OBJECTS]; obj_idx++)
				{
					if (object[obj_idx].location == PLAYERS_POSSESSION)
					{
						typeOutln("Dropping " + object[obj_idx].name + ".");
						object[obj_idx].location = current_location;
						count++;
					}
				}
				if (count == 0) typeOutln("{You have nothing to drop!|You don't have anything to drop!|You aren't {holding|carrying} anything!} ");
			}
			else
			{
				for (obj_idx = 1; obj_idx <= quan[OBJECTS]; obj_idx++)
					if (match(object[obj_idx].name, cmd[1].refined))
						break;
				if (obj_idx <= quan[OBJECTS] && match(object[obj_idx].name, cmd[1].refined))
					if (object[obj_idx].location == PLAYERS_POSSESSION)						// Location 0 represents being in the player's possession
					{
						object[obj_idx].location = current_location;						// Player drops object
						typeOutln("OK.");
					}
					else
						typeOutln("{You don't even have any|You have no} " + cmd[1].raw + "{|| to drop}.");
				else typeOutln("I don't know what that is.");
			}
		else if (ucase(cmd[0].refined) == "INVE" || ucase(cmd[0].refined) == "INVENTORY")
		{
			int item_count = 0;
			for (int obj_idx = 1; obj_idx <= quan[OBJECTS]; obj_idx++)
				if (object[obj_idx].location == PLAYERS_POSSESSION)
				{
					item_count++;
					if (item_count == 1) typeOutln("You are carrying the following items: ");
					typeOutln("  -" + object[obj_idx].short_desc[object[obj_idx].current_state]);
				}
			if (item_count == 0) typeOutln("You are not carrying anything. ");
		}
		else if ( ucase(cmd[0].refined) == "SCORE" || ucase(cmd[0].refined) == "POINTS" || ucase(cmd[0].refined) == "TREASURES" || ucase(cmd[0].refined) == "TREASURE" || ucase(cmd[0].refined)== "LIST" && (ucase(cmd[1].refined) == "TREASURES" || ucase(cmd[1].refined) == "TREASURE") )
		{
			int score = 0;
			for (int obj_idx = 1; obj_idx <= quan[OBJECTS]; obj_idx++)
				if (object[obj_idx].points > 0 && (object[obj_idx].location == PLAYERS_POSSESSION))
				{
					if (score == 0) typeOutln("You have collected the following treasures: ");
					cout << "  " << setw(20) << left << object[obj_idx].short_desc[object[obj_idx].current_state] << setw(5) << right << object[obj_idx].points << endl;
					score += object[obj_idx].points;
				}
			if (score == 0) typeOutln("You are not carrying any treasures.");
			else
				cout << "  " << setw(20) << left << "Total: " << setw(5) << right << score << endl;
		}
		else if (is_direction(cmd[0].refined))															// GO A DIRECTION
		{
			directions dir = find_direction(cmd[0].refined);
			if (location[current_location].link[dir] == NOWHERE)										// A link to zero means 'impossible.'
				typeOut("You cannot proceed " + directionText[dir] + " from here. \n");
			else
				if (obstacle[obs(location[current_location].link[dir])].location == location[current_location].link[dir])
				{
					typeOut("The way is blocked! ");
					typeOut("You cannot proceed " + directionText[dir] + ". ");
						typeOutln(obstacle[obs(location[current_location].link[dir])].description);		// Describe obstacles adjacent
				}
				else
				{
					if (location[current_location].link[dir] == current_location)
						describe(location[current_location].link[dir]);									// Force description of same location
					current_location = location[current_location].link[dir];
				}
		}
		else if (destination > 0)
			if (is_adjacent(destination))
				if (obs(destination))
					typeOutln("The way is blocked to " + location[destination].room_name + "! " 
					+ obstacle[obs(destination)].description);											// Describe obstacles adjacent
				else
					current_location = destination;
			else
				if (current_location == destination)
					typeOutln("That's where you are!");
				else typeOutln("I don't know how to get to that place! The current location is not adjacent to the " + location[destination].room_name + ". ");
		else if (resp_idx > 0)																			// Response case WITHOUT conditions met
		{
		if (!match_object(response[resp_idx].req_obj))
			if (response[resp_idx].req_obj > 0)
				typeOutln("You can't do that without any " + object[response[resp_idx].req_obj].name + "!");
			else
				typeOutln("You can't do that with the " + object[response[-resp_idx].req_obj].name + "right here!");

		else if (!match_location(response[resp_idx].req_loc))
			typeOutln("You can't " + trim(cmd[0].raw + " " + cmd[1].raw) + " here.");
		else if (DEBUG)
			cout << "Error in response cases." << endl;
		}

		else if (PRIVILEGED || DEBUG)
				if (ucase(cmd[0].refined) == "/TEST" && cmd[1].refined == ".")
					test();
				else if (match(cmd[0].refined, "/RELOAD"))
				{
					bool inventory[MAX_OBJECTS + 1] = { 0 };
					for (int i = 1; i <= quan[OBJECTS]; i++)
						inventory[i] = (object[i].location == PLAYERS_POSSESSION);

					if (!initialize())
					{
						cout << "Failure during initialization.";
						return 1;
					}
					cout << "Initialization successful. \n\n";
					// current_location = 1;

					for (int i = 1; i <= quan[OBJECTS]; i++)
						if (inventory[i])
							object[i].location = PLAYERS_POSSESSION;

				}

		else if (ucase(cmd[0].refined) != "QUIT")
		{
			typeOutln("I don't understand that. ");
		}
		{

		}
		{

		}
		{

		}
		{

		}



	} while (ucase(cmd[0].refined) != "QUIT");

	return 0;
}


bool initialize()
{
	string default_file_name = "C:\\Users\\mitch\\Desktop\\Mitch MAIN\\Adventure\\C++ Adventures\\ENCHANT.txt";
	string file_name = "";
	string text;
	ifstream infile;
	int line_count = 0;
	int num;
	int count;
	int idx, status;
	int state_idx = 1;
	string test_word;
	categories category;
	char ch, dummy_ch;

	max_ttl_points = 0;
	for (categories c = static_cast<categories>(0); c <= Q_CATEGORIES; c = static_cast<categories>(c + 1))
		quan[c] = 0;

	cout << "Starting..." << endl;
	cout << "Welcome to Adventure Gaming Engine" << endl;

	srand(time(0));
	if (DEBUG)
		cout << "A random number (0 - 99) is " << rand() % 100 << endl;

	message[WELCOME] = "";
	//message[OBSTACLE_WARNING] = "You cannot proceed in that direction until you have solved the obstacle.";


	if (default_file_name != "")
		cout << "The default game file is " << default_file_name << endl;
	cout << "Specify data filename for the game (or press Enter for default): ";
	getline(cin, file_name);
	cout << endl;
	if (file_name == "")
		file_name = default_file_name;
	else
	{
		if (file_name.back() == QUOTE)
			file_name.pop_back();
		if (file_name.front() == QUOTE)
			file_name.erase(0, 1);
		cout << file_name << endl << endl;
	}
	infile.open(file_name);
	if (!infile)
	{
		cout << "Attempt to open file failed: " << file_name << endl;
		return false;
	}

	for (category = static_cast<categories>(0); category < static_cast<categories>(Q_CATEGORIES); category = static_cast<categories>(category + 1))
	{
		quan[category] = 0;
		if (!infile) return false;						// Input failed, thereore initialization failed.
		skip_white_space(infile);						/* ignore comment line @ and white space */
		getline(infile, test_word);
		remove_comment(test_word);
		line_count++;
		if (DEBUG && VERBOSE) cout << test_word << endl;
	
		if (DEBUG && VERBOSE && false)
			cout << infile.peek() << '\'' << (infile.peek() > 32 ? static_cast<char>(infile.peek()) : ' ') << '\'' << endl;

		if (ucase(test_word) != ucase(categoryText[category]))
		{
			cout << "Line " << line_count << ": "
				<< " ?Error -- '" << categoryText[category] << "' not found. "
				<< "Instead found: " << test_word << endl;
			return false;
		}
		if (category == PARAMS)
		{
			infile >> DEBUG >> VERBOSE >> TRACE_LOCATION >> PRIVILEGED;
		}
		else if (category == MAP_SIZE)
		{
			infile >> quan[category];
			if (DEBUG)
				cout << "This game's <map_size> declaration specifies that it contains " << quan[MAP_SIZE] << " locations." << endl;
			else;
		}
		else 			// Normal Conditions... Load Game File
		{
			idx = 0;
			skip_white_space(infile);
			while (infile.peek() != '<' && infile.good())									// Delimiter for next category
			{
				idx++;
				quan[category]++;
				infile.clear();
				switch (category)
				{
				case ROOMS:
					infile >> num;
					if (num < 1 || num > MAX_LOCATIONS)										// Ensure valid subscript for location[]
					{
						cout << " ?Error: Invalid room number (" << num << ")" << endl;
						return false;
					}
					getline(infile, location[num].room_name);
					remove_comment(location[num].room_name);
					if (DEBUG && VERBOSE)
					{
						cout << "(" << idx << ") ";
						cout << num;
						cout << ": " << location[num].room_name << endl;
					}
					break;
				case OBJECTS:
					infile >> num;															// Must stand alone to use num for next infile read.
					if (num < 1 || num > MAX_OBJECTS)
					{
						cout << " ?Error: Invalid object number (" << num << ")" << endl;
						return false;
					}
					infile >> object[num].name >> object[num].location >> object[num].points >> object[num].weight;
					if (DEBUG & VERBOSE)
						cout << right << setw(3) << num << ": "
						<< left << setw(10) << object[num].name << endl;
					if (num != idx && DEBUG)
						cout << " ?Warning: Object numbering discrepancy at #" << num << " " << object[num].name << endl;
					skip_white_space(infile);
					state_idx = 1;
					do
					{
						bool is_state = (infile.peek() == '%');									// '%' signals that this object has states
						if (infile.peek() == '%')
						{
							infile.get(dummy_ch);												// 'Eat' the % flag
							getline(infile, object[num].state[state_idx], ':');					// Read the state
						}
						skip_white_space(infile);
						getline(infile, object[num].short_desc[state_idx], ';');				// Read the short description of the object in the specified state
						skip_white_space(infile);
						if (is_state)
						{
							getline(infile, object[num].description[state_idx], '(');
							while (object[num].description[state_idx].back() == SPACE || object[num].description[state_idx].back() == TAB)
								object[num].description[state_idx].pop_back();
							infile >> object[num].set_state_command[state_idx][0] >> ws;
							if (infile.peek() != ')')
								getline(infile, object[num].set_state_command[state_idx][1], ')');
							else
								object[num].set_state_command[state_idx][1] = ".";
							if (all_of(object[num].set_state_command[state_idx][1].begin(), object[num].set_state_command[state_idx][1].end(), isdigit))
							{
								int n = stoi(object[num].set_state_command[state_idx][1]);
								if (n >= 1 && n <= quan[OBJECTS])
								{
									object[num].set_state_command[state_idx][1] = object[n].name;
									object[num].absorbed_object[state_idx] = n;
								}
							}

							infile >> ws;
							if (infile.peek() == '~')											// This signals a set pre-condition
							{
								infile.get(dummy_ch);
								infile >> object[num].set_condition[state_idx];
							}

						}
						else 
							getline(infile, object[num].description[state_idx]);
						state_idx++;
						skip_white_space(infile);
					} while (infile.peek() == '%');

					max_ttl_points += object[num].points;
					break;
				case OBSTACLES:
					infile >> num;
					if (num < 1 || num > MAX_OBSTACLES)
					{
						cout << " ?Error: Invalid obstacle number (" << num << ")" << endl;
						return false;
					}
					infile >> obstacle[num].name >> obstacle[num].location;					// Must stand alone to use num for next infile read.
					if (num != idx && DEBUG) 
						cout << " ?Warning: Obstacle numbering discrepancy at #" << num << " " << obstacle[num].name << endl;
					skip_white_space(infile);
					getline(infile, obstacle[num].description);
					remove_comment(obstacle[num].description);
					break;
				case INPUT_SYNONYMS:
					infile >> input_synonym[idx].req_loc >> input_synonym[idx].req_obj >> input_synonym[idx].req_state; 
					if (DEBUG && VERBOSE)
					{
						cout << "(syn " << idx << " req loc is " << input_synonym[idx].req_loc << location[input_synonym[idx].req_loc].room_name << ")\n";
						cout << "(syn " << idx << " req obj is " << input_synonym[idx].req_obj;
						if (input_synonym[idx].req_obj != 0) 
							cout << ": " << object[abs(input_synonym[idx].req_obj)].name;
						cout << ")\n";
						cout << "(syn " << idx << " req state is " << input_synonym[idx].req_state;
						if (input_synonym[idx].req_state != 0) 
							cout << ": " << object[abs(input_synonym[idx].req_obj)].state[abs(input_synonym[idx].req_state)];
						cout << ") \n";
					}
					if (input_synonym[idx].req_obj < -MAX_OBJECTS || num > MAX_OBJECTS)
					{
						cout << "Error: Synonym " << idx << " specifies invalid object number (" << num << ")" << endl;
						return false;
					}
					count = 0;	// 0 is index for the base phrase for each set of input_synonyms
					do
					{
						skip_white_space(infile);
						if (count >= MAX_ENTRIES_PER_INPUT_SYNONYM)
						{
							cout << "  ?Error: Too many entries for input synonym #" << (idx) << " " << input_synonym[idx].first[0] << " " << input_synonym[idx].second[0] << endl;
							infile.ignore(1000, '\n');
							break;
						}
						infile >> ws >> input_synonym[idx].first[count] >> ws >> input_synonym[idx].second[count];	// Read two-word input_synonym phrase
						remove_comment(input_synonym[idx].second[count]);
						input_synonym[idx].second[count] = trim(input_synonym[idx].second[count], ',');				// Remove trailing comma
						if (input_synonym[idx].second[count].back() == ',')
							cout << "ouch! \n";
						if (DEBUG && VERBOSE)
							cout << "Input_Synonym " << idx << " " << count << " is '"
							<< input_synonym[idx].first[count] << " " << input_synonym[idx].second[count] << "'" << endl;
						count++;
						while (infile.peek() == TAB || infile.peek() == SPACE)
							infile.get(dummy_ch);
					} while (infile.peek() != EOL && infile.peek() != COMMENT_DELIMITER && infile && dummy_ch != COMMENT_DELIMITER);
					infile.ignore(1000, '\n');
					break;
				case VERBS:
					skip_white_space(infile);
					infile >> verb[idx].first >> verb[idx].second;
					remove_comment(verb[idx].second);
					skip_white_space(infile);
					infile >> verb[idx].req_loc;
					if (verb[idx].req_loc == NO_REQUIREMENT)
					{
						verb[idx].feedback[WRONG_LOCATION] = "N/A";
						infile.ignore(1000, '\n');
					}
					else
					{
						skip_white_space(infile);
						getline(infile, verb[idx].feedback[WRONG_LOCATION]);
						remove_comment(verb[idx].feedback[WRONG_LOCATION]);
					}
					infile >> verb[idx].req_obj;
					if (verb[idx].req_obj < -MAX_OBJECTS || verb[idx].req_obj > MAX_OBJECTS)
					{
						cout << " ?Error: Verb '" << verb[idx].first << " " << verb[idx].second << " has invalid required object number (" << verb[idx].req_obj << ")" << endl;
						return false;
					}
					if (verb[idx].req_obj == NO_REQUIREMENT)
					{
						verb[idx].feedback[MISSING_OBJECT] = "N/A";
						infile.ignore(1000, '\n');
					} 
					else
					{
						infile >> verb[idx].new_obj_loc;
						getline(infile, verb[idx].feedback[MISSING_OBJECT]);
						remove_comment(verb[idx].feedback[MISSING_OBJECT]);
					}
					infile >> verb[idx].req_obs;
					if (verb[idx].req_obs < -MAX_OBSTACLES || verb[idx].req_obs > MAX_OBSTACLES)
					{
						cout << " ?Error: Verb '" << verb[idx].first << " " << verb[idx].second << " has invalid required obstacle number (" << verb[idx].req_obs << ")" << endl;
						return false;
					}
					if (verb[idx].req_obs == NO_REQUIREMENT)
					{
						verb[idx].feedback[MISSING_OBSTACLE] = "N/A";
						infile.ignore(1000, '\n');
					} 
					else
					{
						infile >> verb[idx].new_obs_loc;
						getline(infile, verb[idx].feedback[MISSING_OBSTACLE]);
						remove_comment(verb[idx].feedback[MISSING_OBSTACLE]);
					}
					infile >> verb[idx].bonus_obj >> verb[idx].bonus_obj_loc;
					if (verb[idx].bonus_obj < -MAX_OBJECTS || verb[idx].bonus_obj > MAX_OBJECTS)
					{
						cout << " ?Error: Verb '" << verb[idx].first << " " << verb[idx].second << " has invalid bonus object number (" << verb[idx].bonus_obj << ")" << endl;
						return false;
					}
					getline(infile, verb[idx].feedback[SUCCESS]);
					remove_comment(verb[idx].feedback[SUCCESS]);
					infile >> verb[idx].old_loc[0] >> verb[idx].new_loc[0]
						>> verb[idx].old_loc[1] >> verb[idx].new_loc[1];
					infile.ignore(1000, '\n');
					if (DEBUG & VERBOSE)
						cout << "(" << idx << ") " << verb[idx].first << " " << verb[idx].second << endl;
					break;
				case RESPONSES:
					infile >> response[idx].req_loc >> response[idx].req_obj >> response[idx].req_state >> response[idx].first >> response[idx].second;
					if (response[idx].req_obj < -MAX_OBJECTS || response[idx].req_obj > MAX_OBJECTS)
					{
						cout << " ?Error: Response '" << response[idx].first << " " << response[idx].second << " has invalid required object number (" << response[idx].req_obj << ")" << endl;
						return false;
					}
					skip_white_space(infile);
					getline(infile, response[idx].feedback);
					remove_comment(response[idx].feedback);
					break;
				case HINTS:
					quan[RESPONSES]++;
					infile >> response[quan[RESPONSES]].req_loc >> response[quan[RESPONSES]].req_obj >> response[quan[RESPONSES]].first >> response[quan[RESPONSES]].second;
					if (response[idx].req_obj < -MAX_OBJECTS || response[idx].req_obj > MAX_OBJECTS)
					{
						cout << " ?Error: Hint '" << response[quan[RESPONSES]].first << " " << response[quan[RESPONSES]].second << " has invalid required object number (" << response[quan[RESPONSES]].req_obj << ")" << endl;
						return false;
					}
					skip_white_space(infile);
					getline(infile, response[quan[RESPONSES]].feedback);
					remove_comment(response[quan[RESPONSES]].feedback);
					break;
				case LOCATIONS:
					skip_white_space(infile);							// skips comment lines
					infile >> num;										//num should equal idx
					if (num != idx)
						if (num <= quan[LOCATIONS])
							cout << " ?Warning: Location numbering discrepancy at #" << num << "(" << idx << ")" << endl;
						else return false;
					for (dir = NORTH; dir <= WEST; dir = static_cast<directions>(dir + 1))
					{
						infile >> location[num].link[dir];
						if (location[num].link[dir] < 0 && location[num].link[dir] != -999 || location[num].link[dir] > MAX_LOCATIONS)										// Ensure valid subscript for location[] or -1 oblivion or -999 game over
						{
							cout << " ?Error: Location #" << num << " has invalid link to " << location[num].link[dir] << endl;
							return false;
						}
					}
					while (infile.peek() == SPACE || infile.peek() == TAB )
						infile.get(dummy_ch);
					getline(infile, location[num].description);
					remove_comment(location[num].description);
					if (DEBUG && VERBOSE)
						cout << "(" << idx << ")  " << num << ": '" << location[num].description << '\'' << endl;
					break;
				}
				skip_white_space(infile);
			}
			if (DEBUG)
				cout << quan[category] << " " << categoryText[category] << " read." << endl;
					
		}
	}
	infile.close();
	if (quan[LOCATIONS] != quan[MAP_SIZE]) 
		cout << " ?Warning: Mismatch of " << quan[LOCATIONS] << " location descriptions and declared map size of " << quan[MAP_SIZE] << ". \n";
	if (infile || quan[LOCATIONS] == quan[MAP_SIZE])
		return true;
	else
		return false;
}




	string ucase(string strToConvert)
	{
		for (string::iterator p = strToConvert.begin(); strToConvert.end() != p; ++p)
			*p = toupper(*p);

		return strToConvert;
	}

	bool match(string rule, string attempt)
	{
		return (ucase(rule) == ucase(attempt) || rule == "*" || rule == "." && attempt.empty() || rule.empty() && attempt == ".");
	}

	bool match_location(int req_loc)										// Check for a match with current location
	{
		if (req_loc == 0)													// 0 is wildcard location, matches any current location
			return true;
		if (req_loc > 0 && req_loc == current_location)						// Location must match
			return true;
		if (req_loc < 0 && -req_loc != current_location)					// Negative prohibits that location
			return true;
		return false;
	}

	bool match_location(objects obj)
	{
		if (match_location(obj.location))
			return true;													// matches current location or player's possession
		if (obj.location < 0)
			if (match_location(object[-obj.location].location))
				return true;												// It's inside another object that matches here

		return false;
	}
	
	bool match_object(int req_obj)											// Check for a match with player's possession and/or current location
	{
		if (req_obj == 0)
			return true;													// 0 is wildcard location, matches any situation
		if (req_obj > 0 && (object[req_obj].location == PLAYERS_POSSESSION || object[req_obj].location == current_location))
			return true;
		if (req_obj < 0 && (object[-req_obj].location != PLAYERS_POSSESSION && object[req_obj].location != current_location))
			return true;
		return false;
	}

	bool match_state(int req_obj, int req_state)
	{
		if (req_obj == 0 || req_state == 0)
			return true;
		if (req_state > 0 && object[abs(req_obj)].current_state == req_state
			|| req_state < 0 && object[abs(req_obj)].current_state != -req_state)
			return true;
		return false;
	}

	directions find_direction(string str)
	{
		directions dir;
		char ch;

		for (dir = NORTH; dir <= WEST; dir = static_cast<directions>(dir + 1))
			if (match(directionText[dir], str) || (str.length() == 1 && (toupper(int(directionText[dir][0])) == toupper(int(str[0])))))
				return dir;

		return NULL_DIRECTION;															// arbitrary result (should use is_direction)					
	}

	bool find_set_state_command(string str1, string str2, int& obj_idx, int& state_idx)
	{
		for (int obj_itr = 1; obj_itr <= quan[OBJECTS]; obj_itr++)
			for (int cmd_itr = 1; cmd_itr <= MAX_STATES_FOR_OBJECTS; cmd_itr++)
				if (object[obj_itr].set_state_command[cmd_itr][0].empty())
					break;
				else if (match(object[obj_itr].set_state_command[cmd_itr][0], str1) && match(object[obj_itr].set_state_command[cmd_itr][1], str2))
				{
					obj_idx = obj_itr;
					state_idx = cmd_itr;
					return true;
				}
		return 0;
	}

	int find_verb(string str1, string str2)
	{
		for (int verb_itr = 1; verb_itr <= quan[VERBS]; verb_itr++)
			if ( (verb[verb_itr].first == "*" || match(verb[verb_itr].first, str1))
				&& (verb[verb_itr].second == "*" || match(verb[verb_itr].second, str2)))
				return verb_itr;												// Found verb at verb_itr.
		return 0;																// Not found.
	}

	int find_response(string str1, string str2)
	{
		for (int resp_itr = 1; resp_itr <= quan[RESPONSES]; resp_itr++)
			if (match(response[resp_itr].first, str1)
				&& match(response[resp_itr].second, str2))
				return resp_itr;												// Found response at resp_itr.
		return 0;																// Not found.
	}

	bool is_direction(string str)
	{
		return (find_direction(str) != NULL_DIRECTION);														
	}

	bool is_adjacent(int where)
	{
		for (directions dir_itr = NORTH; dir_itr <= WEST; dir_itr = static_cast<directions>(dir_itr + 1))
			if (location[current_location].link[dir_itr] == where)
				return true;
		return false;
	}

	int obs(int where)
	{
		for (int obs_idx = 1; obs_idx <= quan[OBSTACLES]; obs_idx++)
			if (obstacle[obs_idx].location == where)
				return obs_idx;
		return 0;
	}

	int find_room(string str)
	{
		if (DEBUG && VERBOSE)
			cout << "Searching for a room named " << str << endl;
		int room_itr;
		for (room_itr = 1; room_itr <= quan[MAP_SIZE]; room_itr++)
			if (match(trim(location[room_itr].room_name), trim(str)))
				return room_itr;								// Found room at location room_itr.
		return 0;												// Not found.
	}

	void get_word(ifstream& infile, string& word)
	{
		size_t char_idx = 0;
		char ch, dummy_ch;
		//if (infile.peek() == SPACE)
			//infile.get(dummy_ch);
		word = "";
		while (infile && infile.peek() != EOL)
		{
			infile.get(ch);
			if ((ch == ' ' || ch == ',') && word.length() >= 0)
				break;
			word[char_idx++] = ch;
		}
	}

	void describe(int where)									// Describe location fully
	{
		size_t idx;
		directions dir_idx;
		char ch;
		if (DEBUG || TRACE_LOCATION)
			cout << "Location " << where << ".  \n";

		if (where >= 0 && where <= MAX_LOCATIONS)
		{
			if (location[where].room_name != "")
				cout << ucase(location[where].room_name)			// Give room name of this location
				<< endl << endl;
			typeOut(location[where].description);					// Describe location
			for (idx = 1; idx <= quan[OBJECTS]; idx++)
				if (object[idx].location == where)
					typeOut(object[idx].description[object[idx].current_state]);				// Describe objects present
			for (idx = 1; idx <= quan[OBSTACLES]; idx++)
				for (dir_idx = NORTH; dir_idx <= WEST; dir_idx = static_cast<directions>(dir_idx + 1))
					if (obstacle[idx].location == location[where].link[dir_idx])
						typeOut("The way is blocked to the " + directionText[dir_idx] + ". " + obstacle[idx].description);			// Describe obstacles adjacent
			last_location = where;
			cout << endl;
		}
		else if (where = -999)
		{
			typeOutln("\n\nThe game has ended.\n\n");
			typeOutln("Type 'QUIT' to exit the program.");
		}
		else
		{
			cout << "There is no describing where you are. \n";
		}
	}

	void checkscore()
	{
		int current_score = 0;

		for (int i = 1; i <= quan[OBJECTS]; i++)
			if (object[i].location == 0)
				current_score += object[i].points;
		if (current_score == max_ttl_points)
		{
			cout << endl << endl;
			cout << "Congratulations! \n\n";
			cout << "You have earned the maxium possible points! "
				<< "(" << max_ttl_points << ")"
				<< "\n";
			cout << "Type QUIT to end the game, champ! \n";
		}
	}

	void test()
	{
		int rm_idx = 0;
		
		cout << "Testing...\n";
		for (categories cat_idx = MAP_SIZE; cat_idx < Q_CATEGORIES; cat_idx = static_cast<categories>(cat_idx + 1))
		{
			cout << "\nTesting " << categoryText[cat_idx] << ": \n";
			for (int idx = 1; idx <= quan[cat_idx]; idx++)
			{
				switch (cat_idx)
				{
				case MAP_SIZE:
					if (idx == 1)
						cout << quan[MAP_SIZE] << endl;
					break;
				case ROOMS:
					while (location[rm_idx].room_name == "" && rm_idx < MAX_ROOMS)
						rm_idx++;
					cout << right << setw(3) << rm_idx << ": " << location[rm_idx++].room_name << endl;
					break;
				case OBJECTS:
					cout << right << setw(3) << idx << ": ";
					cout << left << setw(10) << object[idx].name << "  "
						<< "Loc " << right << setw(3) << object[idx].location << "  ";
					cout << left << setw(16) << location[object[idx].location].room_name + " "
						<< right << setw(3) << object[idx].points << " pts    ";
					for (int state_idx = 1; state_idx <= MAX_STATES_FOR_OBJECTS; state_idx++)
					{
						if (object[idx].state[state_idx].empty() && state_idx != 1)
							break;
						if (state_idx > 1)
							cout << string(53, SPACE);
						cout << left << setw(8) << object[idx].state[state_idx] << " "
							<< setw(19) << object[idx].short_desc[state_idx] << "   "
							<< object[idx].description[state_idx];
						if (!object[idx].set_state_command[state_idx][0].empty())
							cout << "[" << object[idx].set_state_command[state_idx][0] << " " << object[idx].set_state_command[state_idx][1] << "]";
						cout << endl;
					}
					
					if (idx == quan[OBJECTS])
						cout << "Maximum Total Points: " << max_ttl_points << endl;
					break;
				case OBSTACLES:
					cout << idx << ": " << obstacle[idx].name << " -- " << obstacle[idx].description << " Location " << obstacle[idx].location << "." << endl;
					break;
				case INPUT_SYNONYMS:
					cout << right << setw(3) << idx << ": " << left;
					for (int j = 0; j < MAX_ENTRIES_PER_INPUT_SYNONYM; j++)
						if (!input_synonym[idx].first[j].empty())
						cout << setw(8) << input_synonym[idx].first[j] << " " << setw(8) << input_synonym[idx].second[j] << "     ";
					cout << endl;
					break;
				case VERBS:
					cout << idx << ": " << verb[idx].first << " " << verb[idx].second << endl;
					cout << "    -Not at loc " << verb[idx].req_loc << "? " << verb[idx].feedback[WRONG_LOCATION] << endl;
					cout << "    -Have no " << object[abs(verb[idx].req_obj)].name << "? " << verb[idx].feedback[MISSING_OBJECT] << endl;
					cout << "    -No " << obstacle[abs(verb[idx].req_obs)].name << "? " << verb[idx].feedback[MISSING_OBSTACLE] << endl;
					cout << "    -Success: " << verb[idx].feedback[SUCCESS] << endl;
					cout << "       Moves Player from location " << verb[idx].old_loc[0] << " to " << verb[idx].new_loc[0]
						<< " or from " << verb[idx].old_loc[1] << " to " << verb[idx].new_loc[1] << endl;
					cout << "       Moves object " << object[abs(verb[idx].req_obj)].name << " to location " << verb[idx].new_obj_loc << (verb[idx].new_obj_loc < 0 ? " (oblivion)" : "") << endl;
					cout << "       Moves obstacle " << obstacle[abs(verb[idx].req_obs)].name << " to location " << verb[idx].new_obs_loc << (verb[idx].new_obs_loc < 0 ? " (oblivion)" : "") << endl;
					if (verb[idx].bonus_obj > 0)
						cout << "       Moves object " << verb[idx].bonus_obj << " " << object[abs(verb[idx].bonus_obj)].name << " to location " << verb[idx].bonus_obj_loc << endl;
					else cout << "       No bonus object." << endl;
					break;
				case RESPONSES:
					cout << right << setw(3) << idx << ": " << "Location " << setw(3) << response[idx].req_loc << "  " << setw(12) << left << location[abs(response[idx].req_loc)].room_name
						<< "  Object " << right << setw(3) << response[idx].req_obj << " " << setw(10) << left << object[abs(response[idx].req_obj)].name + "  "
						<< "  State " << right << setw(3) << response[idx].req_state << " " << setw(10) << left << object[abs(response[idx].req_obj)].state[abs(response[idx].req_state)] + "   "
						<< setw(8) << left << response[idx].first << " " << setw(8) << response[idx].second << " -- "
						<< response[idx].feedback << endl;
					break;
				case HINTS:
					break;
				case LOCATIONS:
					break;			// Too slow & time-consuming
					cout << "Location " << idx << ": " << endl;
					describe(idx);
					cout << "Links NSEW to " 
						<< location[idx].link[NORTH] << " " << location[idx].link[SOUTH] << " " 
						<< location[idx].link[EAST] << " " << location[idx].link[WEST] << endl;
					cout << endl;
					break;
				}
			}

		}
		

	}

	void skip_white_space(ifstream& infile)
	{
		char dummy_ch;
		while (infile.peek() == SPACE || infile.peek() == TAB || infile.peek() == EOL || infile.peek() == COMMENT_DELIMITER)
			if (infile.peek() == COMMENT_DELIMITER)
				infile.ignore(1000, '\n');
			else
				infile.get(dummy_ch);
	}


	string left$(string s, int len)
	{
		// Len can be positive or negative
		// Positive numbers return a string of the given length.
		// Negative numbers return a string shortened by the given length.
		if (len >= 0)
			return s.substr(0, len);
		else
			return s.substr(0, s.length() + len);					// for negative values of len, chop off that many rightmost chars

	}

	string left$(string s, string delimiter, left$OptionType option) // default option = EXCLUSIVE
	{
		// Returns the left portion of the string s, up to but not including the delimiter.
		// E.g., if the delimiter is a space, then the first word is returned.
		// But, if option INCLUSIVE is passed, then the delimiter is included.

		unsigned int pos = s.find(delimiter);
		unsigned int len = 0;
		if (pos == STRING_NOT_FOUND)
			len = s.length();
		else
			len = (option == INCLUSIVE) ? pos + 1 : pos;

		return s.substr(0, len);
	}

	string right$(string s, int len)
	{
		return s.substr(s.length() - len);
	}

	string capitalize(string s)
	{
		if (islower(s[0]))												// if first letter is lowercase
			s[0] = toupper(s[0]);										// convert to uppercase
		return s;
	}

	string trim(string s, char c)
	{
		s = rtrim(s, c);

		for (int i = 0; i < s.length(); i++)					// erase leading blank spaces
			if (s[i] == ' ' || s[i] == TAB || s[i] == c)
				s.erase(i--, 1);
			else
				break;
		return s;
	}

	string rtrim(string s, char c)
	{
		for (int i = s.length() - 1; i >= 0; i--)						// erase trailing blank spaces
			if (s[i] == ' ' || s[i] == TAB || s[i] == c)
				s.erase(i, 1);
			else
				break;
		return s;
	}

	string lexiSpeechNoNesting(string S)						// E.g., I {like|love|hate} you!
	{
		const size_t NOT_FOUND = string::npos;
		const size_t MAX = 1000;
		size_t idx = 0, len = NULL;
		string result = "", choices[MAX] = { "" }, intermediate[MAX] = { "" };
		size_t choices_count = NULL, intermediate_count = NULL;
		static string previous_S = "";
		static int r[MAX] = { -1 };
		int previous_r;
		static bool first_time = true;

		if (first_time || S != previous_S)
		{
			for (int i = 0; i < MAX; i++)
				r[i] = -1;
		}

		previous_S = S;

		while (S.length() > 0)
		{
			len = S.find("{");
			intermediate[idx] = S.substr(0, len);
			//cout << idx << ": " << intermediate[idx] << endl;
			S.erase(0, len);
			S.erase(0, 1);
			idx++;
			if (S.length() > 0)
			{
				len = S.find("}");
				intermediate[idx] = S.substr(0, len);
				//cout << idx << ": " << intermediate[idx] << endl;

				S.erase(0, len);
				S.erase(0, 1);

				split(intermediate[idx], "|", MAX, choices, choices_count);
				//cout << choices_count << " choices! \n";
				if (choices_count > 0)
				{
					previous_r = r[idx];
					if (choices_count > 1)
						do
						{
							r[idx] = rand() % choices_count;
						}  while (r[idx] == previous_r && choices_count > 2);
					else
						r[idx] = 0;
					intermediate[idx] = choices[r[idx]];
					//	cout << idx << ": " << intermediate[idx] << endl;
					idx++;
				}
			}
		}
		intermediate_count = idx;

		for (idx = 0; idx < intermediate_count; idx++)
			result += intermediate[idx];
		first_time = false;
		return result;
	}
	int lexiSpeechDepth(string S)							// Return count of deepest nesting {{you} win} = 2
	{
		int depth = 0;
		int max_depth = 0;
		int result = 0;

		for (int i = 0; i < S.length(); i++)
			if (S[i] == '{')
			{
				depth++;
				if (depth > max_depth)
					max_depth = depth;
			}
			else if (S[i] == '}')
				depth--;

		if (depth == 0)
			result = max_depth;
		else
			result = 0;										// This reflects a bad string param with unmatched {}'s

		return result;
	}

	string lexiSpeechDeepest(string S)						// E.g., I {like|love|hate} you!
	{
		//const size_t NOT_FOUND = string::npos;
		const size_t MAX = 1000;
		size_t len = NULL;
		string result = "";
		size_t choices_count = NULL, intermediate_count = NULL;
		static string previous_S = "";
		static int r[MAX] = { -1 };
		int previous_r;
		static bool first_time = true;
		int nesting_depth = 0, max_nesting_depth = 0;
		size_t opening_bracket_pos = 0, closing_bracket_pos = 0;
		size_t i = 0;
		string part1, part2, part3;

		if (first_time || S != previous_S)
		{
			for (int i = 0; i < MAX; i++)
				r[i] = -1;
		}

		previous_S = S;

		max_nesting_depth = lexiSpeechDepth(S);

		nesting_depth = 0;
		i = 0;
		
		while (nesting_depth < max_nesting_depth && i < S.length())
		{
			if (S[i] == '{')
				nesting_depth++;
			else if (S[i] == '}')
				nesting_depth--;
			i++;
		}
		i--;

		opening_bracket_pos = i;
		closing_bracket_pos = S.find("}", opening_bracket_pos);
		len = closing_bracket_pos - opening_bracket_pos + 1;

		part1 = S.substr(0, opening_bracket_pos);
		part2 = S.substr(opening_bracket_pos, len);
		if (closing_bracket_pos < S.length() - 1)
			part3 = S.substr(closing_bracket_pos + 1);
		else
			part3 = "";

		result = part1 + lexiSpeechNoNesting(part2) + part3;

		first_time = false;

		return result;
	}

	string lexiSpeech(string S)						// E.g., I {like|love|hate} you!
	{
		int depth = lexiSpeechDepth(S);

		if (depth < 2)
			return lexiSpeechNoNesting(S);

		while (lexiSpeechDepth(S) > 0)
			S = lexiSpeechDeepest(S);

		return S;
	}

	string CPerson(string pText, int pFromPerson, int pToPerson)
	{
		const size_t firstperson = 1, secondperson = 2, thirdpersonMas = 3, thirdpersonFem = 4, thirdpersonNeu = 5;
		string pronouns[6][10] = 
		{
			"pr0", "pr1", "pr2", "pr3", "pr4", "pr5", "pr6", "pr7", "pr8", "pr9",							//0
			"I am", "I was", "I", "me", "my", "mine", "we", "us", "our", "ours",							//firstperson
			"you are", "you were", "you", "you", "your", "yours", "you", "you", "your", "yours",			//secondperson
			"he is", "he was", "he", "him", "his", "his", "they", "them", "their", "theirs",				//thirdpersonMas
			"she is", "she was", "she", "her", "her", "hers", "they", "them", "their", "theirs",			//thirdpersonFem
			"it is", "it was", "it", "it", "its", "its", "they", "them", "their", "theirs"					//thirdpersonNeu
		};
			//	pronouns are regular, possessive, singular and plural

		const string PREP[] =
		{
			"aboard", "about", "above", "across", "after", "against", "along", "amid", "among", "anti",
			"around", "as", "at", "before", "behind", "below", "beneath", "beside", "besides", "between",
			"beyond", "but", "by", "concerning", "considering", "despite", "down", "during", "except",
			"excepting", "excluding", "following", "for", "from", "in", "inside", "into", "like", "minus",
			"near", "of", "off", "on", "onto", "opposite", "outside", "over", "past", "per", "plus",
			"regarding", "round", "save", "since", "than", "through", "to", "toward", "towards", "under",
			"underneath", "unlike", "until", "up", "upon", "versus", "via", "with", "within", "without"
		};

		string Text = pText;

		for (int i = 0; i < pronouns[0]->size(); i++)
			Text = WordReplace(Text, pronouns[pFromPerson][i], pronouns[pToPerson][i]);

		return Text;
	}

	string WordReplace(string pText, string pSearchString, string pReplacementString)
	{
		//dependency: boost.h for replace_all
		const string punct[] = { ",", ".", "!", "?", "(", ")", "/", ";", ":", "@", "#", "$", "%", "^", "&", "*", "-" };

		string Text = " " + pText + " ";	// pad for whole-word checking
		for (int p = 0; p < punct->size(); p++)
			Text = ""; // replace_all;
		return Text;
	}

	string reflect(string S)
	{
		// ID pattern: preposition you
		// sub for     preposition OBJyou
		// change      OBJyou -> me, you -> I, etc.
		string S0 = S;
		

		return CPerson(CPerson(CPerson(S, 1, 0), 2, 1), 0, 2);			// reflect
	}


	void split(string Expression, string Delimiter, size_t Limit, string Str[], size_t& count)
	{
		const size_t NOT_FOUND = string::npos;
		size_t idx = 0;
		size_t pos = NULL;

		if (Expression.find(Delimiter) == NOT_FOUND)
		{
			Str[0] = Expression;
			idx = 1;
			count = 1;
		}
		else
		{
			count = 1;
			do
			{
				pos = Expression.find(Delimiter);
				if (pos != NOT_FOUND)
					count++;
				Str[idx] = Expression.substr(0, pos);
				Expression.erase(0, pos);
				Expression.erase(0, 1);
				idx++;
			} while (Expression.length() > 0 && idx < Limit);
															// Second choice is null string
		}

		for (idx; idx < Limit; idx++)
			Str[idx] = "";

	}

	void remove_comment(string& str)
	{
		str = trim(left$(str, COMMENT_DELIMITER_STRING, EXCLUSIVE));			// Remove all chars past @ comment delimiter
	}


	void typeOut(string s)
	{
		const bool DELAY = true;
		const int TYPE_DELAY_BETWEEN_CHARS = 5;								// Milliseconds delay used in typeOut function
		const int TYPE_DELAY_BETWEEN_MESSAGES = 1;

		s = lexiSpeech(s);

		for (unsigned int j = 0; j < s.length(); j++)
		{
			if (DELAY) Sleep(TYPE_DELAY_BETWEEN_CHARS);
			if (s[j] == '\\')												// A single backslash means line break;
				cout << endl;
			else
				cout << s[j];
		}
		cout << " ";
		if (DELAY) Sleep(TYPE_DELAY_BETWEEN_MESSAGES);
	}

	void typeOutln(string s)
	{
		typeOut(s);
		cout << endl;
	}

	
	


