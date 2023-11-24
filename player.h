#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <string>
#include <vector>

class Player {
    std::string name;
    int playerID;
    std::vector<int> hand; // PLACEHOLDER BEFORE CARDS ARE IMPLEMENTED
    int magic; 
    const int deckMax = 5;

    public:
        Player(std::string newname, int playerID, std::vector<int> initialHand, int initialMagic);
        std::string getName();
        void assignName(std::string newname);
        int getID();
        std::vector<int> getHand(); // PLACEHOLDER BEFORE CARDS ARE IMPLEMENTED
        int getMagic();
        int getDeckMax();
};

#endif