#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "layer2.hpp"

class Camera: public Layer {
    public:
        explicit Camera(): Layer() {}

        virtual void dimsinit() { w = 640; h = 480; }
        virtual void imginit() {}

        virtual void draw() {}
        virtual void camerafollow();

        virtual sf::Vector2<float> offset() {
            sf::Vector2<float> cntr(-x+w/2,-y+h/2);
            return cntr;
        }

        virtual void act() {
            camerafollow();
        }
};
#endif
