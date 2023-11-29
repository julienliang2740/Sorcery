#ifndef __ENCHANTMENTS__
#define __ENCHANTMENTS__

#include <string>
#include "enchantment.h"

class GiantStrength: public Enchantment {
    public:
        GiantStrength(int ownerID);
        Enchantment* makeGiantStrength(int ownerID);
        int getDefense() const override;
        int getAttack() const override;
};

class Enrage: public Enchantment {
    public:
        Enrage(int ownerID);
        Enchantment* makeEnrage(int ownerID);
        int getDefense() const override;
        int getAttack() const override;
};

class Haste: public Enchantment {
    public:
        Haste(int ownerID);
        Enchantment* makeHaste(int ownerID);
        // int getNumActions() const override; // uncomment when actions currency is implemented
};

class MagicFatigue: public Enchantment {
    public:
        MagicFatigue(int ownerID);
        Enchantment* makeMagicFatigue(int ownerID);
        // int getAbilityCost() const override; // uncomment when ability currency is implemented
};

class Silence: public Enchantment {
    public:
        Silence(int ownerID);
        Enchantment* makeSilence(int ownerID);
        actAbility getActivatedAbility() const override;
};

#endif
