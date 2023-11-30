#include <iostream>
#include <string>
#include <vector>

#include "card.h"

Card::Card(int cost, std::string name, int ownershipID, cardtype cardType, bool hasTarget, std::string description) : 
cost{cost},
name{name},
ownershipID{ownershipID},
cardType{cardType},
hasTarget{hasTarget},
description{description} {}

Card::~Card() {}

int Card::getCost() const {
    return cost;
}

std::string Card::getName() const {
    return name;
}

int Card::getID() const {
    return ownershipID;
}

cardtype Card::getType() const {
    return cardType;
}

bool Card::hasATarget() const {
    return hasTarget;
}

cardtype Card::getCardType() const {
    return cardType;
}

std::string Card::getCardDescription() const {
    return description;
}
