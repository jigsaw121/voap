// defensive mods
// markov ships should also be in one file and include this
#ifndef MARKOV_HPP
#define MARKOV_HPP

#include "module.hpp"
#include "movingobj.hpp"

class Ship;

class TrailMod: public Module {
    // attributes changed depending on ship
    public:
        explicit TrailMod(Ship* s): Module(s) {}
        // main functionality acts, passive (always on?)
        virtual void act();
};

class Bullet: public MovingObj {
    // attributes changed depending on ship
    public:
        Ship* host;

		explicit Bullet(Ship* _host);
		virtual void typeinit3() {
            types.push_back(Typenum::BULLET);
            typeinit4();
        }
        virtual void typeinit4() {}

		virtual void die();

        void lifedelay(int);
};

class Trail: public Bullet {
    public:
        explicit Trail(Ship*);/*: MovingObj() {}*/
        virtual void dimsinit() { w=20; h=8; }
        virtual void act() {
			// hurt/bounce back moving objects that touch
			// behaviour can depend on enemy/own ship modules
		}
};

class TurretMod: public Module {
    // attributes changed depending on ship
    public:
        explicit TurretMod(Ship* s): Module(s) {}
        virtual void use();
        virtual void act() {}
};

// could be in a separate file later
class Turret: public MovingObj {
    public:
        explicit Turret(): MovingObj() {}

        // function pointers yay
        //void (*vact)(Turret* self);
        virtual void act() { //vact(this);
            // at any time, if it's blown up, it dies
            // better to destroy before it spawns

            // or even further, a state manager interface thingy with method pointers
            static int state = 0;
            switch(state) {
                case 0:
                    fall(&state); break;
                case 1:
                    build(&state); break;
                case 2:
                    // can't change state so doesn't take that argument
                    aim(); break;
            }
        }

        virtual void specs() {
            speed=1.0;
            slow=1.1;
            grav=0.2;
        }

        /*virtual void specinit() {
            dx=0.0; dy=0.0; angle=0.0;
            specs();
            vact = &fall;
        }*/
        void fall(int*);
        void build(int*);
        void aim();
};
// not very C++ though
// might do a switch-case state machine thingy for act() instead
// a turret falls first until it hits the ground
// (probably just bounces off of other objects)
// then it builds itself
//void fall(Turret* self);
//void build(Turret* self);
//void aim(Turret* self);
// ei ollukkaan huva tama

class MineLayer: public Weapon {
    // attributes changed depending on ship
    public:
        explicit MineLayer(Ship* s): Weapon(s) {}
        virtual void use();
        virtual void die_consequence();
};

class Explosive: public Bullet {
	public:
		explicit Explosive(Ship* _host): Bullet(_host) {}
		virtual void typeinit4() {
            types.push_back(Typenum::EXPLOSIVE);
            typeinit5();
        }
        virtual void typeinit5() {}
        virtual void explode() {
            // create a new explosion
            // if the explosion touches anything, they explode
            // for non-explosives, this means taking damage
        }
};
class Mine: public Explosive {
	public:
		explicit Mine(Ship* _host): Explosive(_host) {}
		virtual void typeinit5() {
            types.push_back(Typenum::MINE);
            typeinit6();
        }
        virtual void typeinit6() {}
        virtual void act() {
            // what could be an exception?
            // or in what cases would exceptions occur?
            if (collideone(Typenum::ANY)) {
                explode();
            }
        }
};

class Flamer: public Weapon {
    public:
        explicit Flamer(Ship* s): Weapon(s) {}
        virtual void use();
};

class Flame: public Bullet {
    public:
        explicit Flame(Ship* _host);
        virtual void specs() {
            speed=8.0;
            slow=1.1;
            grav=0.1;
        }
        virtual void dimsinit() { w=8; h=8; }
        virtual void act();
};

class Spy: public Module {
    public:
        explicit Spy(Ship* s): Module(s) {}
        virtual void act() {}
		virtual void use();
};

class Detonate: public Module {
    public:
        explicit Detonate(Ship* s): Module(s) {}
		// acting could count bullets? and display
        virtual void act() {}
		virtual void use();
};

#endif
