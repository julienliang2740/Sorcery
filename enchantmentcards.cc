#include <vector>
#include <string>

#include "enchantmentcards.h"

int GiantStrength::getDefense() const {
    return 2 + next->getDefense();
}

int GiantStrength::getAttack() const {
    return 2 + next->getAttack();
}

int Enrage::getDefense() const {
    return 2 * next->getDefense();
}

int Enrage::getAttack() const {
    return 2 * next->getAttack();
}
