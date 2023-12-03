#ifndef __RITUAL__
#define __RITUAL__

#include "card.h"
#include "observer.h"
#include <string>

class Ritual: public Card, public Observer {
    int charges;
    int activationCost;
    
    protected:
        bool onState;

    public:
        Ritual(int cost, std::string name, int ownershipID, std::string description, Board* b, triggerType subtype,
                int charges, int activationCost);
        ~Ritual();
        int getCharges() const;
        void addCharges(int n);
        int getActivationCost() const;
        bool getOnState() const;
        void toggleOff();
        void toggleOn();
        void setBoard(Board* b);
};

#endif
