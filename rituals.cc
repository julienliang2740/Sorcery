#include "rituals.h"
#include "minion.h"
#include "board.h"

DarkRitual::DarkRitual(int ownerID, Board* b):
    Ritual{0, "Dark Ritual", ownerID, "At the start of your turn, gain 1 magic", b,
            triggerType::BeginTurn, 5, 1} {}


AuraOfPower::AuraOfPower(int ownerID, Board* b):
    Ritual{1, "Aura of Power", ownerID, "Whenever a minion enters play under your control, it gains +1/+1", b, 
            triggerType::MinionEnters, 4, 1} {}


Standstill::Standstill(int ownerID, Board* b):
    Ritual{3, "Standstill", ownerID, "Whenever a minion enters play, destroy it", b, 
            triggerType::MinionEnters, 4, 2} {
                std::cout << "onstate: " << this->getOnState();
            }
