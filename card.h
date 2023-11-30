#ifndef __CARD__
#define __CARD__

#include <iostream>
#include <string>
#include <vector>

enum cardtype {M, E, R, S};

class Card {
    protected:
        int cost;
        std::string name;
        int ownershipID;
        cardtype cardType;
        bool hasTarget = false;
        std::string description;

    public:
        Card(int cost, std::string name, int ownershipID, cardtype cardType, bool hasTarget, std::string description);
        virtual ~Card();
        int getCost() const;
        std::string getName() const;
        int getID() const;
        cardtype getType() const;
        bool hasATarget() const;
        cardtype getCardType() const;
        std::string getCardDescription() const;
};

#endif
