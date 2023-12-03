#include "minion.h"

Minion::Minion(int cost, std::string name, int ownershipID, int defense, int attack, int totalDamage, actAbility aAbility, bool needsTarget, minionHasAbility abilityOfMinion, int abilityCost, std::string description): 
    MinionComponent{cost, name, ownershipID, cardtype::M, false, nullptr, description}, defense{defense},
    attack{attack}, totalDamage{totalDamage}, aAbility{aAbility}, needsTarget{needsTarget}, abilityOfMinion{abilityOfMinion}, abilityCost{abilityCost} {}

Minion::Minion(MinionComponent* other):
    MinionComponent{other->getCost(), other->getName(), other->getID(), cardtype::M, false, nullptr, other->getMinionDescription()},
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
    Minion* m = new Minion{0, "Air Elemental", ownershipID, 1, 1, 0, actAbility::none, false, minionHasAbility::hasnoability, 0, ""};
    return m;
}

Minion* Minion::makeEarthElemental(int ownershipID) {
    Minion* m = new Minion{3, "Earth Elemental", ownershipID, 4, 4, 0, actAbility::none, false, minionHasAbility::hasnoability, 0, ""};
    return m;
}

Minion* Minion::makeFireElemental(int ownershipID) {
    Minion* m = new Minion{2, "Fire Elemental", ownershipID, 2, 2, 0, actAbility::none, false, minionHasAbility::hastriggeredability, 0, "Whenever an opponent’s minion enters play, deal 1 damage to it."};
    return m;
}

Minion* Minion::makeBoneGolem(int ownershipID) {
    Minion* m = new Minion{2, "Bone Golem", ownershipID, 1, 3, 0, actAbility::none, false, minionHasAbility::hastriggeredability, 0, "Gain +1/+1 whenever a minion leaves play."};
    return m;
}

Minion* Minion::makeNovicePyromancer(int ownershipID) {
    Minion* m = new Minion{1, "Novice Pyromancer", ownershipID, 0, 1, 0, actAbility::pyro, true, minionHasAbility::hasactivatedability, 1, "Deal 1 damage to target minion"};
    return m;
}

Minion* Minion::makeAppSummoner(int ownershipID) {
    Minion* m = new Minion{1, "Apprentice Summoner", ownershipID, 1, 1, 0, actAbility::asumm, false, minionHasAbility::hasactivatedability, 1, "Summon a 1/1 air elemental"};
    return m;
}

Minion* Minion::makeMsSummoner(int ownershipID) {
    Minion* m = new Minion{3, "Master Summoner", ownershipID, 2, 3, 0, actAbility::msumm, false, minionHasAbility::hasactivatedability, 2, "Summon up to three 1/1 air elementals"};
    return m;
}

Minion* Minion::makePotionSeller(int ownershipID) {
    Minion* m = new Minion{2, "Potion Seller", ownershipID, 1, 3, 0, actAbility::none, false, minionHasAbility::hastriggeredability, 0, "At the end of your turn, all your minions gain +0/+1."};
    return m;
}

bool Minion::abilityNeedsTarget() const {
    return needsTarget;
}

minionHasAbility Minion::getHasAbility() const {
   return abilityOfMinion;
}

int Minion::getAbilityCost() const {
    return abilityCost;
}

std::string Minion::getMinionDescription() const {
    return description;
}

void Minion::modDefense(int n) {
    defense += n;
}

void Minion::modAttack(int n) {
    attack += n;
}