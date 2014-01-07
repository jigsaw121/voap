#ifndef UTILS_HPP
#define UTILS_HPP
#include "interactive.hpp"

class Engineer: public Interactive {
    public:
        explicit Engineer(): Interactive() {}
        virtual void typeinit2() {
            types.push_back(Typenum::ENGINEER);
            typeinit3();
        }
        virtual void typeinit3() {}

        virtual void draw() {}
};

class LifeDelay: public Engineer {
    public:
        Interactive* attach;
        int delay;

        explicit LifeDelay(/*int _delay, Interactive* _attach*/): Engineer() { /*delay=_delay; attach=_attach;*/ }

        void lifedelay(int _delay, Interactive* _attach) {
            delay=_delay; attach=_attach;
        }

        virtual void die() {
            remove();
            dying = true;
            attach->die();
        }
        virtual void act() {
            if (delay<=0) {
                die(); return;
            }
            delay--;
        }
};

#endif
