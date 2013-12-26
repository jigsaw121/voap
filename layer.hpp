#ifndef LAYER_H
#define LAYER_H

#include "voap.hpp"

class VoaP;

class Layer {
    public:
        Layer() {}
        Layer(VoaP*);
        ~Layer() {}

        VoaP* voap;
        bool active;

        virtual sf::Sprite* surface() { return NULL; };
        virtual void act() {};
        virtual void nudge(double, double) {};
};

class BGLayer: public Layer {
    public:
        BGLayer(VoaP*, int, int, int);
        ~BGLayer() {}

        VoaP* voap;
        sf::Color* color;

        void act();
        void draw();
};

class ParallaxLayer: public Layer {
    double rx; double ry;
    public:
        ParallaxLayer(VoaP*, std::string, bool, double, double);
        ~ParallaxLayer() {}

        VoaP* voap;
        sf::Image img;
        sf::Sprite spr;

        void act();
        void draw();
        sf::Sprite* surface() { return &spr; };
        void nudge(double, double);
};

#endif
