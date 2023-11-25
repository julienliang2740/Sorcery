#include <iostream>
#include <string>
#include <vector>

#include "card.h"

Card::Card(int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile) : 
cost(cost),
name(name),
ownershipID(ownershipID),
cardType(cardType),
displayFile(displayFile) {}

int Card::getCost() {
    return cost;
}

std::string Card::getName() {
    return name;
}

int Card::getID() {
    return ownershipID;
}

cardtype Card::getType() {
    return cardType;
}

std::string Card::getFile() {
    return displayFile;
}
