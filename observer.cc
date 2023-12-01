#include "observer.h"

Observer::Observer(Board& b, triggerType t) : b(b), subtype(t) {}

triggerType Observer::subType() const {
    return subtype;
}
