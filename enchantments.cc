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

int MagicFatigue::getAbilityCost() const {
    return 2 + next->getAbilityCost();
}

GiantStrength::GiantStrength(int ownershipID):
    Enchantment(1, "Giant Strength", ownershipID, "individual_cards/giantstrength.txt", nullptr, true, "") {}

Enrage::Enrage(int ownershipID):
    Enchantment(2, "Enrage", ownershipID, "individual_cards/enrage.txt", nullptr, true, "") {}

Haste::Haste(int ownershipID):
    Enchantment(1, "Haste", ownershipID, "individual_cards/haste.txt", nullptr, false, "Enchanted minion gains +1 act ion each turn") {}

MagicFatigue::MagicFatigue(int ownershipID):
    Enchantment(0, "Magic Fatigue", ownershipID, "individual_cards/magicfatigue.txt", nullptr, false, "Enchanted minion's activated  ability costs 2 more") {}

Silence::Silence(int ownershipID):
    Enchantment(1, "Silence", ownershipID, "individual_cards/silence.txt", nullptr, false, "Enchanted minion cannot use abilities") {}
