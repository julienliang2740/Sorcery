#include "observer.h"
#include "board.h"
#include "ritual.h"
#include "deck.h"

void Board::addObserver(Observer* o) {
    observers.emplace_back(o);
}

// a deck function to attach the board to each ritual.
void Deck::setBoardForRituals(Board* b) {
    for (Card* c: theDeck) {
        if (c->getCardType() == cardtype::R) {
            Ritual* r = static_cast<Ritual*>(c);
            r->setBoard(b);
            b->addObserver(r);
        }
    }
}

void DarkRitual::notify(int player, int whichCard) {

    if (!onState) {
        // card is not in play
        return;
    }

    if (player != this->ownershipID) {
        // do not modify the other player
        return;
    }

    if (player == 1) {
        b->player1->addMagic(1);
    } else {
        b->player2->addMagic(1);
    }

    int playerCard = 7;
    for (Observer* o: b->observers) {
        if (o->subType() == triggerType::All) {
            o->notify(player, playerCard);
        }
    }
}

void AuraOfPower::notify(int player, int whichCard) {
    if (player == ownershipID) {
        if (onState) {

            std::vector<MinionComponent*> ownMinions = (ownershipID == b->player1->getID()) ? b->p1Minions : b->p2Minions;

            // As the minion has just entered, it should not have enchantments.
            // As such we may static_cast this to a Minion*
            Minion* m = static_cast<Minion*>(ownMinions[whichCard - 1]);
            m->modDefense(1);
            m->modAttack(1);

        }

        for (Observer* o: b->observers) {
            if (o->subType() == triggerType::All) {
                o->notify(player, whichCard);
            }
        }
    }
}

// this helper function deletes the enchantments on a minion and returns a pointer to the base minion.
Minion* Board::deleteEnchantments(int ownershipID, int minion) {
    if (ownershipID != 1 && ownershipID != 2) {
        std::cerr << "invalid player ID" << std::endl;
        return nullptr;
    }

    std::vector<MinionComponent*>& minions = (ownershipID == player1->getID()) ? p1Minions : p2Minions;

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

    Minion* theMinion = static_cast<Minion*>(cur);
    minions[minion - 1] = theMinion;
    return theMinion;
}

void Board::destroyMinion(int player, int minion) {
    Minion * m = deleteEnchantments(player, minion);
    std::vector<MinionComponent*>& minions = (activePlayerID == player1->getID()) ? p1Minions : p2Minions;
    minions.erase(minions.begin() + (minion - 1));
    delete m;

    for (Observer* o: observers) {
        if (o->subType() == triggerType::All || o->subType() == triggerType::MinionLeaves) {
            o->notify(player, minion);
        }
    }
}

void Standstill::notify(int player, int whichCard) {
    if (!onState) {
        return;
    }
    b->destroyMinion(player, whichCard);
}

Board::Board(
    std::vector<MinionComponent*> p1Minions, std::vector<MinionComponent*> p2Minions, 
    Player* player1, Player* player2, 
    int activePlayerID,
    std::vector<Minion*> p1Graveyard, std::vector<Minion*> p2Graveyard) :

    p1Minions{p1Minions}, p2Minions{p2Minions},
    player1{player1}, player2{player2},
    activePlayerID{activePlayerID}, p1Ritual{nullptr}, p2Ritual{nullptr},
    p1Graveyard{p1Graveyard}, p2Graveyard{p2Graveyard} {}

Board::~Board() {
    int i = 1;
    for (MinionComponent* mc: p1Minions) {
        Minion* m = deleteEnchantments(player1->getID(), i++);
        delete m;
    }

    int j = 1;
    for (MinionComponent* mc: p2Minions) {
        Minion* m = deleteEnchantments(player2->getID(), j++);
        delete m;
    }

    for (Minion* m: p1Graveyard) {
        delete m;
    }

    for (Minion* m: p2Graveyard) {
        delete m;
    }

    delete p1Ritual;
    delete p2Ritual;
}

int Board::getActiveID() {
    return activePlayerID;
}

int Board::endTurn() {

    for (auto observer: observers) {
        if (observer->subType() == triggerType::EndTurn) {
            observer->notify(activePlayerID, 0);
        }
    }

    if (activePlayerID == player1->getID()) {
        activePlayerID = player2->getID();
    } else {
        activePlayerID = player1->getID();
    }

    for (auto observer: observers) {
        if (observer->subType() == triggerType::BeginTurn) {
            observer->notify(activePlayerID, 0);
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
        // checking to see if the minion ID provided is valid
        std::cerr << "invalid minion" << std::endl;
        return;
    }

    Player* victim = (activePlayer == player1) ? player2 : player1;

    victim->addHealth(-(ownMinions[minion - 1]->getAttack()));

    int playerCard = 7;
    for (auto p: observers) {
        if (p->subType() == triggerType::All) {
            p->notify(victim->getID(), playerCard);
        }
    }
}


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

    std::vector<MinionComponent*>& minions = (activePlayerID == player1->getID()) ? p1Minions : p2Minions;

    placed = placeMinion(minions, minion);

    if (placed) {
        for (auto observer: observers) {
            if (observer->subType() == triggerType::MinionEnters || observer->subType() == triggerType::All) {
                observer->notify(activePlayerID, minions.size());
            }
        }
    }

    return placed;
}

