#include "textdisplay.h"

card_template_t display_minion(MinionComponent* m) {
    if (m->getHasAbility() == minionHasAbility::hasnoability) {
        return display_minion_no_ability(m->getMinionName(), m->getCost(), m->getAttack(), m->getDefense());
    } else if (m->getHasAbility() == minionHasAbility::hasactivatedability) {
        return display_minion_activated_ability(m->getMinionName(), m->getCost(), m->getAttack(), m->getDefense(), m->getAbilityCost(), m->getAbilityDesc());
    } else {
        return display_minion_triggered_ability(m->getMinionName(), m->getCost(), m->getAttack(), m->getDefense(), m->getAbilityDesc());
    }
}

textDisplay::textDisplay(const Board& b): Observer{b, triggerType::All} {
    // setting player cards
    topRow[2] = display_player_card(1, b.player1->getName(), b.player1->getHealth(), b.player1->getMagic());
    bottomRow[2] = display_player_card(2, b.player2->getName(), b.player2->getHealth(), b.player2->getMagic());

    // setting rituals. Will be done later

    if (!b.p1Graveyard.empty()) {
        Minion* lastMinion = b.p1Graveyard[p1Graveyard.size() - 1];
        topRow[row_length - 1] = display_minion(lastMinion);
    }

    if (!b.p2Graveyard.empty()) {
        Minion* lastMinion = p1Graveyard[p1Graveyard.size() - 1];
        bottomRow[row_length - 1] = display_minion(lastMinion);
    }

    if (!b.p1Minions.empty()) {
        int i = 0;
        for (auto minion: b.p1Minions) {
            p1minions[i] = display_minion(minion);
            ++i;
        }
    }

    if (!b.p2Minions.empty()) {
        int i = 0;
        for (auto minion: b.p2Minions) {
            p2minions[i] = display_minion(minion);
            ++i;
        }
    }
}

textDisplay::~textDisplay() {}

void printRow(card_template_t (row&)[5]) {

    std::string rowLines[11];

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 11; ++j) {
            rowLines[j] += row[i][j];
        }
    }

    for (int i = 0; i < 11; ++i) {
        std::cout << rowLines[i] << std::endl;
    }
}

void textDisplay::printBoard() const {

    std::cout << CENTRE_GRAPHIC[0] << std::endl;

    printRow(topRow);
    printRow(p1minions);
    for (auto line: CENTRE_GRAPHIC) {
        std::cout << line << std::endl;
    }
    printRow(p2minions);
    printRow(bottomRow);

    std::cout << CENTRE_GRAPHIC[0] << std::endl;

    /*
    std::string rowLines[11];
    for (int i = 0; i < row_length; ++i) {
        for (int j = 0; j < 11; ++j) {
            rowLines[j] += topRow[i][j];
        }
    }

    for (int i = 0; i < 11; ++i) {
        out << rowLines[i] << endl;
        rowLines[i] = "";
    }

    for (int i = 0; i < row_length; ++i) {
        for (int j = 0; j < 11; ++j) {
            rowLines[j] += p1minions[i][j];
        }
    }

    for (int i = 0; i < 11; ++i) {
        out << rowLines[i] << endl;
        rowLines[i] = "";
    }

    for (int i = 0; i < row_length; ++i) {
        for (int j = 0; j < 11; ++j) {
            rowLines[j] += p2minions[i][j];
        }
    }

    for (int i = 0; i < 11; ++i) {
        out << rowLines[i] << endl;
        rowLines[i] = "";
    }

    for (auto line: CENTRE_GRAPHIC) {
        out << line << endl;
    }

    for (int i = 0; i < row_length; ++i) {
        for (int j = 0; j < 11; ++j) {
            rowLines[j] += bottomRow[i][j];
        }
    }

    for (int i = 0; i < 11; ++i) {
        out << rowLines[i] << endl;
    }
    */
}

void textDisplay::notify(int player, int whichCard) {

    int ritualCard = 6;
    int playerCard = 7;
    int graveyardCard = 8;

    if (whichCard == ritualCard) {
        // stuff
    } else if (whichCard == playerCard) {

        if (player == b.player1->getID()) {
            topRow[2] = display_player_card(b.player1->getID(), b.player1->getName(), b.player1->getMagic(), b.player1->getHealth());
        } else {
            bottomRow[2] = display_player_card(b.player2->getID(), b.player2->getName(), b.player2->getMagic(), b.player2->getHealth());
        }
        
    } else if (whichCard == graveyardCard) {

        vector<Minion*>& graveyard = (player == b.player1->getID()) ? b.p1Graveyard : b.p2Graveyard;

        if (graveyard.empty) {
            if (player == b.player1->getID()) {
                topRow[4] = CARD_TEMPLATE_EMPTY;
            } else {
                bottomRow[4] = CARD_TEMPLATE_EMPTY;
            }
        } else {
            Minion* m = graveyard[graveyard.size() - 1];
            if (player == b.player1->getID()) {
                topRow[4] = display_minion(m);
            } else {
                bottomRow[4] = display_minion(m);
            }
        }

    } else {

        int minionIndex = whichCard - 1;
        vector<MinionComponent*>& minions = ((player == b.player1->getID()) ? b.p1Minions : b.p2Minions);
        card_template_t newcard = display_minion(minions[minionIndex]);

        if (player == b.player1.getID()) {
            p1minions[minionIndex] = newcard;
        } else {
            p2minions[minionIndex] = newcard;
        }

    }
}

int textDisplay::getRowLength() {
    return row_length;
}
