#ifndef __GRAPHICS_DISPLAY__
#define __GRAPHICS_DISPLAY__

#include <string>
#include <iostream>
#include "window.h"
#include "minioncomponent.h"
#include "minion.h"
#include "enchantment.h"
#include "enchantments.h"
#include "spell.h"
#include "board.h"

//card_template_t display_minion(MinionComponent* m);


class graphicsDisplay{
    Board* b;
    Xwindow* theWindow;
    static const int row_length = 5;
    /*
    card_template_t topRow[5] = {CARD_TEMPLATE_BORDER, CARD_TEMPLATE_EMPTY, PLAYER_1_TEMPLATE, CARD_TEMPLATE_EMPTY, CARD_TEMPLATE_BORDER};
    card_template_t bottomRow[5] = {CARD_TEMPLATE_BORDER, CARD_TEMPLATE_EMPTY, PLAYER_2_TEMPLATE, CARD_TEMPLATE_EMPTY, CARD_TEMPLATE_BORDER};
    card_template_t p1minions[5] = {CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER};
    card_template_t p2minions[5] = {CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER, CARD_TEMPLATE_BORDER};
    */

    public:
        void graphics_display_minion(int x, int y, int cardWidth, int cardHeight, MinionComponent* m);
        void graphics_make_enchantment_card(int x, int y, int cardWidth, int cardHeight, Enchantment* e);

        void graphics_printHand(int x, int y, int cardWidth, int cardHeight, const Player& p);
        void graphics_inspectMinion(int x, int y, int cardWidth, int cardHeight, MinionComponent* minion);
        graphicsDisplay(Board* b, Xwindow* theWindow);
        ~graphicsDisplay();
        //void notify(int player, int whichCard) override;
        void graphics_printBoard(int x, int y, int cardWidth, int cardHeight);
        static int getRowLength();
};

#endif
