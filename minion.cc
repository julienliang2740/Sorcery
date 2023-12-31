#include "minion.h"

Minion::Minion(int cost, std::string name, int ownershipID, int attack, int defense, int totalDamage, int actions, actAbility aAbility, bool needsTarget, minionHasAbility abilityOfMinion, int abilityCost, std::string description): 
    MinionComponent{cost, name, ownershipID, cardtype::M, false, nullptr, description}, attack{attack}, defense{defense},
    totalDamage{totalDamage}, actions{actions}, aAbility{aAbility}, needsTarget{needsTarget}, abilityOfMinion{abilityOfMinion}, abilityCost{abilityCost}, tAbility{nullptr} {}

Minion::Minion(MinionComponent* other):
    MinionComponent{other->getCost(), other->getName(), other->getID(), cardtype::M, false, nullptr, other->getMinionDescription()},
    attack{other->getAttack()}, defense{other->getDefense()}, totalDamage{other->getTotalDamage()} {}

Minion::~Minion() {
    delete tAbility;
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

void Minion::resetDamage() {
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
    Minion* m = new Minion{0, "Air Elemental", ownershipID, 1, 1, 0, 0, actAbility::none, false, minionHasAbility::hasnoability, 0, ""};
    return m;
}

Minion* Minion::makeEarthElemental(int ownershipID) {
    Minion* m = new Minion{3, "Earth Elemental", ownershipID, 4, 4, 0, 0, actAbility::none, false, minionHasAbility::hasnoability, 0, ""};
    return m;
}

Minion* Minion::makeFireElemental(int ownershipID) {
    Minion* m = new Minion{2, "Fire Elemental", ownershipID, 2, 2, 0, 0, actAbility::none, false, minionHasAbility::hastriggeredability, 0, "Whenever an opponent's minion enters play, deal 1 damage to it."};
    return m;
}

Minion* Minion::makeBoneGolem(int ownershipID) {
    Minion* m = new Minion{2, "Bone Golem", ownershipID, 1, 3, 0, 0, actAbility::none, false, minionHasAbility::hastriggeredability, 0, "Gain +1/+1 whenever a minion leaves play."};
    return m;
}

Minion* Minion::makeNovicePyromancer(int ownershipID) {
    Minion* m = new Minion{1, "Novice Pyromancer", ownershipID, 0, 1, 0, 0, actAbility::pyro, true, minionHasAbility::hasactivatedability, 1, "Deal 1 damage to target minion"};
    return m;
}

Minion* Minion::makeAppSummoner(int ownershipID) {
    Minion* m = new Minion{1, "Apprentice Summoner", ownershipID, 1, 1, 0, 0, actAbility::asumm, false, minionHasAbility::hasactivatedability, 1, "Summon a 1/1 air elemental"};
    return m;
}

Minion* Minion::makeMsSummoner(int ownershipID) {
    Minion* m = new Minion{3, "Master Summoner", ownershipID, 2, 3, 0, 0, actAbility::msumm, false, minionHasAbility::hasactivatedability, 2, "Summon up to three 1/1 air elementals"};
    return m;
}

Minion* Minion::makePotionSeller(int ownershipID) {
    Minion* m = new Minion{2, "Potion Seller", ownershipID, 1, 3, 0, 0, actAbility::none, false, minionHasAbility::hastriggeredability, 0, "At the end of your turn, all your minions gain +0/+1."};
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

int Minion::getNumActions() const {
    return actions;
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

void Minion::setActions(int n) {
    actions = n;
}

void Minion::useActions(int n) {
    actions -= n;
}

int Minion::getMinionCost() const {
    return getCost();
}

int Minion::getMinionID() const {
    return getID();
}

void Minion::setTriggeredAbility(triggeredAbility* t) {
    tAbility = t;
}

triggeredAbility* Minion::getTriggeredAbility() const {
    return tAbility;
}

void Minion::toggleAbilityOn() {
    if (tAbility != nullptr) {
        tAbility->toggleOn();
    }
}

void Minion::toggleAbilityOff() {
    if (tAbility != nullptr) {
        tAbility->toggleOff();
    }
}

Minion* Minion::getBaseMinion() const {
    return const_cast<Minion*>(this);
}
