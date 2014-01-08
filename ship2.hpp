#ifndef SHIP2_HPP
#define SHIP2_HPP
#include "movingobj.hpp"
#include "types.hpp"

class Module;

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
			bulletquery = false;
        }
        virtual void typeinit3() {
            types.push_back(Typenum::SHIP);
            typeinit4();
        }
        virtual void typeinit4() {}

        virtual void specs();
        virtual void spawn();
        void set_keys();
        virtual void move();
        virtual void act();
        virtual void bump();
        virtual void mods();
        void collect();

		// if bullets have been requested before
		bool bulletquery;
		std::vector<Bullet*> hosted;
		std::vector<Bullet*> bullets();
        /*void leavefac();*/
};
#endif
