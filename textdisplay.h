#ifndef __TEXT_DISPLAY__
#define __TEXT_DISPLAY__

#include <string>
#include <iostream>
#include "ascii_graphics.h"
#include "minioncomponent.h"
#include "minion.h"
#include "enchantment.h"
#include "enchantments.h"
#include "spell.h"
#include "board.h"
#include "observer.h"

class textDisplay: public Observer {
    static const int row_length = 5;
    card_template_t topRow[5] = {CARD_TEMPLATE_BORDER, CARD_TEMPLATE_EMPTY, PLAYER_1_TEMPLATE, CARD_TEMPLATE_EMPTY, CARD_TEMPLATE_BORDER};
    card_template_t bottomRow[5] = {CARD_TEMPLATE_BORDER, CARD_TEMPLATE_EMPTY, PLAYER_2_TEMPLATE, CARD_TEMPLATE_EMPTY, CARD_TEMPLATE_BORDER};
    card_template_t p1minions[5] = {CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER};
    card_template_t p2minions[5] = {CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER};
    public:
        textDisplay(Board* b);
        ~textDisplay();
        void notify(int player, int whichCard) override;
        void printBoard() const;
        static int getRowLength();
        // minion inspecting will just happen in main. so that this object doesn't take as much memory
};

#endif
