#ifndef __RITUAL__
#define __RITUAL__

#include "card.h"
#include "observer.h"
#include <string>

class DarkRitual: public Ritual {
    public:
        DarkRitual(int ownerID, Board* b);
        void notify(int player, int whichCard) override;
}

class AuraOfPower: public Ritual {
    public:
        AuraOfPower(int ownerID);
        void notify(int player, int whichCard) override;
}

class Standstill: public Ritual {
    public:
        Standstill(int ownerID);
        void notify(int player, int whichCard) override;
}

#endif
