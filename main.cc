#include <iostream>
#include <fstream>
#include <string>

#include "player.h"

using namespace std;

struct GameConfig {
    string deck1 = "decks/default.deck";
    string deck2 = "decks/default.deck";
    string init_file = "inits/chuhan.txt";
    bool testing = false;
    bool graphics = false;
};

int main(int argc, char * argv[]) {
    GameConfig config;
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-deck1" && i + 1 < argc) config.deck1 = argv[++i];
        else if (arg == "-deck2" && i + 1 < argc) config.deck2 = argv[++i];
        else if (arg == "-init" && i + 1 < argc) config.init_file = argv[++i];
        else if (arg == "-testing") config.testing = true;
        else if (arg == "-graphics") config.graphics = true;
    }
    
    cout << "Deck 1: " << config.deck1 << endl;
    cout << "Deck 2: " << config.deck2 << endl;
    cout << "init file: " << config.init_file << endl;
    cout << "testing mode: " << config.testing << endl;
    cout << "fancy graphics: " << config.graphics << endl;

    Deck tempdeck1(vector<Card>(), 0);
    Deck tempdeck2(vector<Card>(), 0);

    Player player1("", 1, vector<Card>(), tempdeck1, 0);
    Player player2("", 2, vector<Card>(), tempdeck2, 0);

    // assuming that very first line is Player 1's name and second line is Player 2's name
    string cmd;
    ifstream initfile(config.init_file);
    int lines_read = 0;
    bool readFromFile = true;

    while (true) {
        // Determing where to read from (or rather where to not read from, and when to stop)
        if (readFromFile && !(initfile >> cmd)) { // can't read from initfile anymore => start reading from cin
            initfile.close();
            readFromFile = false;
        }
        else if (!readFromFile && !(cin >> cmd)) { // can't even read from cin anymore => it's time to stop
            break;
        }

        // Processing Commands
        if (lines_read == 0) {
            player1.assignName(cmd);
            lines_read += 1;
        }
        else if (lines_read == 1) {
            player2.assignName(cmd);
            lines_read += 1;
        }

        if (cmd == "help") {
            ifstream helpfile("help.txt");
            if (helpfile.is_open()) {
                string line;
                while (getline(helpfile, line)) {
                    cout << line << endl;
                }
                helpfile.close();
            }
        }
        else if (cmd == "end") {
            cout << "end turn" << endl; //  INCOMPLETE INCOMPLETE INCOMPLETE
        }
        else if (cmd == "quit") {
            break;
        }
        else if (cmd == "draw") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            if (config.testing) {
                cout << "draw card" << endl; 
            }
            else {
                cout << "draw is only available on testing mode" << endl;
            }
        }
        else if (cmd == "discard") {
            int i = -1;
            cin >> i;
            if (config.testing) {
                cout << "discard " << i << "th card in hand" << endl; //  INCOMPLETE INCOMPLETE INCOMPLETE
            }
            else {
                cout << "discard is only available on testing mode" << endl;
            }
        }
        else if (cmd == "attack") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            int i,j = -1;
            cin >> i;

            if (cin.peek() != '\n') cin >> j;

            if (j == -1) cout << i << "th minion attacks enemy player" << endl;
            else cout << i << "th minion attacks enemy player's " << j << "th minion";
        }
        else if (cmd == "play") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            int i,p,t = -1;
            cin >> i;

            if (cin.peek() != '\n') cin >> p >> t;

            if (p == -1) cout << "Play" << i << "th card in active player's hand" << endl;
            else cout << "Play" << i << "th card in active player's hand on card " << t << " owned by player " << p << endl;
        }
        else if (cmd == "use") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            int i,p,t = -1;
            cin >> i;

            if (cin.peek() != '\n') cin >> p >> t;

            if (p == -1) cout << "Use" << i << "th card in active player's hand" << endl;
            else cout << "Use" << i << "th card in active player's hand on card " << t << " owned by player " << p << endl;
        }
        else if (cmd == "inspect") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            int i = 0;
            cin >> i;
            cout << "Inspecting " << i << "th minion";
        }
        else if (cmd == "hand") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            cout << "*Displaying active player's hand*" << endl;
        }
        else if (cmd == "board") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            cout << "*Dispalying the board*" << endl;
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        else if (cmd == "players") {
            cout << "Player 1: " << player1.getName() << endl;
            cout << "Player 2: " << player2.getName() << endl;
        }
        else if (cmd == "天王盖地虎") {
            cout << "宝塔镇河妖" << endl; 
        }
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        cmd.clear();
    }
}
