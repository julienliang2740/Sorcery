#ifndef __CARD__
#define __CARD__

#include <iostream>
#include <string>
#include <vector>

enum cardtype {Minion, Enchantment, Ritual, Spell};

class Card {
    int cost;
    std::string name;
    int ownershipID;
    cardtype cardType;
    std::string displayFile;

    public:
        Card(int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile);
        int getCost();
        std::string getName();
        int getID();
        cardtype getType();
        std::string getFile();
};

#endif
