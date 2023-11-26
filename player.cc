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

std::string Player::getName() const {
    return name;
}

void Player::assignName(std::string newname) const {
    name = newname;
}

int Player::getID() const {
    return playerID;
}

std::vector<Card> Player::getHand() const {
    return hand;
}

int Player::getMagic() const {
    return magic;
}

int Player::getHandMax() const {
    return handMax;
}

bool Player::removeCard(int i) {
    if (i < 1 || i > hand.size()) {
        return false;
    } else {
        hand.erase(hand.begin() + (i - 1));
        return true;
    }
}
