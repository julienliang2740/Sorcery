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

    Player player1("", 1, vector<int>(), 0);
    Player player2("", 2, vector<int>(), 0);

    // assuming that very first line is Player 1's name and second line is Player 2's name
    string cmd, aux1, aux2, aux3;
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
        else if (cmd == "quit") {
            break;
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