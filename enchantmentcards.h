#ifndef __ENCHANTMENTCARDS__
#define __ENCHANTMENTCARDS__

#include "enchantment.h"

class GiantStrength : public Enchantment {
    public:
        int getDefense() const override;
        int getAttack() const override;
};

class Enrage : public Enchantment {
    public:
        int getDefense() const override;
        int getAttack() const override;
};

class Haste : public Enchantment {};

class MagicFatigue : public Enchantment {};

class Silence : public Enchantment {};

#endif
