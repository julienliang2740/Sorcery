#ifndef __DECK__
#define __DECK__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "card.h"
#include "minion.h"

class Deck {
    std::vector<Card *> theDeck;
    int cardsNumber;
    int ownershipID;

    bool nameIsMinion(std::string name);
    Minion* makeMinionFromName(std::string name, int playerID);

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
