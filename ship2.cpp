#include "ship2.hpp"
#include "math.h"
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
    if (lkey) {
        angle -= turn;
        spr.rotate(rad(turn));
    }
    if (rkey) {
        angle += turn;
        spr.rotate(-rad(turn));
    }

    if (fwdkey) {
        dx += cos(angle)*speed; dy += sin(angle)*speed;
    }
    if (backkey) {
        dx /= slow*2; dy /= slow*2;
    }

    dx /= slow; dy /= slow;
    dy += grav;

    x += dx; y += dy;
}

void Ship::bump() {
    if (collideone(1) || collideone(2)) { x -= dx; y -= dy; }
}

void Ship::act() {
    move();
    bump();
}

/*void Ship::leavefac() {
    if (up) {
        act = defact;
        act();
    }
}*/
