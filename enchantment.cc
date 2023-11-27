#include "enchantment.h"

Enchantment::Enchantment(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next):
    MinionComponent{cost, name, ownershipID, cardtype::Enchantment, displayFile, false}, next{next} {}

Enchantment::~Enchantment() {
    delete next;
}

int Enchantment::getDefense() const {
    return next->getDefense();
}

int Enchantment::getAttack() const {
    return next->getAttack();
}

int Enchantment::getTotalDamage() const {
    return next->getTotalDamage();
}

void Enchantment::beAttacked(int n) {
    next->beAttacked(n);
}

void Enchantment::attackMinion(MinionComponent* m) {
    m->beAttacked(getAttack());
    beAttacked(m->getAttack());
}
