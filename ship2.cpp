#include "ship2.hpp"
#include "math.h"
#include <iostream>
//#include <SFML/Keyboard.hpp>

double rad(double n) {
    return n*180/3.14159;
}

void Ship::set_keys() {
    lkey = sf::Keyboard::Left;
    rkey = sf::Keyboard::Right;
    fwdkey = sf::Keyboard::Up;
    backkey = sf::Keyboard::Down;
}
void Ship::move() {
    if (sf::Keyboard::isKeyPressed(lkey)) {
        angle -= turn;
    }
    if (sf::Keyboard::isKeyPressed(rkey)) {
        angle += turn;
    }
    spr.setRotation(rad(angle));

    if (sf::Keyboard::isKeyPressed(fwdkey)) {
        dx += cos(angle)*speed; dy += sin(angle)*speed;
    }
    if (sf::Keyboard::isKeyPressed(backkey)) {
        dx /= slow*2; dy /= slow*2;
    }

    /*dx /= slow;*/ dy /= slow;
    dy += grav;

    cap(&dx, -24, 24);
    cap(&dy, -24, 24);

    if (dx||dy) {
        std::cout<<dx<<" "<<dy<<" "<<turn<<" "<<angle<<"\n";
    }

    x += dx; y += dy;
}

void Ship::bump() {
    if (collideone(1) || collideone(2)) { x -= dx; y -= dy; }
}

void Ship::act() {
    move();
    //bump();
}

/*void Ship::leavefac() {
    if (up) {
        act = defact;
        act();
    }
}*/
