#include "enchantments.h"

GiantStrength::GiantStrength(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next):
    Enchantment(cost, name, ownershipID, displayFile, next) {}

Enrage::Enrage(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next):
    Enchantment(cost, name, ownershipID, displayFile, next) {}

Haste::Haste(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next):
    Enchantment(cost, name, ownershipID, displayFile, next) {}

MagicFatigue::MagicFatigue(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next):
    Enchantment(cost, name, ownershipID, displayFile, next) {}

Silence::Silence(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next):
    Enchantment(cost, name, ownershipID, displayFile, next) {}

Enchantment* GiantStrength::makeGiantStrength(int ownerID) {
    return new GiantStrength(1, "Giant Strength", ownerID, "individual_cards/giantstrength.txt", nullptr);
}
