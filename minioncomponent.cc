#include "minioncomponent.h"

MinionComponent::MinionComponent(int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile, bool hasTarget):
    Card{cost, name, ownershipID, cardType, displayFile, hasTarget} {}

MinionComponent::~MinionComponent() {}
