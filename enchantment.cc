#include "enchantment.h"

Enchantment::Enchantment(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next, bool hasStats, std::string abilityDescription):
    MinionComponent{cost, name, ownershipID, cardtype::E, displayFile, false, next}, hasStats{hasStats}, abilityDescription{abilityDescription} {}

Enchantment::~Enchantment() {}

int Enchantment::getDefense() const {
    return next->getDefense();
}

int Enchantment::getAttack() const {
    return next->getAttack();
}

int Enchantment::getTotalDamage() const {
    return next->getTotalDamage();
}

std::string Enchantment::getMinionName() const {
    return next->getMinionName();
}

actAbility Enchantment::getActivatedAbility() const {
    return next->getActivatedAbility();
}

void Enchantment::setNext(MinionComponent* m) {
    next = m;
}

void Enchantment::beAttacked(int n) {
    next->beAttacked(n);
}

void Enchantment::attackMinion(MinionComponent* m) {
    m->beAttacked(getAttack());
    beAttacked(m->getAttack());
}

bool Enchantment::abilityNeedsTarget() const {
    return next->abilityNeedsTarget();
}

minionHasAbility Enchantment::getHasAbility() const {
    return next->getHasAbility();
}

bool Enchantment::getHasStats() const {
    return hasStats;
}

std::string Enchantment::getAbilityDesc() const {
    return abilityDescription;
}
