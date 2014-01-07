#ifndef LAYER2_H
#define LAYER2_H
#include "interactive.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Layer: public Interactive {
    public:
        Interactive* follow;
        std::string filename;
        double parallax;

        explicit Layer(std::string _filename="", double _parallax=1.0): Interactive() { filename = _filename; parallax = _parallax; }
        virtual void typeinit2() {
            types.push_back(Typenum::ENGINEER);
            typeinit3();
        }
        virtual void typeinit3() {}

        virtual void specinit() {
            //start_camerafollow(NULL);
        }
        virtual void imginit() {
            if (filename.empty()) return;
            texture.loadFromFile(filename);
            spr.setTexture(texture);
        }
        void start_camerafollow(Interactive*);
        virtual void camerafollow() {}
        virtual void act() {
            //camerafollow();
            //if (!follow) return;
            //std::cout<<x<<", "<<y<<" "<<follow->x<<", "<<follow->y<<"\n";
        }
};

class BGLayer: public Layer {
    public:
        BGLayer(/*State* _gm, double _x, double _y*/): Layer(/*_gm,_x,_y*/) {}
        virtual void imginit() {}
        virtual void draw() {
            screen()->clear(sf::Color(160,60,40));
        }
        virtual void act() {}
};

#endif
