#ifndef MINERAL_H
#define MINERAL_H

#include "voap.hpp"

class VoaP;

class Mineral {
    public:
        int value;
        double x,y;
        VoaP* voap;

        Mineral(VoaP*, double, double, int);
        void wane();
        bool alive();
        bool collected();
        void draw();

        sf::Image img;
        sf::Sprite spr;
};

#endif
