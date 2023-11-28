#ifndef __TRIGGERED_ABILITY__
#define __TRIGGERED_ABILITY__

#include "observer.h"

class triggeredAbility: public Observer {
    Minion* self;
    public:
        triggeredAbility(Board* b, Minion* self) = default;
        void notify() override = 0;
        triggerType subType() const override = 0;
        ~triggeredAbility() override = default;
};

#endif
