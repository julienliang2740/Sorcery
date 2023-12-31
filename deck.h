#ifndef __DECK__
#define __DECK__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "minion.h"
#include "spell.h"
#include "enchantment.h"
#include "enchantments.h"
#include "ritual.h"
#include "rituals.h"

class Deck {
    std::vector<Card *> theDeck;
    int cardsNumber;
    int ownershipID;

    Minion* makeMinionFromName(std::string name, int playerID);
    bool nameIsMinion(std::string name);

    Spell* makeSpellFromName(std::string name, int playerID);
    bool nameIsSpell(std::string name);

    Enchantment* makeEnchantmentFromName(std::string name, int playerID);
    bool nameIsEnchantment(std::string name);

    Ritual* makeRitualFromName(std::string name, int playerID);
    bool nameisRitual(std::string name);

    public:
        Deck(std::vector<Card *> theDeck, int cardsNumber);
        Deck(std::ifstream& deckFile, int ownerID);
        int getNumCards() const;

        bool isEmpty(); // ALWAYS CALL THIS FIRST BEFORE ATTEMPTING TO DRAW!!!
        Card* draw();
        void shuffle();
        bool addCardFront(Card *theCard); // returns true if succesfully added
        bool addCardBack(Card *theCard); // returns true if succesfully added
        ~Deck();
        void setBoardForRituals(Board* b);
        Deck& operator=(Deck&& other) noexcept;
};

#endif
