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

Minion* Deck::makeMinionFromName(std::string name, int PlayerID) {
    Minion* newMinion = ((name == "Air Elemental") || (name == "Air Elemental\r")) ? Minion::makeAirElemental(PlayerID)
                            : (((name == "Earth Elemental") || (name == "Earth Elemental\r")) ? Minion::makeEarthElemental(PlayerID)
                            : (((name == "Bone Golem") || (name == "Bone Golem\r")) ? Minion::makeBoneGolem(PlayerID)
                            : (((name == "Novice Pyromancer") || (name == "Novice Pyromancer\r")) ? Minion::makeNovicePyromancer(PlayerID)
                            : (((name == "Fire Elemental") || (name == "Fire Elemental\r")) ? Minion::makeFireElemental(PlayerID)
                            : (((name == "Potion Seller") || (name == "Potion Seller\r")) ? Minion::makePotionSeller(PlayerID)
                            : (((name == "Apprentice Summoner") || (name == "Apprentice Summoner\r")) ? Minion::makeAppSummoner(PlayerID)
                            : Minion::makeMsSummoner(PlayerID)))))));
    return newMinion;
}

Spell* Deck::makeSpellFromName(std::string name, int playerID) {
    Spell* newSpell = ((name == "Banish") || (name == "Banish\r")) ? Spell::makeBanish(playerID)
                        : (((name == "Unsummon") || (name == "Unsummon\r")) ? Spell::makeUnsummon(playerID)
                        : (((name == "Recharge") || (name == "Recharge\r")) ? Spell::makeRecharge(playerID)
                        : (((name == "Disenchant") || (name == "Disenchant\r")) ? Spell::makeDisenchant(playerID)
                        : (((name == "Raise Dead") || (name == "Raise Dead\r")) ? Spell::makeRaiseDead(playerID)
                        : Spell::makeBlizzard(playerID)))));
    return newSpell;
}

/*
Enchantment* Deck::makeEnchantmentFromName(std::string name, int playerID) {
    Enchantment* newEnchantment = ((name == "Giant Strength") || (name == "Giant Strength\r")) ? ...
                                    : (((name == "Enrage") || (name == "Enrage\r")) ? ...
                                    : (((name == "Haste") || (name == "Haste\r")) ? ...
                                    : (((name == "Magic Fatigue") || (name == "Magic Fatigue\r")) ? ...
                                    : )))
    ...
    return newEnchantment;
}
*/

bool Deck::nameIsMinion(std::string name) {
    return (name == "Air Elemental") || (name == "Earth Elemental") || (name == "Fire Elemental") || (name == "Bone Golem") || (name == "Novice Pyromancer") || (name == "Potion Seller") || (name == "Apprentice Summoner") || (name == "Master Summoner")
            || (name == "Air Elemental\r") || (name == "Earth Elemental\r") || (name == "Fire Elemental\r") || (name == "Bone Golem\r") || (name == "Novice Pyromancer\r") || (name == "Potion Seller\r") || (name == "Apprentice Summoner\r") || (name == "Master Summoner\r");
}

bool Deck::nameIsSpell(std::string name) {
    return (name == "Banish") || (name == "Unsummon") || (name == "Recharge") || (name == "Disenchant") || (name == "Raise Dead") || (name == "Blizzard")
            || (name == "Banish\r") || (name == "Unsummon\r") || (name == "Recharge\r") || (name == "Disenchant\r") || (name == "Raise Dead\r") || (name == "Blizzard\r");
}

bool Deck::nameIsEnchantment(std::string name) {
    return (name == "Giant Strength") || (name == "Enrage") || (name == "Haste") || (name == "Magic Fatigue") || (name == "Silence")
            || (name == "Giant Strength\r") || (name == "Enrage\r") || (name == "Haste\r") || (name == "Magic Fatigue\r") || (name == "Silence\r");
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