bool Board::destroyRitual(int playerID) {
    Ritual* toDestroy = (playerID == player1->getID()) ? p1Ritual : p2Ritual;

    if (toDestroy == nullptr) {
        return false;
        // no ritual to destroy, function does nothing
    }
                        
    // finding the index of the ritual in the board's observers
    int i = 0;
    for (Observer* o: observers) {
        if (o == toDestroy) {
            break;
        }
        ++i;
    }

    observers.erase(observers.begin() + i);

    if (playerID == player1->getID()) {
        p1Ritual = nullptr;
    } else {
        p2Ritual = nullptr;
    }

    for (Observer* o: observers) {
        if (o->subType() == triggerType::All) {
            o->notify(playerID, 6);
        }
    }

    delete toDestroy;
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

    cardtype type = c->getCardType();
    std::string name = c->getName();

    if (!(name == "Banish" && t == 6) && static_cast<int>(targetMinions.size()) < t) {
        std::cerr << "invalid target minion" << std::endl;
        return false;
    }

    bool wasplaced = false;

    if (type == cardtype::M) {
        std::cout << "placing a minion" << std::endl;
        Minion* newMinion = static_cast<Minion*>(c);
        wasplaced = addMinion(newMinion);
    } 

    else if (type == cardtype::S) {
        if (name == "Banish") {
            if (t < 6) {
                destroyMinion(p, t);
            } else if (t == 6) {
                wasplaced = destroyRitual(p);
            }
            if (wasplaced) delete c;
        }
        else if (name == "Unsummon") {
            Player* targetPlayer = (p == player1->getID()) ? player1 : player2;
            if ((targetPlayer != activePlayer) && (targetPlayer->getHand().size() >= Player::getHandMax())) {
                std::cerr << "cannot unsummon. Opponent's hand is full.";
                return false;
            }

            activePlayer->removeCard(i);
            Minion* m = deleteEnchantments(targetPlayer->getID(), t);
            targetMinions.erase(targetMinions.begin() + (t - 1));
            targetPlayer->addCardToHand(m);

            for (Observer* o: observers) {
                if (o->subType() == triggerType::All || o->subType() == triggerType::MinionLeaves) {
                    o->notify(targetPlayer->getID(), t);
                }
            }

            delete c;

            wasplaced = true;
        }
        else if (name == "Recharge") {
            if (c->getID() == player1->getID()) {
                if (p1Ritual) {
                    p1Ritual->addCharges(3);
                    wasplaced = true;
                } else {
                    std::cerr << "No ritual placed; cannot recharge" << std::endl;
                    return false;
                }
            } else {
                if (p2Ritual) {
                    p2Ritual->addCharges(3);
                    wasplaced = true;
                } else {
                    std::cerr << "No ritual placed; cannot recharge" << std::endl;
                    return false;
                }
            }
        }
        else if (name == "Disenchant") { //wip

            if (targetMinions[t - 1]->getCardType() != cardtype::E) {
                std::cerr << "minion is not enchanted - cannot disenchant" << std::endl;
                return false;
            }

            MinionComponent* temp = targetMinions[t - 1];
            targetMinions[t - 1] = (targetMinions[t - 1])->getNext();
            delete temp;
            for (auto observer: observers) {
                if (observer->subType() == triggerType::All) {
                    observer->notify(p, t);
                }
            }

            if (targetMinions[t - 1]->getDefense() - targetMinions[t - 1]->getTotalDamage() < 0) {
                moveMinionToGraveyard(p, t);
            }

            delete c;
            wasplaced = true;
        }
        else if (name == "Raise Dead") { //wip
            
            std::vector<MinionComponent*>& ownMinions = (c->getID() == player1->getID()) ? p1Minions : p2Minions;
            if (ownMinions.size() > 4) {
                std::cerr << "minions are at capacity. Cannot raise dead" << std::endl;
                return false;
            }

            std::vector<Minion*>& graveyard = (c->getID() == player1->getID()) ? p1Graveyard : p2Graveyard;
            if (graveyard.empty()) {
                std::cerr << "no minions in graveyard to revive" << std::endl;
                return false;
            }


            Minion* m = graveyard.back();
            m->setDefense(1);
            m->resetDamage();

            graveyard.pop_back();
            ownMinions.emplace_back(m);

            for (Observer* o: observers) {
                if (o->subType() == triggerType::All) {
                    o->notify(c->getID(), 8);
                }
            }

            for (Observer* o: observers) {
                if (o->subType() == triggerType::All || o->subType() == triggerType::MinionEnters) {
                    o->notify(c->getID(), ownMinions.size());
                }
            }

            delete c;
            wasplaced = true;
        }
        else if (name == "Blizzard") {

            int p1MinionPos = 1;
            int p2MinionPos = 1;

            for (MinionComponent* victim: p1Minions) {
                victim->beAttacked(2);
                for (Observer* o: observers) {
                    if (o->subType() == triggerType::All) {
                        o->notify(player1->getID(), p1MinionPos);
                    }
                }
                ++p1MinionPos;
            }

            for (MinionComponent* victim : p2Minions) {
                victim->beAttacked(2);
                for (Observer* o: observers) {
                    if (o->subType() == triggerType::All) {
                        o->notify(player2->getID(), p2MinionPos);
                    }
                }
                ++p2MinionPos;
            }

            int i = 0;
            while (i < p1Minions.size()) {
                if (p1Minions[i]->getDefense() - p1Minions[i]->getTotalDamage() < 0) {
                    moveMinionToGraveyard(player1->getID(), i + 1);
                } else {
                    ++i;
                }
            }

            i = 0;
            while (i < p2Minions.size()) {
                if (p2Minions[i]->getDefense() - p2Minions[i]->getTotalDamage() < 0) {
                    moveMinionToGraveyard(player2->getID(), i + 1);
                } else {
                    ++i;
                }
            }

            for (int j = 1; j < 6; ++j) {
                for (Observer* o: observers) {
                    if (o->subType() == triggerType::All) {
                        o->notify(player1->getID(), j);
                        o->notify(player2->getID(), j);
                    }
                }
            }
            
            delete c;

            wasplaced = true;
        }
    } 

    else if (type == cardtype::R) {
        Ritual* r = static_cast<Ritual*>(c);
        Ritual* oldRitual = nullptr;
        r->toggleOn();

        destroyRitual(activePlayerID);
        
        if (activePlayerID == player1->getID()) {
            p1Ritual = r;
        } else {
            p2Ritual = r;
        }

        int ritualCard = 6;

        for (Observer* o: observers) {
            if (o->subType() == triggerType::All) {
                o->notify(activePlayerID, ritualCard);
            }
        }

        wasplaced = true;
    }
    
    else if (type == cardtype::E) {
        // attaching the enchantment onto the target minion
        MinionComponent* temp = targetMinions[t - 1];
        Enchantment* newEnchantment = static_cast<Enchantment*>(c);
        newEnchantment->setNext(temp);
        targetMinions[t - 1] = newEnchantment;

        // notifying display observers that an enchantment was placed
        for (Observer* o: observers) {
            if (o->subType() == triggerType::All) {
                o->notify(p, t);
            }
        }
        wasplaced = true;
    }

    if (wasplaced) {
        activePlayer->removeCard(i);
    }

    return wasplaced;
}

