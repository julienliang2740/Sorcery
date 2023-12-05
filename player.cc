#include <iostream>
#include <string>
#include <vector>

#include "player.h"

Player::Player(std::string newname, int playerID, std::vector<Card *> initalHand, Deck* playerDeck, int initialMagic) : 
name(newname), 
playerID(playerID), 
hand(initalHand),
magic(initialMagic), health(20),
playerDeck(playerDeck) {}

Player::~Player() {
    for (auto card: hand) {
        delete card;
    }
    delete playerDeck;
}

std::string Player::getName() const {
    return name;
}

void Player::assignName(std::string newname) {
    name = newname;
}

int Player::getID() const {
    return playerID;
}

std::vector<Card*> Player::getHand() const {
    return hand;
}

int Player::getMagic() const {
    return magic;
}

int Player::getHandMax() {
    return handMax;
}

int Player::getHealth() const {
    return health;
}

// frees the ith card in the player's hand.
void Player::freeCard(int i) {
    if (i < 1 || i > hand.size()) {
        return;
    } else {
        delete hand[i - 1];
    }
}

bool Player::removeCard(int i) {
    if (i < 1 || i > hand.size()) {
        return false;
    } else {
        hand.erase(hand.begin() + (i - 1));
        return true;
    }
}

bool Player::addCardToHand(Card* c) {
    if (hand.size() >= handMax) {
        std::cerr << "hand is full, cannot add card" << std::endl;
        return false;
    }

    hand.emplace_back(c);
    return true;
}

bool Player::drawCard() {
    if (playerDeck->isEmpty()) {
        std::cout << "Deck is empty. Cannot draw." << std::endl;
        return false;
    }
    else if (hand.size() == handMax) {
        std::cout << "Hand is full. Cannot draw." << std::endl;
        return false;
    }
    addCardToHand(playerDeck->draw());
    return true;
}

void Player::shuffle() {
    playerDeck->shuffle();
}

void Player::addMagic(int change) {
    magic += change;
}

void Player::addHealth(int change) {
    health += change;
}
