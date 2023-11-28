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

    if (type == cardtype::M) {

        std::string name = c->getName();
        
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

    } else if (type == cardtype::S) {
        return false; // IMPLEMENT
    } else if (type == cardtype::R) {
        return false; // IMPLEMENT
    } else if (type == cardtype::E) {
        return false; // IMPLEMENT
    }

    if (placed) {
        activePlayer->removeCard(i);
        delete c;
    }

    return placed;
}

bool Board::attackMinion(int curMinion, int target) {
    curMinions = (activePlayerID == player1.getID()) ? p1Minions : p2minions;
    targetMinions = (curMinions == p1Minions) ? p2Minions : p1Minions;

    if (curMinion > curMinions.size() || curMinion < 1) {
        std::cerr << "you don't have that minion!" << std::endl;
        return false;
    }

    if (target > targetMinions.size() || target < 1) {
        std::cerr << "your opponent doesn't have that minion!" << std::endl;
        return false;
    }

    
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
