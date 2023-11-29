#ifndef __MINION__
#define __MINION__

#include "minioncomponent.h"

class Minion: public MinionComponent {
    //friend class Spell;
    int defense;
    int attack;
    int totalDamage;
    // int actions;
    actAbility aAbility;
    bool needsTarget;
    // triggeredAbility* tAbility; // or maybe a unique ptr if you don't wanna deal with memory management
    // int abilityCost;
    public:
        Minion(int cost, std::string name, int ownershipID, std::string displayFile, int defense, int attack, int totalDamage, actAbility aAbility, bool needsTarget);
        Minion(MinionComponent* other);
        ~Minion();
        int getDefense() const override;
        int getAttack() const override;
        int getTotalDamage() const override;
        std::string getMinionName() const override;
        actAbility getActivatedAbility() const override;
        void beAttacked(int n) override;
        void attackMinion(MinionComponent* other) override;
        static Minion* makeAirElemental(int ownershipID);
        static Minion* makeEarthElemental(int ownershipID);
        static Minion* makeFireElemental(int ownershipID);
        static Minion* makeBoneGolem(int ownershipID);
        static Minion* makeNovicePyromancer(int ownershipID);
        static Minion* makeAppSummoner(int ownershipID);
        static Minion* makeMsSummoner(int ownershipID);
        static Minion* makePotionSeller(int ownershipID);
        void reset();
        void setDefense(int n);
        bool abilityNeedsTarget() const override;
};

#endif
