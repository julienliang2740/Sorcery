#include "triggeredabilities.h"

bgAbility::bgAbility(Board* b, Minion* self) : triggeredAbility{b, triggerType::MinionLeaves, self} {}

feAbility::feAbility(Board* b, Minion* self) : triggeredAbility{b, triggerType::MinionEnters, self} {}

psAbility::psAbility(Board* b, Minion* self) : triggeredAbility{b, triggerType::EndTurn, self} {}
