#include "minioncomponent.h"

MinionComponent::MinionComponent(int cost, std::string name, int ownershipID, cardtype cardType, bool hasTarget, MinionComponent* next):
    Card{cost, name, ownershipID, cardType, hasTarget}, next{next} {}

MinionComponent::~MinionComponent() {}

MinionComponent* MinionComponent::getNext() const {
    return next;
}

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
    return Iterator{const_cast<MinionComponent*>(this)};
}

MinionComponent::Iterator MinionComponent::end() const {
    return Iterator{nullptr};
}
// the end is a dummy iterator, so the one before end is a minion ptr. Just check for that case
