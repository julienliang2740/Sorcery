#include "spell.h"

Card::Card(int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile, bool hasTarget) : 

Spell::Spell(int cost, std::string name, int ownershipID, std::string displayFile, bool hasTarget) :
    Card{cost, name, ownershipID, cardtype::S, displayFile, hasTarget} {}

Spell::Spell() {}

Spell* Spell::makeBanish(int ownershipID) {
    Spell* newSpell = new Spell{2, "Banish", ownershipID, "individual_cards/banish.txt", true};
    return newSpell;
}

Spell* Spell::makeUnsummon(int ownershipID) {
    Spell* newSpell = new Spell{1, "Unsummon", ownershipID, "individual_cards/unsummon.txt", true};
    return newSpell;
}

Spell* Spell::makeRecharge(int ownershipID) {
    Spell* newSpell = new Spell{1, "Recharge", ownershipID, "individual_cards/recharge.txt", false};
    return newSpell;
}

Spell* Spell::makeDisenchant(int ownershipID) {
    Spell* newSpell = new Spell{1, "Disenchant", ownershipID, "individual_cards/disenchant.txt", true};
    return newSpell;
}

Spell* Spell::makeRaiseDead(int ownershipID) {
    Spell* newSpell = new Spell{1, "Raise Dead", ownershipID, "individual_cards/raisedead.txt", false};
    return newSpell;
}

Spell* Spell::makeBlizzard(int ownershipID) {
    Spell* newSpell = new Spell{1, "Raise Dead", ownershipID, "individual_cards/blizzard.txt", false};
    return newSpell;
}
