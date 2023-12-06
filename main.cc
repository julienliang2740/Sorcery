#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "player.h"
#include "board.h"
#include "deck.h"
#include "minioncomponent.h"
#include "ascii_graphics.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
// #include "window.h"
// (^included from graphicsdisplay.h)

using namespace std;

struct GameConfig {
    string deck1 = "decks/default.deck";
    string deck2 = "decks/default.deck";
    string init_file = "inits/empty.txt";
    bool testing = false;
    bool graphics = false;
};

const int cardWidth = 240;
const int cardHeight = 160;

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

    Board gameBoard(vector<MinionComponent*>(), vector<MinionComponent*>(), &player1, &player2, 1, vector<Minion*>(), vector<Minion*>());
    textDisplay td(&gameBoard);
    gameBoard.addObserver(&td);

    // for when config.graphics is true
    unique_ptr<graphicsDisplay> gd = (config.graphics) ? std::make_unique<graphicsDisplay>(&gameBoard, new Xwindow()) : nullptr;

    player1.playerDeck->setBoardForRituals(&gameBoard);
    player2.playerDeck->setBoardForRituals(&gameBoard);
    
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
            if (cmd != "") {
                lines_read += 1;
                td.notify(1, 7);
            }
        }
        else if (lines_read == 1) {
            player2.assignName(cmd);
            if (cmd != "") {
                lines_read += 1;
                td.notify(2, 7);
                cout << "It is now the turn of " << ((activePlayerID == player1.getID()) ? player1.getName() : player2.getName()) << endl;
                player1.addMagic(1);
                td.notify(1, 7);
                
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
                cout << "discard " << i << ((i == 1) ? "st " : ((i == 2) ? "nd " : ((i == 3) ? "rd " : "th "))) << "card in hand" << endl;
                activePlayer.freeCard(i);
                if (!activePlayer.removeCard(i)) cout << "could not discard card";
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
            if (j == -1) {
                cout << i << ((i == 1) ? "st " : ((i == 2) ? "nd " : ((i == 3) ? "rd " : "th "))) << "minion attacks enemy player" << endl;
                gameBoard.attackPlayer(i);
            } else {
                cout << i << ((i == 1) ? "st " : ((i == 2) ? "nd " : ((i == 3) ? "rd " : "th "))) << "minion attacks enemy player's " << j << ((j == 1) ? "st " : ((j == 2) ? "nd " : ((j == 3) ? "rd " : "th "))) << "minion" << endl;
                gameBoard.attackMinion(i, j);
            }

            // Seeing if any player died
            if (gameBoard.checkWinState() == 1) { // player 1 wins
                cout << "Player 1 (" << player1.getName() << ") wins" << endl;
                break;
            }
            else if (gameBoard.checkWinState() == -1) { // player 1 loses -> player 2 wins
                cout << "Player 2 (" << player2.getName() << ") wins" << endl;
                break;
            }
        }
        else if (cmd == "play") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            int i = -1, p = -1, t = -1;
            char tChar;
            if (readFromFile) {
                initfile >> i;
                if (initfile.peek() != '\r' && initfile.peek() != '\n') {
                    initfile >> p;
                    initfile >> tChar;
                    if (isdigit(tChar)) t = tChar - '0';
                    else if (tChar == 'r') {
                        t = 6;
                    }
                }
            }
            else {
                cin >> i;
                if (cin.peek() != '\n') {
                    cin >> p;
                    cin >> tChar;
                    if (isdigit(tChar)) t = tChar - '0';
                    else if (tChar == 'r') {
                        t = 6;
                    }
                }
            }

            bool placed = gameBoard.playCard(i, p, t);
            if (!placed) {
                std::cerr << "cannot place card" << std::endl;
            }
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

            if (p == -1) cout << "Use " << i << ((i == 1) ? "st " : ((i == 2) ? "nd " : ((i == 3) ? "rd " : "th "))) << "card in active player's hand" << endl;
            else cout << "Use " << i << ((i == 1) ? "st " : ((i == 2) ? "nd " : ((i == 3) ? "rd " : "th "))) << "card in active player's minions on minion " << t << " owned by player " << p << endl;
            gameBoard.useActivatedAbility(i, p, t);
        }
        else if (cmd == "inspect") { //  INCOMPLETE INCOMPLETE INCOMPLETE
            int i = 0;
            if (readFromFile) initfile >> i; else cin >> i;
            cout << "Inspecting " << i << ((i == 1) ? "st" : ((i == 2) ? "nd" : ((i == 3) ? "rd" : "th"))) << "minion" << endl;
            std::vector<MinionComponent*> ownMinions = (activePlayerID == player1.getID()) ? gameBoard.p1Minions : gameBoard.p2Minions;
            if (i < 1 || i > ownMinions.size()) {
                cout << "invalid minion ID" << endl;
                continue;
            }

            inspectMinion(ownMinions[i - 1]);
            if (gd.get() != nullptr) gd->graphics_inspectMinion(5, 5, cardWidth, cardHeight, ownMinions[i - 1]);
        }
        else if (cmd == "hand") { //  INCOMPLETE INCOMPLETE INCOMPLETE

            if (activePlayer.getHand().empty()) {
                cout << "hand is empty" << endl;
                continue;
            }

            printHand(activePlayer);

            if (gd.get() != nullptr) gd->graphics_printHand(5, 5, cardWidth, cardHeight, activePlayer);
            
        }
        else if (cmd == "board") { //  INCOMPLETE INCOMPLETE INCOMPLETE

            td.printBoard();
            if (gd.get() != nullptr) gd->graphics_printBoard(5, 5, cardWidth, cardHeight);
        }
        else if (cmd == "players") {
            cout << "Player 1: " << player1.getName() << endl;
            cout << "Player 2: " << player2.getName() << endl;
        }
        
        if (cmd != "hand" && cmd !="inspect"){
            if (gd.get() != nullptr) gd->graphics_printBoard(5, 5, cardWidth, cardHeight);
        }
        
        cmd.clear();

    }
}
