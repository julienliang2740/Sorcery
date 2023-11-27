#ifndef __MINION_COMPONENT__
#define __MINION_COMPONENT__

#include "card.h"

class MinionComponent: public Card {
    public:
        MinionComponent(int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile, bool hasTarget);
        ~MinionComponent();
        virtual int getDefense() const = 0;
        virtual int getAttack() const = 0;
        virtual int getTotalDamage() const = 0;
        virtual void beAttacked(int n) = 0;
        virtual void attackMinion(MinionComponent* m) = 0;

        // UNCOMMENT THESE WHEN YOU IMPLEMENT THEM
        // virtual int getNumActions() = 0;
        // virtual void doActivatedAbility() = 0;
        // virtual void attackPlayer() = 0;
        // virtual int getAbilityCost() = 0;
        // virtual bool attackMinion() = 0;
};

#endif
