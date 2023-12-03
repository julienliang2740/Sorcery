#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Board;

enum class triggerType{ BeginTurn, EndTurn, MinionEnters, MinionLeaves, All };

class Observer {
    triggerType subtype;
 public:
    Board *b;
    Observer(Board* b, triggerType subtype);
    virtual void notify(int player, int whichCard) = 0;  // c is the Cell that called the notify method
    triggerType subType() const;
    virtual ~Observer() = default;
};

#endif
