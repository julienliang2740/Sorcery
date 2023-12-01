#include "observer.h"

Observer::Observer(Board& b, triggerType t) : b(b), subtype(t) {}

triggerType subType() const {
    return subtype;
}
