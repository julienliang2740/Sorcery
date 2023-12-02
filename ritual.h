#ifndef __RITUAL__
#define __RITUAL__

#include "card.h"
#include "observer.h"
#include <string>

class Ritual: public Card, public Observer {
    int charges;
    int activationCost;
    bool onState;

    public:
        Ritual(int cost, std::string name, int ownershipID, std::string description, Board* b, triggerType subtype,
                int charges, int activationCost);
        ~Ritual();
        int getCharges() const;
        int getActivationCost() const;
        bool getOnState() const;
        void toggleOff() const;
        void toggleOn() const;
};

#endif
