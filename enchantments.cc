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

int Haste::getNumActions() const {
    return 1 + next->getNumActions();
}

GiantStrength::GiantStrength(int ownershipID):
    Enchantment(1, "Giant Strength", ownershipID, nullptr, true, "") {}

Enrage::Enrage(int ownershipID):
    Enchantment(2, "Enrage", ownershipID, nullptr, true, "") {}

Haste::Haste(int ownershipID):
    Enchantment(1, "Haste", ownershipID, nullptr, false, "Enchanted minion gains +1 action each turn") {}

MagicFatigue::MagicFatigue(int ownershipID):
    Enchantment(0, "Magic Fatigue", ownershipID, nullptr, false, "Enchanted minion's activated  ability costs 2 more") {}

Silence::Silence(int ownershipID):
    Enchantment(1, "Silence", ownershipID, nullptr, false, "Enchanted minion cannot use abilities") {}
