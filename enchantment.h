#ifndef __ENCHANTMENT__
#define __ENCHANTMENT__

#include "minioncomponent.h"

class Enchantment: public MinionComponent {
    bool hasStats;
    std::string abilityDescription;
    public:
        Enchantment(int cost, std::string name, int ownershipID, std::string displayFile, MinionComponent* next, bool hasStats, std::string abilityDescription);
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
        bool getHasStats() const;
        std::string getAbilityDesc() const;
};

#endif