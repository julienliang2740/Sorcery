#ifndef __DECK__
#define __DECK__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "card.h"
#include "minion.h"
#include "spell.h"
#include "enchantment.h"

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
        Deck& operator=(Deck&& other) noexcept;
};

#endif
