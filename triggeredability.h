#ifndef __TRIGGERED_ABILITY__
#define __TRIGGERED_ABILITY__

#include "observer.h"

class Minion;
class Board;

class triggeredAbility: public Observer {
    protected:
    Minion* self;
    bool onState;
    public:
        triggeredAbility(Board* b, triggerType trigger, Minion* self);
        void notify(int player, int whichCard) = 0;
        void toggleOff();
        void toggleOn();
};

#endif
