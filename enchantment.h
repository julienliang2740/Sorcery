#ifndef __ENCHANTMENT__
#define __ENCHANTMENT__

#include "minioncomponent.h"

class Enchantment: public MinionComponent {
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
        void attackMinion(MinionComponent* m);
        bool abilityHasTarget() const;
};

#endif