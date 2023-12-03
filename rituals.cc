#include "rituals.h"
#include "minion.h"
#include "board.h"

DarkRitual::DarkRitual(int ownerID, Board* b):
    Ritual{0, "Dark Ritual", ownerID, "At the start of your turn, gain 1 magic", b,
            triggerType::BeginTurn, 5, 1} {}

void DarkRitual::notify(int player, int whichCard) {
    if (player == 1) {
        b->player1->addHealth(1);
    }
    else {
        b->player2->addHealth(1);
    }
}

AuraOfPower::AuraOfPower(int ownerID, Board* b):
    Ritual{1, "Aura of Power", ownerID, "Whenever a minion enters play under your control, it gains +1/+1", b, 
            triggerType::MinionEnters, 4, 1} {}

void AuraOfPower::notify(int player, int whichCard) {
    if (player == ownershipID) {
        if (onState) {
            if (ownershipID == b->player1->getID()) {
                Minion* m = static_cast<Minion*>(b->p1Minions[whichCard -1]); // "just trust me bro"
                m->modDefense(1);
                m->modAttack(1);
            } else {
                Minion* m = static_cast<Minion*>(b->p2Minions[whichCard - 1]);
                m->modDefense(1);
                m->modAttack(1);
            }
        }
    }
}

Standstill::Standstill(int ownerID, Board* b):
    Ritual{3, "Standstill", ownerID, "Whenever a minion enters play, destroy it", b, 
            triggerType::MinionEnters, 4, 2} {}

void Standstill::notify(int player, int whichCard) {
    b->destroyMinion(player, whichCard);
}