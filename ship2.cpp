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
    modi->initall(gm,x,y,team);
    //cargo.push_back(new TurretMod(this));
    //cargo.back()->initall(gm,x,y);
    cargo.push_back(new TrailMod(this));
    cargo.back()->initall(gm,x,y,team);
    set_keys();
}
void Ship::spawn()  {
    gm->add(new Ship(/*gm,x,y*/))->initall(gm,x,y,team);
}
void Ship::player_init(Player* p) {
	host = p;
}
/*void Ship::set_keys() {
    lkey = sf::Keyboard::Left;
    rkey = sf::Keyboard::Right;
    fwdkey = sf::Keyboard::Up;
    backkey = sf::Keyboard::Down;
    skey = sf::Keyboard::Z;
    ckey = sf::Keyboard::X;
}*/
void Ship::move() {
    if (sf::Keyboard::isKeyPressed(host->lkey)) {
        angle -= turn;
    }
    if (sf::Keyboard::isKeyPressed(host->rkey)) {
        angle += turn;
    }
    spr.setRotation(rad(angle));

    if (sf::Keyboard::isKeyPressed(host->fwdkey)) {
        dx += cos(angle)*speed; dy += sin(angle)*speed;
    }
    if (sf::Keyboard::isKeyPressed(host->backkey)) {
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
    if (modi==NULL) return;
    modi->act();
    // with two mods, the ckey just toggles a swap context
    // and whichever module you activate next gets swapped
    if (sf::Keyboard::isKeyPressed(host->skey)) modi->use();
    if (sf::Keyboard::isKeyPressed(host->ckey)) modi->swap(this);
}

void Ship::collect() {
    //Module m* = static_cast<Module>(collideone(MODULE_TYPE));
    Interactive* intr = collideone(Typenum::MODULE);
    // only implemented for module types anyway
    intr->collectme(this);
}

void Ship::hosted_init() {
    unsigned int i;
	for (i=0; i<gm->objects.size(); i++) {
		if (matchtype(gm->objects[i]->types, Typenum::BULLET)
			// screw it, I'll cast it for now - don't wanna change host's Ship* type
			&& static_cast<Bullet*>(gm->objects[i])->host==this) {
			hosted.push_back(static_cast<Bullet*>(gm->objects[i]));
		}
	}
}

std::vector<Bullet*> Ship::bullets() {
	// on the first time, load bullets by a search
	// after that, save bullets to vector 'hosted'
	// bullet death causes removal
	if (!bulletquery) {
		hosted_init();
		bulletquery = true;
	}
	return hosted;
}

/*void Ship::leavefac() {
    if (up) {
        act = defact;
        act();
    }
}*/

void Ship::resourcedrop() {
	if (modi!=NULL) gm->add(modi);
	// drop some minerals while you're at it
}

void Ship::die() {
	remove();
	dying = true;
	resourcedrop();
}
