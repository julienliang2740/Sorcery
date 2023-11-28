#include <iostream>
#include <string>
#include <vector>
#include "spell.h"

Spell::Spell (int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile, bool hasTarget, Board* board) :  Card(cost, name, ownershipID, cardType, displayFile, hasTarget), theBoard(board) {}

void Spell::useMagic() {
    int cardCost = getCost();
    (ownershipID == 1) ? theBoard->player1->addMagic(-cardCost) : theBoard->player2->addMagic(-cardCost);
    std::cout << cardCost << " magic expended" << std::endl;
}

Spell::~Spell() {}

// Abilities for each card

void Blizzard::massAbility() {

}

void Banish::targetAbility(Card target) {
    // NOTHING TO DEAL WITH VIRTUAL YET!!!
    // (currently just moves minion to gravyard)
    
} 