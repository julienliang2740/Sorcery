#ifndef __TRIGGERED_ABILITIES__
#define __TRIGGERED_ABILITIES__

class bgAbility: public triggeredAbility {
    public:
        void notify() override;
};

class feAbility: public triggeredAbility {
    public:
        void notify() override;
};

class psAbility: public triggeredAbility {
    public:
        void notify() override;
};
