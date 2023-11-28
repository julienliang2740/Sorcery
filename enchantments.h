#ifndef __ENCHANTMENTS__
#define __ENCHANTMENTS__

#include <string>
#include "enchantment.h"

class GiantStrength: public Enchantment {
    public:
        GiantStrength(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next);
        Enchantment* makeGiantStrength(int ownerID);
        int getDefense() const override;
        int getAttack() const override;
};

class Enrage: public Enchantment {
    public:
        Enrage(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next);
        Enchantment* makeEnrage(int ownerID);
        int getDefense() const override;
        int getAttack() const override;
};

class Haste: public Enchantment {
    public:
        Haste(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next);
        Enchantment* makeHaste(int ownerID);
        // int getNumActions() const override; // uncomment when actions currency is implemented
};

class MagicFatigue: public Enchantment {
    public:
        MagicFatigue(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next);
        Enchantment* makeMagicFatigue(int ownerID);
        // int getAbilityCost() const override; // uncomment when ability currency is implemented
};

class Silence: public Enchantment {
    public:
        Silence(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next);
        Enchantment* makeSilence(int ownerID);
        actAbility getActivatedAbility() const override;
};

#endif
