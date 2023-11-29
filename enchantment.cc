#include "enchantment.h"

Enchantment::Enchantment(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next):
    MinionComponent{cost, name, ownershipID, cardtype::E, displayFile, false, next} {}

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

bool abilityHasTarget() const {
    return next->abilityHasTarget();
}
