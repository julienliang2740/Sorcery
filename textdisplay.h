#ifndef __TEXT_DISPLAY__
#define __TEXT_DISPLAY__

#include <string>
#include <iostream>
#include "ascii_graphics.h"
#include "board.h"

enum class triggerType{ BeginTurn, EndTurn, MinionEnters, MinionLeaves, All };

class textDisplay: public Observer {
    ostream& out;
    card_template_t ritual1 = CARD_TEMPLATE_BORDER;
    card_template_t ritual2 = CARD_TEMPLATE_BORDER;
    card_template_t player1 = PLAYER_1_TEMPLATE;
    card_template_t player2 = PLAYER_2_TEMPLATE;
    card_template_t p1minions[5] = {CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER};
    card_template_t p2minions[5] = {CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER};
    public:
        void printBoard();
        textDisplay(const Board& b, ostream& out);
        ~textDisplay();
        void notify(int player, int whichCard) override;
        void triggerType subType() const override;
        void 
}

#endif
