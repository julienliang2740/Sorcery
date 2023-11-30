#ifndef __ENCHANTMENT__
#define __ENCHANTMENT__

#include "minioncomponent.h"

class Enchantment: public MinionComponent {
    enchantmentHasStats hasStats;
    std::string abilityDescription;
    public:
        Enchantment(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next);
        ~Enchantment();
        int getDefense() const override;
        int getAttack() const override;
        int getTotalDamage() const override;
        void setNext(MinionComponent* next);
        std::string getMinionName() const override;
        actAbility getActivatedAbility() const override;
        void beAttacked(int n) override;
        void attackMinion(MinionComponent* m) override;
        bool abilityNeedsTarget() const override;
        minionHasAbility getHasAbility() const override;
        enchantmentHasStats getHasStats() const override;
        std::string getAbilityDesc() const;
};

#endif