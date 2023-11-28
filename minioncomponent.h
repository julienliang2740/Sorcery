#ifndef __MINION_COMPONENT__
#define __MINION_COMPONENT__

#include "card.h"

enum class actAbility{ none, pyro, asumm, msumm };

class MinionComponent: public Card {
    protected:
        MinionComponent* next;
    public:
        class Iterator {
            MinionComponent* cur;
            Iterator( MinionComponent* cur);
            public:
                Iterator operator++();
                MinionComponent* operator*() const;
                bool operator!=(const Iterator& other) const;

                friend class MinionComponent;
        };

        Iterator begin() const;
        Iterator end() const;

        MinionComponent(int cost, std::string name, int ownershipID, cardtype cardType, std::string displayFile, bool hasTarget, MinionComponent* next);
        ~MinionComponent() override;
        MinionComponent* getNext() const;
        virtual int getDefense() const = 0;
        virtual int getAttack() const = 0;
        virtual int getTotalDamage() const = 0;
        virtual actAbility getActivatedAbility() const = 0;
        virtual void beAttacked(int n) = 0;
        virtual void attackMinion(MinionComponent* m) = 0;
        virtual std::string getMinionName() const = 0;

        // UNCOMMENT THESE WHEN YOU IMPLEMENT THEM
        // virtual int getNumActions() = 0;
        // virtual void doActivatedAbility() = 0;
        // virtual void attackPlayer() = 0;
        // virtual int getAbilityCost() = 0;
        // virtual bool attackMinion() = 0;
};

#endif