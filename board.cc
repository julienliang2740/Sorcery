#include <iostream>
#include <string>
#include <vector>
#include "board.h"

Board::Board(
    std::vector<MinionComponent*> p1Minions, std::vector<MinionComponent*> p2Minions, 
    Player* player1, Player* player2, 
    int activePlayerID,
    std::vector<Minion*> p1Graveyard, std::vector<Minion*> p2Graveyard) :

    p1Minions{p1Minions}, p2Minions{p2Minions},
    player1{player1}, player2{player2},
    activePlayerID{activePlayerID},
    p1Graveyard{p1Graveyard}, p2Graveyard{p2Graveyard} {}

int Board::getActiveID() {
    return activePlayerID;
}

void Board::addObserver(int n) {
    observers.emplace_back(n);
}

int Board::endTurn() {
    for (auto p: observers) {
        // LOOP THROUGH OBSERVERS AND NOTIFY THEM
    }

    if (activePlayerID == player1->getID()) {
        activePlayerID = player2->getID();
    } else {
        activePlayerID = player1->getID();
    }

    return activePlayerID;
}


// EDIT THIS FUNCTION AFTER MINION CLASS IS MADE
bool Board::placeMinion(std::vector<MinionComponent*>& minions, Minion* minion) {
    if (minions.size() > 4) {
        return false;
    } else {
        minions.emplace_back(minion);
        return true;
    }
}


bool Board::addMinion(Minion* minion) {
    bool placed = false;

    if (activePlayerID == player1->getID()) {
        placed = placeMinion(p1Minions, minion);
    } else {
        placed = placeMinion(p2Minions, minion);
    }

    if (placed) {
        for (auto observer: observers) {
            // LOOP THROUGH AND NOTIFY
        }
    }

    return placed;
}


bool Board::playCard(int i, int p, int t) {

    Player* activePlayer = (activePlayerID == player1->getID()) ? player1 : player2;

    if (i < 1 || i > activePlayer->getHand().size()) {
        std::cerr << "no such card exists" << std::endl;
        return false;
    }

    Card* c = activePlayer->getHand()[i - 1];

    if (c->hasATarget() && (p < 0 || t < 0)) {
        std::cerr << "must provide target for card" << std::endl;
        return false;
    }

    bool placed = false;

    cardtype type = c->getCardType();
    std::string name = c->getName();

    if (type == cardtype::M) {
        std::cout << "minion name: " << name << std::endl;
        std::cout << "name is equal to Air Elemental: " << (name == "Air Elemental") << std::endl;
        std::cout << "name is equal to Earth Elemental: " << (name == "Earth Elemental") << std::endl;
        std::cout << "name is equal to Bone Golem: " << (name == "Bone Golem") << std::endl;
        std::cout << "name is equal to Novice Pyromancer: " << (name == "Novice Pyromancer") << std::endl;
        std::cout << "name is equal to Fire Elemental: " << (name == "Fire Elemental") << std::endl;
        std::cout << "name is equal to Potion Seller: " << (name == "Potion Seller") << std::endl;
        std::cout << "name is equal to Apprentice Summoner: " << (name == "Apprentice Summoner") << std::endl;
        std::cout << "name is equal to Master Summoner: " << (name == "Master Summoner") << std::endl;
        Minion* newMinion = (name == "Air Elemental") ? Minion::makeAirElemental(activePlayerID)
                            : ((name == "Earth Elemental") ? Minion::makeEarthElemental(activePlayerID)
                            : ((name == "Bone Golem") ? Minion::makeBoneGolem(activePlayerID)
                            : ((name == "Novice Pyromancer") ? Minion::makeNovicePyromancer(activePlayerID)
                            : ((name == "Fire Elemental") ? Minion::makeFireElemental(activePlayerID)
                            : ((name == "Potion Seller") ? Minion::makePotionSeller(activePlayerID)
                            : ((name == "Apprentice Summoner") ? Minion::makeAppSummoner(activePlayerID)
                            : Minion::makeMsSummoner(activePlayerID)))))));

        placed = addMinion(newMinion);
        
        if (!placed) {
            delete newMinion;
        }
    } 

    else if (type == cardtype::S) {
        if (name == "Banish") {
            moveMinionToGraveyard(p, t);
        }
        else if (name == "Unsummon") { //wip
            std::cout << "Unsummon is currently under development" << std::endl;
        }
        else if (name == "Recharge") {
            std::cout << "Recharge is currently under development" << std::endl;
        }
        else if (name == "Disenchant") { //wip
            std::cout << "Disenchant is currently under development" << std::endl;
        }
        else if (name == "Raise Dead") { //wip
            std::cout << "Disenchant is currently under development" << std::endl;
        }
        else if (name == "Blizzard") {
            for (MinionComponent* victim : p1Minions) victim->beAttacked(2);
            for (MinionComponent* victim : p1Minions) victim->beAttacked(2);
        }
        else std::cout << "bruga spells isnt getting picked properly" << std::endl;
    } 

    else if (type == cardtype::R) {
        return false; // IMPLEMENT
    } 
    
    else if (type == cardtype::E) {
        return false; // IMPLEMENT
    }

    if (placed) {
        activePlayer->removeCard(i);
        delete c;
    }

    return placed;
}

