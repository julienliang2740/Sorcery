#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "board.h"

class Board;

enum class triggerType{ BeginTurn, EndTurn, MinionEnters, MinionLeaves, All };

class Observer {
    Board *b;
    triggerType subtype;
 public:
    Observer(Board* b, triggerType subtype);
    virtual void notify(int player, int whichCard) = 0;  // c is the Cell that called the notify method
    virtual triggerType subType() const;
    virtual ~Observer() = default;
};

#endif
