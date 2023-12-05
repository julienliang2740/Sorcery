#include "graphicsdisplay.h"

void graphicsDisplay::graphics_display_minion(int x, int y, int cardWidth, int cardHeight, MinionComponent* m) {
    if (m->getHasAbility() == minionHasAbility::hasnoability) {
        return theWindow->graphics_display_minion_no_ability(x, y, cardWidth, cardHeight, m->getMinionName(), m->getCost(), m->getAttack(), m->getDefense() - m->getTotalDamage());
    } else if (m->getHasAbility() == minionHasAbility::hasactivatedability) {
        return theWindow->graphics_display_minion_activated_ability(x, y, cardWidth, cardHeight, m->getMinionName(), m->getCost(), m->getAttack(), m->getDefense() - m->getTotalDamage(), m->getAbilityCost(), m->getMinionDescription());
    } else {
        return theWindow->graphics_display_minion_triggered_ability(x, y, cardWidth, cardHeight, m->getMinionName(), m->getCost(), m->getAttack(), m->getDefense() - m->getTotalDamage(), m->getMinionDescription());
    }
}

void graphicsDisplay::graphics_make_enchantment_card(int x, int y, int cardWidth, int cardHeight, Enchantment* e) {
    if (e->getName() == "Giant Strength") {
        return theWindow->graphics_display_enchantment_attack_defence(x, y, cardWidth, cardHeight, e->getName(), e->getCost(), e->getCardDescription(), "+2", "+2");
    } else if (e->getName() == "Enrage") {
        return theWindow->graphics_display_enchantment_attack_defence(x, y, cardWidth, cardHeight, e->getName(), e->getCost(), e->getCardDescription(), "*2", "*2");
    } else {
        return theWindow->graphics_display_enchantment(x, y, cardWidth, cardHeight, e->getName(), e->getCost(), e->getCardDescription());
    }
}

void graphicsDisplay::graphics_printHand(int x, int y, int cardWidth, int cardHeight, const Player& p) {
    theWindow->clearWindow();
    for (Card* c: p.getHand()) {
        if (c->getCardType() == cardtype::M) {
            Minion* m = static_cast<Minion*>(c);
            graphics_display_minion(x, y, cardWidth, cardHeight, m);
        } else if (c->getCardType() == cardtype::E) {
            graphics_make_enchantment_card(x, y, cardWidth, cardHeight, static_cast<Enchantment*>(c));
        } else if (c->getCardType() == cardtype::S) {
            theWindow->graphics_display_spell(x, y, cardWidth, cardHeight, c->getName(), c->getCost(), c->getCardDescription());
        } else if (c->getCardType() == cardtype::R) {
            Ritual* r = static_cast<Ritual*>(c);
            theWindow->graphics_display_ritual(x, y, cardWidth, cardHeight, r->getName(), r->getCost(), r->getActivationCost(), r->getCardDescription(), r->getCharges());
        }
        x = x + cardWidth + 3;
    }
}

void graphicsDisplay::graphics_inspectMinion(int x, int y, int cardWidth, int cardHeight, MinionComponent* minion) {
    theWindow->clearWindow();
    std::vector<Enchantment*> enchantments;

    for (MinionComponent::Iterator it = minion->begin(); it != minion->end(); ++it) {
        if ((*it)->getCardType() == cardtype:: M) {
            break;
        } else {
            enchantments.emplace_back(static_cast<Enchantment*>(*it));
        }
    }

    const int og_x = x;

    graphics_display_minion(x, y, cardWidth, cardHeight, minion);

    int row_cardscount = 1;
    x = x + cardWidth + 3;

    for (Enchantment* attachedenchantment : enchantments) {
        if (row_cardscount < 5) {
            graphics_make_enchantment_card(x, y, cardWidth, cardHeight, attachedenchantment);
            row_cardscount += 1;
            x = x + cardWidth + 3;
        }
        else {
            y = y + cardHeight + 3;
            x = og_x;
            graphics_make_enchantment_card(x, y, cardWidth, cardHeight, attachedenchantment);
            row_cardscount = 1;
        }
    }
}

