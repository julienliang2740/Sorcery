#ifndef __ENCHANTMENT__
#define __ENCHANTMENT__

#include "minioncomponent.h"

class Enchantment: public MinionComponent {
    protected:
        MinionComponent* next;
    public:
        Enchantment(int cost, std::string name, int ownershipID std::string displayFile);
        ~Enchantment();
        int getDefense() const override;
        int getAttack() const override;
        int getTotalDamage() const override;
        void beAttacked(int n) override;
        void attackMinion(MinionComponent* m) = 0;
}

#endif