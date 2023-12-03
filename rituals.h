#ifndef __RITUALS__
#define __RITUALS__

#include "ritual.h"
#include <string>

class DarkRitual: public Ritual {
    public:
        DarkRitual(int ownerID, Board* b);
        void notify(int player, int whichCard) override;
};

class AuraOfPower: public Ritual {
    public:
        AuraOfPower(int ownerID, Board* b);
        void notify(int player, int whichCard) override;
};

class Standstill: public Ritual {
    public:
        Standstill(int ownerID, Board* b);
        void notify(int player, int whichCard) override;
};

#endif