graphicsDisplay::graphicsDisplay(Board* b, Xwindow* theWindow): b{b}, theWindow{theWindow} {
    // The code below was from textdisplay
    /*
    // setting player cards
    topRow[2] = display_player_card(1, b->player1->getName(), b->player1->getHealth(), b->player1->getMagic());
    bottomRow[2] = display_player_card(2, b->player2->getName(), b->player2->getHealth(), b->player2->getMagic());

    if (!b->p1Graveyard.empty()) {
        Minion* lastMinion = b->p1Graveyard[b->p1Graveyard.size() - 1];
        topRow[row_length - 1] = display_minion(lastMinion);
    }

    if (!b->p2Graveyard.empty()) {
        Minion* lastMinion = b->p1Graveyard[b->p1Graveyard.size() - 1];
        bottomRow[row_length - 1] = display_minion(lastMinion);
    }

    if (!b->p1Minions.empty()) {
        int i = 0;
        for (auto minion: b->p1Minions) {
            p1minions[i] = display_minion(minion);
            ++i;
        }
    }

    if (!b->p2Minions.empty()) {
        int i = 0;
        for (auto minion: b->p2Minions) {
            p2minions[i] = display_minion(minion);
            ++i;
        }
    }
    */
}

graphicsDisplay::~graphicsDisplay() {
    delete theWindow;
}

void graphicsDisplay::graphics_printBoard(int x, int y, int cardWidth, int cardHeight) {
    theWindow->clearWindow();
    theWindow->buildBoard(cardWidth, cardHeight, 3);
    const int og_x = x;
    const int og_y = y;

    // players
    theWindow->graphics_display_player_card(og_x+3*3+2*cardWidth, og_y+3, cardWidth, cardHeight, 1, b->player1->getName(), b->player1->getHealth(), b->player1->getMagic());
    theWindow->graphics_display_player_card(og_x+3*3+2*cardWidth, og_y+5*3+4*cardHeight, cardWidth, cardHeight, 2, b->player2->getName(), b->player2->getHealth(), b->player2->getMagic());

    // rituals
    if (b->p1Ritual != nullptr) theWindow->graphics_display_ritual(og_x+3, og_y+3, cardWidth, cardHeight, b->p1Ritual->getName(), b->p1Ritual->getCost(), b->p1Ritual->getActivationCost(), b->p1Ritual->getCardDescription(), b->p1Ritual->getCharges());
    if (b->p2Ritual != nullptr) theWindow->graphics_display_ritual(og_x+3, og_y+5*3+4*cardHeight, cardWidth, cardHeight, b->p2Ritual->getName(), b->p2Ritual->getCost(), b->p2Ritual->getActivationCost(), b->p2Ritual->getCardDescription(), b->p2Ritual->getCharges());
    
    // graveyard
    if (b->p1Graveyard.size() != 0) graphics_display_minion(og_x+5*3+4*cardWidth, og_y+3, cardWidth, cardHeight, b->p1Graveyard[b->p1Graveyard.size()-1]);
    if (b->p2Graveyard.size() != 0) graphics_display_minion(og_x+5*3+4*cardWidth, og_y+5*3+4*cardHeight, cardWidth, cardHeight, b->p2Graveyard[b->p2Graveyard.size()-1]);

    // minions
    for (int i = 0; i < b->p1Minions.size(); ++i) {
        graphics_display_minion(x+3, y+2*3+cardHeight, cardWidth, cardHeight, b->p1Minions[i]);
        x = x + 3 + cardWidth;
    }
    x = og_x;
    for (int i = 0; i < b->p2Minions.size(); ++i) {
        graphics_display_minion(x+3, y+4*3+3*cardHeight, cardWidth, cardHeight, b->p2Minions[i]);
        x = x + 3 + cardWidth;
    }

    // code below was from textdisplay
    /*
    std::cout << CENTRE_GRAPHIC[0] << std::endl;

    std::string rowLines[11] = {EXTERNAL_BORDER_CHAR_UP_DOWN, EXTERNAL_BORDER_CHAR_UP_DOWN, EXTERNAL_BORDER_CHAR_UP_DOWN, EXTERNAL_BORDER_CHAR_UP_DOWN, EXTERNAL_BORDER_CHAR_UP_DOWN,
                                EXTERNAL_BORDER_CHAR_UP_DOWN, EXTERNAL_BORDER_CHAR_UP_DOWN, EXTERNAL_BORDER_CHAR_UP_DOWN, EXTERNAL_BORDER_CHAR_UP_DOWN, EXTERNAL_BORDER_CHAR_UP_DOWN,
                                EXTERNAL_BORDER_CHAR_UP_DOWN};

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 11; ++j) {
            rowLines[j] += topRow[i][j];
            if (i == 4) rowLines[j] += EXTERNAL_BORDER_CHAR_UP_DOWN;
        }
    }

    for (int i = 0; i < 11; ++i) {
        std::cout << rowLines[i] << std::endl;
        rowLines[i] = EXTERNAL_BORDER_CHAR_UP_DOWN;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 11; ++j) {
            rowLines[j] += p1minions[i][j];
            if (i == 4) rowLines[j] += EXTERNAL_BORDER_CHAR_UP_DOWN;
        }
    }

    for (int i = 0; i < 11; ++i) {
        std::cout << rowLines[i] << std::endl;
        rowLines[i] = EXTERNAL_BORDER_CHAR_UP_DOWN;
    }

    // printRow(topRow);
    // printRow(p1minions);
    for (auto line: CENTRE_GRAPHIC) {
        std::cout << line << std::endl;
    }
    // printRow(p2minions);
    // printRow(bottomRow);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 11; ++j) {
            rowLines[j] += p2minions[i][j];
            if (i == 4) {
                rowLines[j] += EXTERNAL_BORDER_CHAR_UP_DOWN;
            }
        }
    }

    for (int i = 0; i < 11; ++i) {
        std::cout << rowLines[i] << std::endl;
        rowLines[i] = EXTERNAL_BORDER_CHAR_UP_DOWN;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 11; ++j) {
            rowLines[j] += bottomRow[i][j];
            if (i == 4) rowLines[j] += EXTERNAL_BORDER_CHAR_UP_DOWN;
        }
    }

    for (int i = 0; i < 11; ++i) {
        std::cout << rowLines[i] << std::endl;
    }

    std::cout << CENTRE_GRAPHIC[0] << std::endl;
    */
}

