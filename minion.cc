#include "minion.h"

Minion::Minion(int cost, std::string name, int ownershipID, std::string displayFile, int defense, int attack): 
    MinionComponent{cost, name, ownershipID, cardtype::Minion, displayFile, false}, defense{defense},
    attack{attack}, totalDamage{0} {}

Minion::~Minion() {}

int Minion::getDefense() const {
    return defense;
}

int Minion::getAttack() const {
    return attack;
}

int Minion::getTotalDamage() const {
    return totalDamage;
}

void Minion::beAttacked(int n) {
    totalDamage +=n;
}

void Minion::attackMinion(MinionComponent* other) {
    other->beAttacked(attack);
    beAttacked(other->getAttack());
}

MinionComponent* Minion::makeAirElemental(int ownershipID) {
    Minion* m = new Minion{0, "Air Elemental", ownershipID, "individual_cards/airelemental.txt", 1, 1};
    return m;
}

MinionComponent* Minion::makeEarthElemental(int ownershipID) {
    Minion* m = new Minion{3, "Earth Elemental", ownershipID, "individual_cards/earthelemental.txt", 4, 4};
    return m;
}
