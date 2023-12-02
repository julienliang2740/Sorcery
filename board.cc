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
    if (activePlayerID == player1->getID()) {
        activePlayerID = player2->getID();
    } else {
        activePlayerID = player1->getID();
    }

    for (auto observer: observers) {
        if (observer->subType() == triggerType::EndTurn) {
            observer->notify(0, 0);
        }
    }

    return activePlayerID;
}

Player* Board::getActivePlayer() {
    return (activePlayerID == player1->getID()) ? player1 : player2;
}

void Board::attackPlayer(int minion) {
    Player* activePlayer = getActivePlayer();
    std::vector<MinionComponent*> ownMinions = (activePlayerID == player1->getID()) ? p1Minions : p2Minions;
    
    if (static_cast<int>(ownMinions.size()) < minion || minion < 1) {
        std::cerr << "invalid minion" << std::endl;
        return;
    }

    Player* victim = (activePlayer == player1) ? player2 : player1;

    victim->addHealth(-(ownMinions[minion - 1]->getAttack()));
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

    Player* activePlayer = getActivePlayer();

    if (i < 1 || i > activePlayer->getHand().size()) {
        std::cerr << "no such card exists" << std::endl;
        return false;
    }

    Card* c = activePlayer->getHand()[i - 1];

    if (c->hasATarget() && (((p != 1) && (p != 2)) || t < 1)) {
        std::cerr << "must provide target for card" << std::endl;
        return false;
    }

    std::vector<MinionComponent*>& targetMinions = (p == player1->getID()) ? p1Minions : p2Minions;

    if (static_cast<int>(targetMinions.size()) < t) {
        std::cerr << "target minions size: " << targetMinions.size() << std::endl;
        std::cerr << "provided t-value: " << t << std::endl;
        std::cerr << "invalid target minion" << std::endl;
        return false;
    }

    bool wasplaced = false;

    cardtype type = c->getCardType();
    std::string name = c->getName();

    if (type == cardtype::M) {
        std::cout << "placing a minion" << std::endl;
        Minion* newMinion = static_cast<Minion*>(c);
        wasplaced = addMinion(newMinion);
    } 

    else if (type == cardtype::S) {
        if (name == "Banish") {
            moveMinionToGraveyard(p, t);
        }
        else if (name == "Unsummon") { //wip
            Player* targetPlayer = (p == player1->getID()) ? player1 : player2;
            if ((targetPlayer != activePlayer) && (targetPlayer->getHand().size() >= Player::getHandMax())) {
                std::cerr << "cannot unsummon. Opponent's hand is full.";
                return false;
            }

            activePlayer->removeCard(i);
            Minion* m = deleteEnchantments(targetPlayer->getID(), t);
            targetMinions.erase(targetMinions.begin() + (t - 1));
            targetPlayer->addCardToHand(m);
        }
        else if (name == "Recharge") {
            std::cout << "Recharge is currently under development" << std::endl;
        }
        else if (name == "Disenchant") { //wip

            if (targetMinions[t - 1]->getCardType() != cardtype::E) {
                std::cerr << "minion is not enchanted - cannot disenchant" << std::endl;
                return false;
            }

            MinionComponent* temp = targetMinions[t - 1];
            targetMinions[t - 1] = (targetMinions[t - 1])->getNext();
            delete temp;
            wasplaced = true;
        }
        else if (name == "Raise Dead") { //wip
            
            std::vector<MinionComponent*> ownMinions = (c->getID() == player1->getID()) ? p1Minions : p2Minions;
            if (ownMinions.size() > 4) {
                std::cerr << "minions are at capacity. Cannot raise dead" << std::endl;
            }

            std::vector<Minion*>& graveyard = (c->getID() == player1->getID()) ? p1Graveyard : p2Graveyard;
            if (graveyard.empty()) {
                std::cerr << "no minions in graveyard to revive" << std::endl;
            }

            Minion* m = graveyard.back();
            graveyard.pop_back();
            ownMinions.emplace_back(m);
            wasplaced = true;
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
        MinionComponent* temp = targetMinions[t - 1];
        Enchantment* newEnchantment = static_cast<Enchantment*>(c);
        newEnchantment->setNext(temp);
        targetMinions[t - 1] = newEnchantment;
        wasplaced = true;
    }

    if (wasplaced) {
        activePlayer->removeCard(i);
    }

    return wasplaced;
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

    // Minion* theMinion = new Minion{cur}; // copies over the contents of cur into a new minion.
    // this is because we want the return type to be a Minion*, not a MinionComponent*
    // JK FIX THIS. USE STATIC CASTING PLEASE FIX THIS FIX THIS FIX THIS FIX THIS

    Minion* theMinion = static_cast<Minion*>(cur);
    minions[minion - 1] = theMinion;
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

bool Board::useActivatedAbility(int i, int p, int t) {
    
    Player* activePlayer = getActivePlayer();

    if (activePlayerID == 1) {
        if (i < 1 || i > p1Minions.size()) {
            std::cerr << "no such card exists" << std::endl;
            return false;
        }
    }
    else {
        if (i < 1 || i > p2Minions.size()) {
            std::cerr << "no such card exists" << std::endl;
            return false;
        }
    }

    MinionComponent* theminion = (activePlayerID == player1->getID()) ? p1Minions[i - 1] : p2Minions[i - 1];
    std::string name = theminion->getName();
    // ^def has to be miniontype

    if (theminion->abilityNeedsTarget()) {
        if (((p != 1) && (p != 2)) || t < 1) {
            std::cerr << "must provide target for minion" << std::endl;
            return false;
        }
        
        MinionComponent* thetarget = (p == player1->getID()) ? p1Minions[i - 1] : p2Minions[i - 1];

        if (name == "Novice Pyromancer") {
            thetarget->beAttacked(1);
        }
        else std::cout << "bruga minion not picked properly" << std::endl;
        
        return true;
    }
    else {
        if (p != -1 || t != -1) {
            std::cerr << "not supposed to take in target" << std::endl;
            return false;
        }

        if (name == "Apprentice Summoner") {
            if (activePlayerID == 1) {
                if (p1Minions.size() >= 5) {
                    std::cout << "board full, not summoning air elemental" << std::endl;
                }
                else {
                    Minion* toAdd = Minion::makeAirElemental(activePlayerID);
                    addMinion(toAdd);
                }
            }
            else {
                if (p2Minions.size() >= 5) {
                    std::cout << "board full, not summoning air elemental" << std::endl;
                }
                else {
                    Minion* toAdd = Minion::makeAirElemental(activePlayerID);
                    addMinion(toAdd);
                }
            }
        }
        else if (name == "Master Summoner") {
            if (activePlayerID == 1) {
                for (int k = 0; k < 3; ++k) {
                    if (p1Minions.size() >= 5) {
                        std::cout << "board full, not summoning air elemental number " << k+1 << std::endl;
                    }
                    else {
                        Minion* toAdd = Minion::makeAirElemental(activePlayerID);
                        addMinion(toAdd);
                    }
                }
            }
            else {
                for (int k = 0; k < 3; ++k) {
                    if (p2Minions.size() >= 5) {
                        std::cout << "board full, not summoning air elemental number " << k+1 << std::endl;
                    }
                    else {
                        Minion* toAdd = Minion::makeAirElemental(activePlayerID);
                        addMinion(toAdd);
                    }
                }
            }
        }
        return true;
    }
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
