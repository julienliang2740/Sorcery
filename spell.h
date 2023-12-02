    #ifndef __SPELL__
#define __SPELL__
#include "card.h"
#include <string>

class Spell: public Card {
    public:
        Spell(int cost, std::string name, int ownershipID, bool hasTarget, std::string description) noexcept;
        static Spell* makeBanish(int ownershipID);
        static Spell* makeUnsummon(int ownershipID);
        static Spell* makeRecharge(int ownershipID);
        static Spell* makeDisenchant(int ownershipID);
        static Spell* makeRaiseDead(int ownershipID);
        static Spell* makeBlizzard(int ownershipID);
};

#endif
