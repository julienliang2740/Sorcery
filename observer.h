#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "board.h"

enum class triggerType{ BeginTurn, EndTurn, MinionEnters, MinionLeaves, All };

class Observer {
    Board& b;
 public:
    Observer(Board& b);
    virtual void notify(int player, int whichCard) = 0;  // c is the Cell that called the notify method
    virtual triggerType subType() const = 0;
    virtual ~Observer() = default;
};

#endif