Minion* Board::deleteEnchantments(int ownershipID, int minion) {
    if (ownershipID != 1 && ownershipID != 2) {
        std::cerr << "invalid player ID" << std::endl;
        return nullptr;
    }

    std::vector<MinionComponent*>& minions = (activePlayerID == player1->getID()) ? p1Minions : p2Minions;

    if (minion > minions.size()) {
        std::cerr << "invalid minion ID" << std::endl;
        return nullptr;
    }

    MinionComponent* cur = minions[minion - 1];

    while (cur->getType() != cardtype::M) {
        MinionComponent* temp = cur;
        cur = cur->getNext();
        delete temp;
    }

    Minion* theMinion = new Minion{cur}; // copies over the contents of cur into a new minion.
    // this is because we want the return type to be a Minion*, not a MinionComponent*
    minions[minion - 1] = theMinion;
    delete cur;
    return theMinion;
}

bool Board::moveMinionToGraveyard(int ownershipID, int minion) {
    if (ownershipID != 1 && ownershipID != 2) {
        std::cerr << "invalid player ID" << std::endl;
        return false;
    }

    std::vector<MinionComponent*>& minions = (activePlayerID == player1->getID()) ? p1Minions : p2Minions;
    std::vector<Minion*>& graveyard = (activePlayerID == player1->getID()) ? p1Graveyard : p2Graveyard;

    if (minion > minions.size()) {
        std::cerr << "invalid minion ID" << std::endl;
        return false;
    }

    Minion* m = deleteEnchantments(ownershipID, minion);
    minions.erase(minions.begin() + (minion - 1));
    graveyard.emplace_back(m);
    return true;
}

bool Board::useActivatedAbility(int minionUser, int targetPlayerID, int targetMinion) {
    return false;
}

bool Board::attackMinion(int curMinion, int target) {
    std::vector<MinionComponent*>& curMinions = (activePlayerID == player1->getID()) ? p1Minions : p2Minions;
    std::vector<MinionComponent*>& targetMinions = (curMinions == p1Minions) ? p2Minions : p1Minions;

    if (curMinion > curMinions.size() || curMinion < 1) {
        std::cerr << "you don't have that minion!" << std::endl;
        return false;
    }

    if (target > targetMinions.size() || target < 1) {
        std::cerr << "your opponent doesn't have that minion!" << std::endl;
        return false;
    }

    MinionComponent* attacker = curMinions[curMinion - 1];
    MinionComponent* attacked = targetMinions[target - 1];

    attacker->attackMinion(attacked);

    if (attacker->getDefense() - attacker->getTotalDamage() < 1) {
        moveMinionToGraveyard(activePlayerID, curMinion);
    }

    if (attacked->getDefense() - attacked->getTotalDamage() < 1) {
        moveMinionToGraveyard(1 + (activePlayerID % 2), target);
    }

    return true;
}

int Board::checkWinState() {
    int p1_lost = -1;
    int p1_won = 1;
    int stillPlaying = 0;
    if (player1->getHealth() < 1) {
        return p1_lost;
    } else if (player2->getHealth() < 1) {
        return p1_won;
    } else {
        return stillPlaying;
    }
}
