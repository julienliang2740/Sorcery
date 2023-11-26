#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>
#include <string>
#include <vector>

#include "card.h"
#include "deck.h"

class Player {
    std::string name;
    int playerID;
    std::vector<Card *> hand;
    Deck playerDeck; // WORK IN PROGRESS
    int magic; 
    int health;
    static const int handMax = 5;

    public:
        Player(std::string newname, int playerID, std::vector<Card *> initialHand, Deck playerDeck, int initialMagic);
        std::string getName() const;
        void assignName(std::string newname);
        int getID() const;
        std::vector<Card> getHand() const; 
        int getMagic() const;
        int getHandMax() const;
        int getHealth() const;
        bool removeCard(int i);
};

#endif
