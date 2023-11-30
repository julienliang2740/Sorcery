#include "minion.h"

Minion::Minion(int cost, std::string name, int ownershipID, std::string displayFile, int defense, int attack, int totalDamage, actAbility aAbility, bool needsTarget): 
    MinionComponent{cost, name, ownershipID, cardtype::M, displayFile, false, nullptr}, defense{defense},
    attack{attack}, totalDamage{totalDamage}, aAbility{aAbility}, needsTarget{needsTarget} {}

Minion::Minion(MinionComponent* other):
    MinionComponent{other->getCost(), other->getName(), other->getID(), cardtype::M, other->getFile(), false, nullptr},
    defense{other->getDefense()}, attack{other->getAttack()}, totalDamage{other->getTotalDamage()} {}

Minion::~Minion() {
    // delete actAbility;
    // delete tAbility; // uncomment when abilities are implemented.
}

std::string Minion::getMinionName() const {
    return name;
}

actAbility Minion::getActivatedAbility() const {
    return aAbility;
}

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

void Minion::reset() {
    totalDamage = 0;
}

void Minion::setDefense(int n) {
    if (n < 1) {
        return;
    }

    defense = n;
}


// static functions to make default minions

Minion* Minion::makeAirElemental(int ownershipID) {
    Minion* m = new Minion{0, "Air Elemental", ownershipID, "individual_cards/airelemental.txt", 1, 1, 0, actAbility::none, false}, minionHasAbility::hasnoability;
    return m;
}

Minion* Minion::makeEarthElemental(int ownershipID) {
    Minion* m = new Minion{3, "Earth Elemental", ownershipID, "individual_cards/earthelemental.txt", 4, 4, 0, actAbility::none, false, minionHasAbility::hasnoability};
    return m;
}

Minion* Minion::makeFireElemental(int ownershipID) {
    Minion* m = new Minion{2, "Fire Elemental", ownershipID, "individual_cards/fireelemental.txt", 2, 2, 0, actAbility::none, false, minionHasAbility::hastriggeredability};
    return m;
}

Minion* Minion::makeBoneGolem(int ownershipID) {
    Minion* m = new Minion{2, "Bone Golem", ownershipID, "individual_cards/bonegolem.txt", 1, 3, 0, actAbility::none, false, minionHasAbility::hastriggeredability};
    return m;
}

Minion* Minion::makeNovicePyromancer(int ownershipID) {
    Minion* m = new Minion{1, "Novice Pyromancer", ownershipID, "individual_cards/novicepyromancer.txt", 0, 1, 0, actAbility::pyro, true, minionHasAbility::hasactivatedability};
    return m;
}

Minion* Minion::makeAppSummoner(int ownershipID) {
    Minion* m = new Minion{1, "Apprentice Summoner", ownershipID, "individual_cards/apprenticesummoner.txt", 1, 1, 0, actAbility::asumm, false, minionHasAbility::hasactivatedability};
    return m;
}

Minion* Minion::makeMsSummoner(int ownershipID) {
    Minion* m = new Minion{3, "Master Summoner", ownershipID, "individual_cards/mastersummoner.txt", 2, 3, 0, actAbility::msumm, false, minionHasAbility::hasactivatedability};
    return m;
}

Minion* Minion::makePotionSeller(int ownershipID) {
    Minion* m = new Minion{2, "Potion Seller", ownershipID, "individual_cards/potionseller.txt", 1, 3, 0, actAbility::none, false, minionHasAbility::hastriggeredability};
    return m;
}

bool Minion::abilityNeedsTarget() const {
    return needsTarget;
}

minionHasAbility Minion::getHasAbility() const {
    return abilityOfMinion;
}