#include <iostream>
#include <string>
using namespace std;

struct GameConfig {
    string deck1 = "default.deck";
    string deck2 = "default.deck";
    string init_file = "defaultinit";
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
}