#ifndef SHIP2_HPP
#define SHIP2_HPP
#include "movingobj.hpp"
#include "module.hpp"
#include "types.hpp"

class Ship: public MovingObj {
    public:
        Module* modi; //Module* m2;
        double turn;
        sf::Keyboard::Key lkey,rkey,fwdkey,backkey,skey,ckey;
		// guess minerals inherit from Module too
		std::vector<Module*> cargo;

        explicit Ship(/*State* _gm, double _x, double _y*/): MovingObj(/*_gm,x,y*/) {
            //set_keys();
            //specs();
        }
		virtual void typeinit3() {
			types.push_back(Typenum::SHIP);
			typeinit4();
		}
		virtual void typeinit4() {}

		virtual void specs() {
			speed=0.3;
            slow=1.02;
            grav=0.1;
            turn=3.14159/45.0;
			set_keys();
        }
        virtual void spawn();
        void set_keys();
        virtual void move();
        virtual void act();
        virtual void bump();
        virtual void mods();
		void collect();

        /*void leavefac();*/
};
#endif
