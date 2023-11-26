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
    bool hasTarget = false;

    public:
        Card(int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile, bool hasTarget);
        int getCost() const;
        std::string getName() const;
        int getID() const;
        cardtype getType() const;
        std::string getFile() const;
};

#endif
