#ifndef SHIP2_HPP
#define SHIP2_HPP
#include "movingobj.hpp"
#include "module.hpp"

class Ship: public MovingObj {
    public:
        Module* m1; Module* m2;
        double turn;
        sf::Keyboard::Key lkey,rkey,fwdkey,backkey;

        explicit Ship(State* _gm, double _x, double _y): MovingObj(_gm,x,y) {
            set_keys();
            specs();
        }
        virtual void specs() {
            speed=1.0;
            slow=1.02;
            grav=0.2;
            turn=0.2;
        }
        virtual void init() {
            //types stype;
            //stype = SHIP_TYPE;
            type = 2;
        }
        virtual Interactive* spawn() {
            return new Ship(gm,x,y);
        }
        virtual void move();
        virtual void set_keys();
        virtual void act();
        virtual void bump();

        /*void leavefac();*/
};
#endif
