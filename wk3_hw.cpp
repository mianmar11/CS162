#include <iostream>
#include <string>

using namespace std;

int main() {
    // Init Variable
    string username;        // player name

    // Welcome User
    cout << "Hello Stranger.." << endl;
    cout << "Your name...?: ";
    getline(cin, username);
    cout << "Hello, " << username << "." << endl;
    cout << "\nWelcome to .{Silver Grit}." << endl;

    // 

    return 0;
}