/*
void textDisplay::notify(int player, int whichCard) {

    // std::cout << "calling td notify" << std::endl;

    int ritualCard = 6;
    int playerCard = 7;
    int graveyardCard = 8;

    if (whichCard == ritualCard) {
        if (player == b->player1->getID()) {
            Ritual* r = b->p1Ritual;
            if (r == nullptr) {
                topRow[0] = CARD_TEMPLATE_BORDER;
            } else {
                topRow[0] = display_ritual(r->getName(), r->getCost(), r->getActivationCost(), r->getCardDescription(), r->getCharges());
            }
        } else if (player == b->player2->getID()) {
            Ritual* r = b->p2Ritual;
            if (r == nullptr) {
                bottomRow[0] = CARD_TEMPLATE_BORDER;
            } else {
                bottomRow[0] = display_ritual(r->getName(), r->getCost(), r->getActivationCost(), r->getCardDescription(), r->getCharges());
            }
        }
    } else if (whichCard == playerCard) {

        if (player == b->player1->getID()) {
            topRow[2] = display_player_card(b->player1->getID(), b->player1->getName(), b->player1->getMagic(), b->player1->getHealth());
        } else {
            bottomRow[2] = display_player_card(b->player2->getID(), b->player2->getName(), b->player2->getMagic(), b->player2->getHealth());
        }
        
    } else if (whichCard == graveyardCard) {

        std::vector<Minion*>& graveyard = (player == b->player1->getID()) ? b->p1Graveyard : b->p2Graveyard;

        if (graveyard.empty()) {
            if (player == b->player1->getID()) {
                topRow[4] = CARD_TEMPLATE_BORDER;
            } else {
                bottomRow[4] = CARD_TEMPLATE_EMPTY;
            }
        } else {
            Minion* m = graveyard[graveyard.size() - 1];
            if (player == b->player1->getID()) {
                topRow[4] = display_minion(m);
            } else {
                bottomRow[4] = display_minion(m);
            }
        }

    } else if (whichCard >= 1 && whichCard <= 5) {

        std::cout << "whichCard: " << whichCard << std::endl;

        int minionIndex = whichCard - 1;

        std::cout << "Minion Index: " << minionIndex << std::endl;

        std::vector<MinionComponent*>& minions = ((player == b->player1->getID()) ? b->p1Minions : b->p2Minions);

        card_template_t newcard;

        if (whichCard > minions.size()) {
            newcard = CARD_TEMPLATE_BORDER;
        } else {
            newcard = display_minion(minions[minionIndex]);
        }

        if (player == b->player1->getID()) {
            p1minions[minionIndex] = newcard;
        } else {
            p2minions[minionIndex] = newcard;
        }

        std::cout << "Modified td" << std::endl;

    }
}
*/

int graphicsDisplay::getRowLength() {
    return row_length;
}
