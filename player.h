#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <string>
#include <vector>

#include "card.h"

class Player {
    std::string name;
    int playerID;
    std::vector<Card> hand; 
    int magic; 
    const int deckMax = 5;

    public:
        Player(std::string newname, int playerID, std::vector<Card> initialHand, int initialMagic);
        std::string getName();
        void assignName(std::string newname);
        int getID();
        std::vector<Card> getHand(); 
        int getMagic();
        int getDeckMax();
};

#endif
