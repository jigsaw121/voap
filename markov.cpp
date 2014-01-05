#include "markov.hpp"

void TrailMod::act() {
	// module follows ship, constantly spawns trail atoms that block/hurt
	// trails disappear after a while
	// can be toggled on/off to save power
	gm->add(/* new trail of the current type at this pos */);
}

void TurretMod::use() {
	// drop a turret base that'll build itself once it hits the ground
	// turret building can be accelerated with slow turrets
	// and they can be repaired later
	// (there are different types that inherit from this)
	gm->add(new Turret());
	gm->prev()->initall(gm,x,y);
}

void Turret::fall(int* state) {
	if (collideone(OBJECT_TYPE)) {
		// bounce back!
		// enemies might juggle turret seeds to block them, and other emergent behaviour
		x -= dx; y -= dy;
		dx = -dx/1.1; dy = -dy/1.1;
	}
	if (collideone(WALL_TYPE)) {
		// should I have a swapstate() for all Interactives?
		//vact = &build;
		*state = 1;
		return;
	}
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
	Interactive* close = closestenemy(range);
	if (close) shootat(close);
}