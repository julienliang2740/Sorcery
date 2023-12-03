#include "spell.h"

Spell::Spell(int cost, std::string name, int ownershipID, bool hasTarget, std::string description) noexcept :
    Card{cost, name, ownershipID, cardtype::S, hasTarget, description} {}

Spell* Spell::makeBanish(int ownershipID) {
    Spell* newSpell = new Spell{2, "Banish", ownershipID, true, "Destroy target minion or ritual"};
    return newSpell;
}

Spell* Spell::makeUnsummon(int ownershipID) {
    Spell* newSpell = new Spell{1, "Unsummon", ownershipID, true, "Return target minion to its owner's hand"};
    return newSpell;
}

Spell* Spell::makeRecharge(int ownershipID) {
    Spell* newSpell = new Spell{1, "Recharge", ownershipID, false, "Your ritual gains 3 charges"};
    return newSpell;
}

Spell* Spell::makeDisenchant(int ownershipID) {
    Spell* newSpell = new Spell{1, "Disenchant", ownershipID, true, "Destroy the top enchantment on target minion"};
    return newSpell;
}

Spell* Spell::makeRaiseDead(int ownershipID) {
    Spell* newSpell = new Spell{1, "Raise Dead", ownershipID, false, "Resurrect the top minion in your graveyard and set its defence to 1"};
    return newSpell;
}

Spell* Spell::makeBlizzard(int ownershipID) {
    Spell* newSpell = new Spell{1, "Blizzard", ownershipID, false, "Deal 2 damage to all minions"};
    return newSpell;
}
