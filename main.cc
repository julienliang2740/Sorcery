#include <iostream>
#include <fstream>
#include <string>

#include "player.h"
#include "board.h"
#include "minioncomponent.h"

using namespace std;

struct GameConfig {
    string deck1 = "decks/default.deck";
    string deck2 = "decks/default.deck";
    string init_file = "inits/empty.txt";
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

    ifstream d1 {config.deck1};
    ifstream d2 {config.deck2};

    Player player1(string(""), 1, vector<Card*>(), new Deck{d1, 1}, 0);
    Player player2(string(""), 2, vector<Card*>(), new Deck{d2, 2}, 0);

    if (!config.testing) {
        player1.shuffle();
        player2.shuffle();
    }

    std::cout << "player 1 has this many cards: " << player1.playerDeck->getNumCards() << std::endl;
    std::cout << "player 2 has this many cards: " << player2.playerDeck->getNumCards() << std::endl;

    Board gameBoard(vector<MinionComponent*>(), vector<MinionComponent*>(), &player1, &player2, 1, vector<Minion*>(), vector<Minion*>());
    
    std::cout << "player 1 has this many cards after board is initialized: " << player1.playerDeck->getNumCards() << std::endl;
    std::cout << "player 2 has this many cards after board is initialized: " << player2.playerDeck->getNumCards() << std::endl;

    // assuming that very first line is Player 1's name and second line is Player 2's name
    string cmd;
    ifstream initfile(config.init_file);
    int lines_read = 0;
    bool readFromFile = true;
    
    while (true) {
        // Figuring out whose turn it is
        int activePlayerID = gameBoard.getActiveID();
        Player& activePlayer = (activePlayerID == player1.getID()) ? player1 : player2;

        // Determining where to read from
        if (config.init_file == "inits/empty.txt") {
            readFromFile = false;
        }
        // Determing where to read from (or rather where to not read from, and when to stop)
        if (readFromFile && !(initfile >> cmd)) { // can't read from initfile anymore => start reading from cin
            initfile.close();
            readFromFile = false;
        }
        else if (!readFromFile && !(cin >> cmd)) { // can't even read from cin anymore => it's time to stop
            break;
        }

        // Processing Names
        if (lines_read == 0) {
            player1.assignName(cmd);
            if (cmd != "") lines_read += 1;
        }
        else if (lines_read == 1) {
            player2.assignName(cmd);
            if (cmd != "") {
                lines_read += 1;
                cout << "It is now the turn of " << ((activePlayerID == player1.getID()) ? player1.getName() : player2.getName()) << endl;
                
                if (!config.testing) {
                    for (int i = 0; i < Player::getHandMax(); ++i) {
                        player1.drawCard();
                        player2.drawCard();
                    }
                }
            }
        }

        // Processing Commands
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
            activePlayerID = gameBoard.endTurn();
            int previousPlayerID = (activePlayerID % 2) + 1;
            cout << "Turn ended for player" << previousPlayerID << endl;
            cout << "It is now the turn of " << ((activePlayerID == player1.getID()) ? player1.getName() : player2.getName()) << endl;
            
            if (!config.testing) {
                if (activePlayerID == player1.getID()) {
                    player1.drawCard();
                } else {
                    player2.drawCard();
                }
            }
        }
        else if (cmd == "quit") {
            break;
        }
        else if (cmd == "draw") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            std::cout << "player 1 deck length: " << player1.playerDeck->getNumCards() << std::endl;
            std::cout << "player 2 deck length: " << player2.playerDeck->getNumCards() << std::endl;
            if (config.testing) {
                if (activePlayer.drawCard()) cout << activePlayer.getName() << " drew a card" << endl;
            }
            else {
                cout << "draw is only available on testing mode" << endl;
            }
        }
        else if (cmd == "discard") {
            int i = -1;
            if (readFromFile) initfile >> i; else cin >> i;
            
            if (config.testing) {
                cout << "discard " << i << "th card in hand" << endl; //  INCOMPLETE INCOMPLETE INCOMPLETE
            }
            else {
                cout << "discard is only available on testing mode" << endl;
            }
        }
        else if (cmd == "attack") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            int i = -1, j = -1;
            if (readFromFile) {
                initfile >> i;
                if (initfile.peek() != '\r' && initfile.peek() != '\n') {
                    initfile >> j;
                }
            }
            else {
                cin >> i;
                if (cin.peek() != '\n') cin >> j;
            }         
            if (j == -1) cout << i << "th minion attacks enemy player" << endl;
            else cout << i << "th minion attacks enemy player's " << j << "th minion" << endl;
        }
        else if (cmd == "play") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            int i = -1, p = -1, t = -1;
            if (readFromFile) {
                initfile >> i;
                if (initfile.peek() != '\r' && initfile.peek() != '\n') initfile >> p >> t;
            }
            else {
                cin >> i;
                if (cin.peek() != '\n') cin >> p >> t;
            }

            if (p == -1) cout << "Play " << i << "th card in active player's hand" << endl;
            else cout << "Play " << i << "th card in active player's hand on card " << t << " owned by player " << p << endl;
        }
        else if (cmd == "use") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            int i = -1, p = -1, t = -1;
            if (readFromFile) {
                initfile >> i;
                if (initfile.peek() != '\r' && initfile.peek() != '\n') initfile >> p >> t;
            }
            else {
                cin >> i;
                if (cin.peek() != '\n') cin >> p >> t;
            }

            if (p == -1) cout << "Use " << i << "th card in active player's hand" << endl;
            else cout << "Use " << i << "th card in active player's hand on card " << t << " owned by player " << p << endl;
        }
        else if (cmd == "inspect") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            int i = 0;
            if (readFromFile) initfile >> i; else cin >> i;
            cout << "Inspecting " << i << "th minion" << endl;
        }
        else if (cmd == "hand") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            for (auto card: activePlayer.getHand()) {
                cout << card->getName() << endl;
            }
        }
        else if (cmd == "board") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            cout << "*Displaying the board*" << endl;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (cmd == "players") {
            cout << "Player 1: " << player1.getName() << endl;
            cout << "Player 2: " << player2.getName() << endl;
        }
        else if (cmd == "天王盖地虎") {
            cout << "宝塔镇河妖" << endl; 
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        cmd.clear();
    }
}
