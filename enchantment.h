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
        std::string getMinionName() const override;
        void beAttacked(int n) override;
        void attackMinion(MinionComponent* m);
};

#endif