#ifndef __TRIGGERED_ABILITIES__
#define __TRIGGERED_ABILITIES__

#include "triggeredability.h"

class bgAbility: public triggeredAbility {
    public:
        bgAbility(Board* b, Minion* self);
        void notify(int player, int whichCard) override;
};

class feAbility: public triggeredAbility {
    public:
        feAbility(Board* b, Minion* self);
        void notify(int player, int whichCard) override;
};

class psAbility: public triggeredAbility {
    public:
        psAbility(Board* b, Minion* self);
        void notify(int player, int whichCard) override;
};

#endif
