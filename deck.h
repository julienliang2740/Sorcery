#ifndef __DECK__
#define __DECK__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "card.h"

class Deck {
    std::vector<Card *> theDeck;
    int cardsNumber;

    public:
        Deck(std::vector<Card *> theDeck, int cardsNumber);
        Deck(ifstream& deckFile);
        int getNumCards();

        bool isEmpty(); // ALWAYS CALL THIS FIRST BEFORE ATTEMPTING TO DRAW!!!
        Card draw();
        void shuffle();
        bool addCardFront(Card theCard); // returns true if succesfully added
        bool addCardBack(Card theCard); // returns true if succesfully added
};

#endif
