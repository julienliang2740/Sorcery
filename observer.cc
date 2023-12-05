#include "observer.h"
#include "board.h"

class Board;

Observer::Observer(Board* b, triggerType t) : subtype(t), b(b) {}

triggerType Observer::subType() const {
    return subtype;
}

void Observer::setBoard(Board* gameBoard) {
    this->b = gameBoard;
}
