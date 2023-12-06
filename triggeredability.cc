#include "triggeredability.h"

triggeredAbility::triggeredAbility(Board* b, triggerType trigger, Minion* self) :
    Observer{b, trigger}, self{self}, onState{false} {}

void triggeredAbility::toggleOff() {
    onState = false;
}

void triggeredAbility::toggleOn() {
    onState = true;
}
