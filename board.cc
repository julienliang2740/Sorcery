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
    p1Graveyard{p1Graveyard}, p2Graveyard{p2Graveyard} {
        std::cout << "player 1 deck has " << player1->playerDeck->getNumCards() << " cards" << std:: endl;
        std::cout << "player 2 deck has " << player2->playerDeck->getNumCards() << " cards" << std:: endl;
    }

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

    if (type == cardtype::Minion) {
        if (c->getName() == "Air Elemental") {
            Minion* newMinion = Minion::makeAirElemental();
            placed = addMinion(newMinion);
            if (placed) {
                delete c;
                activePlayer->getHand.erase(i - 1); // actually this is NOT how erase works, but uh just keep this for now
            } else {
                delete newMinion;
            }
        } else if (c->getName() == "Earth Elemental") {
            Minion* newMinion = Minion::makeEarthElemental();
            placed = addMinion(newMinion);
            if (placed) {
                delete c;
                activePlayer->getHand.erase(i - 1); // actually this is NOT how erase works, but uh just keep this for now
            } else {
                delete newMinion;
            }
        }
        // THEN MAKE ANOTHER THING FOR EVERY FUCKING MINION HOLY SHIT
    } else if (type == cardtype::Spell) {
        return false; // IMPLEMENT
    } else if (type == cardtype::Ritual) {
        return false; // IMPLEMENT
    } else if (type == cardtype::Enchantment) {
        return false; // IMPLEMENT
    }

    if (placed) {
        activePlayer->removeCard(i);
    }

    return placed;
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
