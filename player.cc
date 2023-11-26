#include <iostream>
#include <string>
#include <vector>

#include "player.h"

Player::Player(std::string newname, int playerID, std::vector<Card> initalHand, Deck playerDeck, int initialMagic) : 
name(newname), 
playerID(playerID), 
hand(initalHand),
playerDeck(playerDeck),
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

int Player::getHandMax() {
    return handMax;
}
