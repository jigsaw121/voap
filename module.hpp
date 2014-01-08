#include "movingobj.hpp"

class Ship;

class Module: public MovingObj {
    // MovingObj because there'll be physical modules on ship drops
    // before that, they're not updated (and not added to gm)
    // alternatively, encapsulate them in a separate moving fragment...
    public:
        Ship* host;

        explicit Module(/*State* _gm, double _x, double _y,*/ Ship* _host): MovingObj(/*_gm,_x,_y*/) { host = _host; }
        virtual void typeinit3() {
            types.push_back(Typenum::MODULE);
            typeinit4();
        }
        virtual void typeinit4() {}

        virtual void move() {}
        // when a ship dies it calls this
        virtual void die_consequence() {}

        virtual void use() {}
        virtual void swap(Ship* s);
        virtual void act() {}
        virtual void draw() {
            // only drawn as a module image if not wielded/cargoed
            if (host==NULL) gendraw();
        }

        virtual void set_host(Ship*);
        virtual void collectme(Ship*);
};

class Weapon: public Module {
    public:
        int cooldown;
        explicit Weapon(Ship* _host): Module(_host) { cooldown=0; }
        virtual void typeinit4() {
            types.push_back(Typenum::WEAPON);
            typeinit5();
        }
        virtual void typeinit5() {}
};

class Mineral: public Module {
    public:
        int value;
        explicit Mineral(Ship* _host, int _value): Module(_host) { value=_value; }
        virtual void typeinit4() {
            types.push_back(Typenum::MINERAL);
            typeinit5();
        }
        virtual void typeinit5() {}
};
