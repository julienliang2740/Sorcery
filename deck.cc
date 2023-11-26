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
cardsNumber(cardsNumber) { std::cout << "calling deck ctor" << std::endl;}

Deck::~Deck() {
    std::cout << "calling deck destructor" << std::endl;
    for (auto card: theDeck) {
        if (card != nullptr) std::cout << "deleting a card" << std::endl;
        else std::cout << "deleting a nullptr" << std::endl;
        delete card;
    }
}

Deck::Deck(std::ifstream& deckFile, int ownerID): theDeck{std::vector<Card *>()}, cardsNumber{0}, ownershipID{ownerID} {
    std::cout << "deck ctor" << std::endl;
    std::string cardName;

    while (getline(deckFile, cardName)) {
        ++cardsNumber;
        Card * newCard = new Card(0, cardName, ownerID, cardtype::Minion, std::string("file"), false);
        theDeck.emplace_back(newCard);
        std::cout << "made a new card" << std::endl;
    }

    std::cout << "cards number: " << cardsNumber << std::endl;
}

int Deck::getNumCards() const {
    return cardsNumber;
}

bool Deck::isEmpty() {
    if (theDeck.empty()) return true;
    else return false;
}

Card* Deck::draw() {
    Card* drawnCard = theDeck[0];
    theDeck.erase(theDeck.begin());
    cardsNumber -= 1;
    return drawnCard;    
}

void Deck::shuffle() {
    std::shuffle (theDeck.begin(), theDeck.end(), std::default_random_engine(seed));
}

bool Deck::addCardFront(Card *theCard) {
    try{
        theDeck.insert(theDeck.begin(), theCard);
        cardsNumber += 1;
        return true;
    }
    catch (...){
        return false;
    }
}

bool Deck::addCardBack(Card *theCard) {
    try{
        theDeck.push_back(theCard);
        cardsNumber += 1;
        return true;
    }
    catch (...){
        return false;
    }
}

Deck& Deck::operator=(Deck&& other) noexcept {
    std::cout << "move assignment operator" << std::endl;
    if (this != &other) {
        std::cout << "this is not other" << std::endl;

        for (Card* card: theDeck) {
            delete card;
        }

        std::swap(theDeck, other.theDeck);

        cardsNumber = other.cardsNumber;
        ownershipID = other.ownershipID;
        other.theDeck.clear();
        std::cout << "just cleared other deck" << std::endl;
        other.cardsNumber = 0;
    } else {
        std::cout << "self assignment" << std::endl;
    }
    return *this;
}
