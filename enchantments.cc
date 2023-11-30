#include "enchantments.h"

int GiantStrength::getAttack() const {
    return 2 + next->getAttack();
}

int GiantStrength::getDefense() const {
    return 2 + next->getDefense();
}

int Enrage::getAttack() const {
    return 2 * next->getAttack();
}

int Enrage::getDefense() const {
    return 2 * next->getDefense();
}

actAbility Silence::getActivatedAbility() const {
    return actAbility::silenced;
}

GiantStrength::GiantStrength(int ownershipID):
    Enchantment(1, "Giant Strength", ownershipID, "individual_cards/giantstrength.txt", nullptr) {}

Enrage::Enrage(int ownershipID):
    Enchantment(2, "Enrage", ownershipID, "individual_cards/enrage.txt", nullptr) {}

Haste::Haste(int ownershipID):
    Enchantment(1, "Haste", ownershipID, "individual_cards/haste.txt", nullptr) {}

MagicFatigue::MagicFatigue(int ownershipID):
    Enchantment(0, "Magic Fatigue", ownershipID, "individual_cards/magicfatigue.txt", nullptr) {}

Silence::Silence(int ownershipID):
    Enchantment(1, "Silence", ownershipID, "individual_cards/silence.txt", nullptr) {}\

actAbility Silence::getActivatedAbility() const {
    return minionHasAbility::hasnoability;
}
