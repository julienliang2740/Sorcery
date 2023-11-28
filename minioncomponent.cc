#include "minioncomponent.h"

MinionComponent::MinionComponent(int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile, bool hasTarget, MinionComponent* next):
    Card{cost, name, ownershipID, cardType, displayFile, hasTarget}, next{next} {}

MinionComponent::~MinionComponent() {}

MinionComponent* MinionComponent::Iterator::operator*() const {
    return cur;
}

MinionComponent::Iterator::Iterator( MinionComponent* cur): cur{cur} {}

MinionComponent::Iterator MinionComponent::Iterator::operator++() {
    cur = cur->next;
}

bool MinionComponent::Iterator::operator!=(const MinionComponent::Iterator& other) const {
    return cur != other.cur;
}

MinionComponent::Iterator MinionComponent::begin() const {
    return Iterator{next};
} // uhhh this only begins at the next one, so when you loop through the enchantments make sure to
// do whatever to the first enchantment first. I know this is spaghetti code I'm sorry

MinionComponent::Iterator MinionComponent::end() const {
    return Iterator{nullptr};
}
// the end is a dummy iterator, so the one before end is a minion ptr. Just check for that case
