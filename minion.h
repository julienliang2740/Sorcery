#ifndef __MINION__
#define __MINION__

#include "minioncomponent.h"
#include "triggeredability.h"
#include "triggeredabilities.h"


class Minion: public MinionComponent {
    //friend class Spell;
    int attack;
    int defense;
    int totalDamage;
    int actions;
    actAbility aAbility;
    bool needsTarget;
    minionHasAbility abilityOfMinion;
    int abilityCost;
    triggeredAbility* tAbility;
    public:
        Minion(int cost, std::string name, int ownershipID, int attack, int defense, int totalDamage, int actions, actAbility aAbility, bool needsTarget, minionHasAbility abilityOfMinion, int abilityCost, std::string description);
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
        void resetDamage();
        void setDefense(int n);
        bool abilityNeedsTarget() const override;
        minionHasAbility getHasAbility() const override;
        int getAbilityCost() const override;
        int getNumActions() const override;
        std::string getMinionDescription() const override;
        void modDefense(int n) override;
        void modAttack(int n) override;
        void setActions(int n) override;
        void useActions(int n) override;
        int getMinionCost() const override;
        int getMinionID() const override;
        void setTriggeredAbility(triggeredAbility* t);
        triggeredAbility* getTriggeredAbility() const;
        void toggleAbilityOn() override;
        void toggleAbilityOff() override;
        Minion* getBaseMinion() const override;
};

#endif
