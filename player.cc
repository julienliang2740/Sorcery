#include <iostream>
#include <string>
#include <vector>

#include "player.h"

Player::Player(std::string newname, int playerID, std::vector<Card> initalHand, int initialMagic) : 
name(newname), 
playerID(playerID), 
hand(initalHand),
magic(initialMagic) {}

std::string Player::getName() {
    return name;
}

void Player::assignName(std::string newname) {
    name = newname;
}

int Player::getID() {
    return playerID;
}

std::vector<Card> Player::getHand() {
    return hand;
}

int Player::getMagic() {
    return magic;
}

int Player::getDeckMax() {
    return deckMax;
}
