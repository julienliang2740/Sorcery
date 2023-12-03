#include "observer.h"
#include "board.h"

class Board;

Observer::Observer(Board& b, triggerType t) : b(b), subtype(t) {}

triggerType Observer::subType() const {
    return subtype;
}
