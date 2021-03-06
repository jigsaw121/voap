#ifndef MOVINGOBJ_HPP
#define MOVINGOBJ_HPP
#include "types.hpp"
#include "interactive.hpp"

class MovingObj: public Interactive {
    public:
        double dx,dy,angle,speed,slow,grav;

        explicit MovingObj(/*State* _gm, double _x, double _y*/): Interactive(/*_gm,_x,_y*/) {
            //specs();
        }
        virtual void typeinit2() {
            types.push_back(Typenum::MOVING);
            typeinit3();
        }
        virtual void typeinit3() {}

        virtual void specinit() {
            dx=0.0; dy=0.0; angle= -3.14159/2.0;
            specs();
        }
        virtual void specs() {
            speed=1.0;
            slow=1.1;
            grav=0.1;
        }
        virtual void genmove() { x += dx; y += dy; }
        virtual void move() {}
        virtual void push(double _dx, double _dy) { dx+=_dx; dy+=_dy; }
};
#endif
