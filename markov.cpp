#include "markov.hpp"
#include "types.hpp"
#include "ship2.hpp"
#include "state.hpp"
#include "utils.hpp"
#include <math.h>

void TrailMod::act() {
    // module follows ship, constantly spawns trail atoms that block/hurt
    // trails disappear after a while
    // can be toggled on/off to save power

    //gm->add(/* new trail of the current type at this pos */)->initall(gm,x,y);
    Trail* t = new Trail();
    gm->add(t);
    t->initall(gm,host->x,host->y);
    t->lifedelay(200);
}

Trail::Trail(): Bullet() {
    /*LifeDelay* l = new LifeDelay();
    gm->add(l);
    l->initall(gm,x,y);
    l->lifedelay(200, this);*/
}

void Bullet::lifedelay(int delay) {
    LifeDelay* l = new LifeDelay();
    gm->add(l);
    l->initall(gm,x,y);
    l->lifedelay(delay, this);
}

void TurretMod::use() {
    // drop a turret base that'll build itself once it hits the ground
    // turret building can be accelerated with slow turrets
    // and they can be repaired later
    // (there are different types that inherit from this)
    Turret* t = new Turret();
    gm->add(t);
    t->initall(gm,host->x,host->y);
    t->push(host->dx,host->dy);
}

void Turret::fall(int* state) {
    /*if (collideone(Typenum::MOVING)) {
        // bounce back!
        // enemies might juggle turret seeds to block them, and other emergent behaviour
        x -= dx; y -= dy;
        dx = -dx/1.1; dy = -dy/1.1;
    }*/
    /*if (collideone(Typenum::WALL)) {
        // should I have a swapstate() for all Interactives?
        //vact = &build;
        *state = 1;
        return;
    }*/
    x += dx;
    y += dy;
    dy += grav;
}

void Turret::build(int* state) {
    static int growth = 0;
    if (growth>=70) {
        //vact = &aim;
        *state = 2;
        return;
    }
    growth++;
}

void Turret::aim() {
    // lol pseudocode

    //Interactive* close = closestenemy(range);
    //if (close) shootat(close);
}

void MineLayer::die_consequence() {
    std::vector<Interactive*> mines = find(Typenum::MINE);
    // any that belong to this blow up on host death
    // unless another mod blocks it

    //unsigned int i;
    //for (i=0;i<mines.size();i++) {
    //    if (mines[i]->host==this) mines[i]->explode();
    //}
}

void MineLayer::use() {
    // drop a turret base that'll build itself once it hits the ground
    // turret building can be accelerated with slow turrets
    // and they can be repaired later
    // (there are different types that inherit from this)

    //gm->add(/* new Mine() */)->initall(gm,x,y);
}

void Flamer::use() {
    Flame* f = new Flame();
    gm->add(f);
    f->initall(gm,host->x,host->y);
    f->push(cos(host->angle+(std::rand()%20)/60.0)*8.0+host->dx,
            sin(host->angle+(std::rand()%20)/60.0)*8.0+host->dy);
    f->lifedelay(200);
}

Flame::Flame(): Bullet() {
    /*LifeDelay* l = new LifeDelay();
    gm->add(l);
    l->initall(gm,x,y);
    l->lifedelay(200, this);*/
}
void Flame::act() {
    // if collides with a ship, stick to it
    // dies in some 200 frames
    genmove();
}
