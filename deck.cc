#include <iostream>
#include <string>
#include <vector>

#include "deck.h"

// Shuffle strategy based on example at:
// http://www.cplusplus.com/reference/algorithm/shuffle/
// shuffle algorithm example
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

// obtain a time-based seed:
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

Deck::Deck(std::vector<Card *> theDeck, int cardsNumber) : 
theDeck(theDeck), 
cardsNumber(cardsNumber) {}

Card::Card(int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile, bool hasTarget) : 


Deck::Deck(std::ifstream& deckFile, int ownerID): theDeck{vector<Card *>()}, cardsNumber{0}, ownershipID{ownerID} {
    string cardName;

    while (getline(deckFile, cardName)) {
        ++cardsNumber;
        Card * newCard = new Card(0, cardName, 0, ownerID, cardtype::Minion, "file", false);
    }
}

int Deck::getNumCards() {
    return cardsNumber;
}

bool Deck::isEmpty() {
    if (theDeck.empty()) return true;
    else return false;
}

Card Deck::draw() {
    Card drawnCard = theDeck[0];
    theDeck.erase(theDeck.begin());
    cardsNumber -= 1;
    return drawnCard;    
}

void Deck::shuffle() {
    std::shuffle (theDeck.begin(), theDeck.end(), std::default_random_engine(seed));
}

bool Deck::addCardFront(Card theCard) {
    try{
        theDeck.insert(theDeck.begin(), theCard);
        cardsNumber += 1;
        return true;
    }
    catch (...){
        return false;
    }
}

bool Deck::addCardBack(Card theCard) {
    try{
        theDeck.push_back(theCard);
        cardsNumber += 1;
        return true;
    }
    catch (...){
        return false;
    }
}

#include "deck.h"
