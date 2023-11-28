#ifndef __SPELL__
#define __SPELL__

#include <iostream>
#include <string>
#include <vector>
#include "card.h"
#include "board.h"

class Spell : public Card {
    protected:
        Board* theBoard;
    public:
        Spell (int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile, bool hasTarget, Board* board);
        void useMagic();
        // each spell's ability is either: massAbility(), targetAbility()
        virtual ~Spell();
};

class Blizzard : public Spell {
    void massAbility();
};

class Banish : public Spell {
    void targetAbility(Card target);
};

#endif
