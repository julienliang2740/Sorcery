#include <iostream>
#include <string>
#include <vector>

#include "card.h"

Card::Card(int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile, bool hasTarget) : 
cost{cost},
name{name},
ownershipID{ownershipID},
cardType{cardType},
displayFile{displayFile},
hasTarget{hasTarget} {}

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

std::string Card::getFile() const {
    return displayFile;
}

bool Card::hasATarget() const {
    return hasTarget;
}

cardtype Card::getCardType() const {
    return cardType;
}
