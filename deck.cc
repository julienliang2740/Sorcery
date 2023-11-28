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
std::default_random_engine engine(seed);

Deck::Deck(std::vector<Card *> theDeck, int cardsNumber) : 
theDeck(theDeck), 
cardsNumber(cardsNumber) {}

Deck::~Deck() {
    for (auto card: theDeck) {
        delete card;
    }
}

Minion* Deck::makeMinionFromName(std::string name, int playerID) {
    Minion* newMinion = (name == "Air Elemental") ? Minion::makeAirElemental(activePlayerID)
                            : ((name == "Earth Elemental") ? Minion::makeEarthElemental(activePlayerID)
                            : ((name == "Bone Golem") ? Minion::makeBoneGolem(activePlayerID)
                            : ((name == "Novice Pyromancer") ? Minion::makeNovicePyromancer(activePlayerID)
                            : ((name == "Fire Elemental") ? Minion::makeFireElemental(activePlayerID)
                            : ((name == "Potion Seller") ? Minion::makePotionSeller(activePlayerID)
                            : ((name == "Apprentice Summoner") ? Minion::makeAppSummoner(activePlayerID)
                            : Minion::makeMsSummoner(activePlayerID)))))));
    return newMinion;
}

bool Deck::nameIsMinion(std::string name) {
    return (name == "Air Elemental") || (name == "Earth Elemental") || (name == "Fire Elemental") || (name == "Bone Golem")
            || (name == "Novice Pyromancer") || (name == "Potion Seller") || (name == "Apprentice Summoner") || (name == "Master Summoner");
}

bool Deck::nameIsSpell(std::string name) {
    return (name == "Banish") || (name == "Unsummon") || (name == "Recharge") || (name == "Disenchant")
            || (name == "Raise Dead") || (name == "Blizzard");
}

Spell* Deck::makeSpellFromName(std::string name, int playerID) {
    Spell* newSpell = nullptr; // IMPLEMENT
    return newSpell;
}

Deck::Deck(std::ifstream& deckFile, int ownerID): theDeck{std::vector<Card *>()}, cardsNumber{0}, ownershipID{ownerID} {
    std::string cardName;

    while (getline(deckFile, cardName)) {
        ++cardsNumber;
        Card * newCard = (nameIsMinion(cardName)) ? makeMinionFromName(cardName, ownershipID)
                        : ((nameIsSpell(cardName)) ? makeSpellFromName(cardName, ownershipID)
                        : new Card(0, cardName, ownerID, cardtype::M, std::string("file"), false));
        theDeck.emplace_back(newCard);
    }
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
    std::shuffle (theDeck.begin(), theDeck.end(), engine);
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
