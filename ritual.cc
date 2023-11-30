#include "ritual.h"

Ritual::Ritual(int cost, std::string name, int ownershipID, std::string description, Board& b,
               triggerType subtype, int charges, int activationCost):
    Card{cost, name, ownershipID, cardtype::R, false, description}, Observer{b}, 
    charges{charges}, activationCost{activationCost}, onState{false} {}

Ritual::~Ritual() {}

int Ritual::getCharges() const {
    return charges;
}

int Ritual::getActivationCost() const {
    return activationCost;
}

bool Ritual::getOnState() const {
    return onState;
}

void Ritual::toggleOff() {
    onState = false;
}

void Ritual::toggleOn() {
    onState = true;
}

void 
