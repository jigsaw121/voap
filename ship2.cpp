#include "ship2.hpp"
#include "state.hpp"
#include "markov.hpp"
#include "math.h"
#include <iostream>
//#include <SFML/Keyboard.hpp>

double rad(double n) {
    return n*180/3.14159;
}

void Ship::specs() {
    speed=0.3;
    slow=1.02;
    grav=0.1;
    turn=3.14159/45.0;
    modi = new Flamer(this);
    modi->initall(gm,x,y);
    cargo.push_back(new TurretMod(this));
    cargo.back()->initall(gm,x,y);
    set_keys();
}
void Ship::spawn()  {
    gm->add(new Ship(/*gm,x,y*/))->initall(gm,x,y);
}
void Ship::set_keys() {
    lkey = sf::Keyboard::Left;
    rkey = sf::Keyboard::Right;
    fwdkey = sf::Keyboard::Up;
    backkey = sf::Keyboard::Down;
    skey = sf::Keyboard::Z;
    ckey = sf::Keyboard::X;
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

    /*dx /= slow; dy /= slow;*/
    dy += grav;

    cap(&dx, -24, 24);
    cap(&dy, -24, 24);

    /*if (dx||dy) {
        std::cout<<dx<<" "<<dy<<" "<<turn<<" "<<angle<<"\n";
    }*/

    x += dx; y += dy;
}

void Ship::bump() {
    if (collideone(1) || collideone(2)) {
        x -= dx; y -= dy;
        dx/=1.1; dy/=1.1;
        // probably damage too
    }
}

void Ship::act() {
    move();
	mods();
    //bump();
}

void Ship::mods() {
	if (sf::Keyboard::isKeyPressed(skey)) modi->use();
	if (sf::Keyboard::isKeyPressed(ckey)) modi->swap(this);
}

void Ship::collect() {
	//Module m* = static_cast<Module>(collideone(MODULE_TYPE));
	Interactive* intr = collideone(Typenum::MODULE);
	// only implemented for module types anyway
	intr->collectme(this);
}

/*void Ship::leavefac() {
    if (up) {
        act = defact;
        act();
    }
}*/