bool Board::moveMinionToGraveyard(int ownershipID, int minion) {
    if (ownershipID != 1 && ownershipID != 2) {
        std::cerr << "invalid player ID" << std::endl;
        return false;
    }

    std::vector<MinionComponent*>& theMinions = (ownershipID == player1->getID()) ? p1Minions : p2Minions;
    std::vector<Minion*>& graveyard = (ownershipID == player1->getID()) ? p1Graveyard : p2Graveyard;

    if (minion > theMinions.size()) {
        std::cerr << "invalid minion ID. Cannot move to graveyard." << std::endl;
        return false;
    }

    Minion* m = deleteEnchantments(ownershipID, minion);
    theMinions.erase(theMinions.begin() + (minion - 1));
    for (auto observer: observers) {
        if (observer->subType() == triggerType::MinionLeaves || observer->subType() == triggerType::All) {
            observer->notify(m->getID(), minion);
        }
    }
    graveyard.emplace_back(m);
    for (auto observer: observers) {
        if (observer->subType() == triggerType::All) {
            observer->notify(m->getID(), 8);
        }
    }

    return true;
}

bool Board::useActivatedAbility(int i, int p, int t) {


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
    std::string name = theminion->getMinionName();
    // ^def has to be miniontype
    if (theminion->getActivatedAbility() == actAbility::silenced) {
        std::cerr << "activated ability is being silenced. It cannot be used." << std::endl;
        return false;
    } else if (theminion->getActivatedAbility() == actAbility::none) {
        std::cerr << "this minion has no activated ability." << std::endl;
        return false;
    }

    if (theminion->abilityNeedsTarget()) {
        if (((p != 1) && (p != 2)) || t < 1) {
            std::cerr << "must provide target for minion" << std::endl;
            return false;
        }
        
        MinionComponent* thetarget = (p == player1->getID()) ? p1Minions[t - 1] : p2Minions[t - 1];

        if (name == "Novice Pyromancer") {
            thetarget->beAttacked(1);
            for (Observer* o: observers) {
                if (o->subType() == triggerType::All) {
                    o->notify(p, t);
                }
            }
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
                        break;
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

    for (Observer* o: observers) {
        if (o->subType() == triggerType::All) {
            o->notify(attacker->getID(), curMinion);
        }
    }

    for (Observer* o: observers) {
        if (o->subType() == triggerType::All) {
            o->notify(attacked->getID(), target);
        }
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
