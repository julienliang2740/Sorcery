#include "textdisplay.h"

card_template_t display_minion(MinionComponent* m) {
    if (m->getHasAbility() == minionHasAbility::hasnoability) {
        return display_minion_no_ability(m->getMinionName(), m->getMinionCost(), m->getAttack(), m->getDefense() - m->getTotalDamage());
    } else if (m->getHasAbility() == minionHasAbility::hasactivatedability) {
        return display_minion_activated_ability(m->getMinionName(), m->getMinionCost(), m->getAttack(), m->getDefense() - m->getTotalDamage(), m->getAbilityCost(), m->getMinionDescription());
    } else {
        return display_minion_triggered_ability(m->getMinionName(), m->getMinionCost(), m->getAttack(), m->getDefense() - m->getTotalDamage(), m->getMinionDescription());
    }
}

card_template_t make_enchantment_card(Enchantment* e) {
    if (e->getName() == "Giant Strength") {
        return display_enchantment_attack_defence(e->getName(), e->getCost(), e->getCardDescription(), "+2", "+2");
    } else if (e->getName() == "Enrage") {
        return display_enchantment_attack_defence(e->getName(), e->getCost(), e->getCardDescription(), "*2", "*2");
    } else {
        return display_enchantment(e->getName(), e->getCost(), e->getCardDescription());
    }
}

void printHand(const Player& p) {
    std::string rowLines[11];

    for (Card* c: p.getHand()) {

        card_template_t displayCard;
        if (c->getCardType() == cardtype::M) {
            Minion* m = static_cast<Minion*>(c);
            displayCard = display_minion(m);
        } else if (c->getCardType() == cardtype::E) {
            displayCard = make_enchantment_card(static_cast<Enchantment*>(c));
        } else if (c->getCardType() == cardtype::S) {
            displayCard = display_spell(c->getName(), c->getCost(), c->getCardDescription());
        } else if (c->getCardType() == cardtype::R) {
            Ritual* r = static_cast<Ritual*>(c);
            displayCard = display_ritual(r->getName(), r->getCost(), r->getActivationCost(), r->getCardDescription(), r->getCharges());
        }

        for (int i = 0; i < 11; ++i) {
            rowLines[i] += displayCard[i];
        }
    }

    for (int i = 0; i < 11; ++i) {
        std::cout << rowLines[i] << std::endl;
    }
}

void inspectMinion(MinionComponent* minion) {
    std::string rowLines[11];
    std::vector<Enchantment*> enchantments;

    for (MinionComponent::Iterator it = minion->begin(); it != minion->end(); ++it) {
        if ((*it)->getCardType() == cardtype:: M) {
            break;
        } else {
            enchantments.emplace_back(static_cast<Enchantment*>(*it));
        }
    }

    card_template_t theMinion = display_minion(minion);
    for (std::string line: theMinion) {
        std::cout << line << std::endl;
    }

    int enchantmentCount = 0;
    for (std::vector<Enchantment*>::reverse_iterator it = enchantments.rbegin(); it != enchantments.rend(); ++it) {

        if (enchantmentCount == 5) {
            for (int i = 0; i < 11; ++i) {
                std::cout << rowLines[i] << std::endl;
                rowLines[i] = "";
            }
            enchantmentCount = 0;
        }

        card_template_t enchantmentCard = make_enchantment_card(*it);
        for (int i = 0; i < 11; ++i) {
            rowLines[i] += enchantmentCard[i];
        }

        ++enchantmentCount;
    }

    if (rowLines[0] != "") {
        for (int i = 0; i < 11; ++i) {
            std::cout << rowLines[i] << std::endl;
        }
    }
}

textDisplay::textDisplay(Board* b): Observer{b, triggerType::All} {
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
}

textDisplay::~textDisplay() {}

/*
void printRow(card_template_t row[]) {

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
*/

void textDisplay::printBoard() const {

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

}

void textDisplay::notify(int player, int whichCard) {

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

        int minionIndex = whichCard - 1;

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

    }
}

int textDisplay::getRowLength() {
    return row_length;
}
