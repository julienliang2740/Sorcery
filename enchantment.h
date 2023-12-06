#ifndef __ENCHANTMENT__
#define __ENCHANTMENT__

#include "minioncomponent.h"
#include "minion.h"

class Enchantment: public MinionComponent {
    bool hasStats;
    public:
        Enchantment(int cost, std::string name, int ownershipID, MinionComponent* next, bool hasStats, std::string description);
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
        int getAbilityCost() const override;
        int getNumActions() const override;
        std::string getMinionDescription() const override;
        void setActions(int n) override;
        void useActions(int n) override;
        int getMinionCost() const override;
        int getMinionID() const override;
        void modAttack(int n) override;
        void modDefense(int n) override;
        void toggleAbilityOn() override;
        void toggleAbilityOff() override;
        Minion* getBaseMinion() const override;
};

#endif
