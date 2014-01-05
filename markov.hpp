// defensive mods
// markov ships should also be in one file and include this

#include "module.hpp"
#include "movingobj.hpp"

class TrailMod: public Module() {
	// attributes changed depending on ship
	public:
		explicit TrailMod(): Module() {}
		// main functionality acts, passive (always on?)
		virtual void act();
}

class TurretMod: public Module() {
	// attributes changed depending on ship
	public:
		explicit TurretMod(): Module() {}
		virtual void use();
		virtual void act();
}

// could be in a separate file later
class Turret: public MovingObj() {
	public:
		explicit Turret(): MovingObj() {}
		
		// function pointers yay
		//void (*vact)(Turret* self);
		virtual void act() { //vact(this);
			// at any time, if it's blown up, it dies
			// better to destroy before it spawns
		
			// or even further, a state manager interface thingy with method pointers
			static int state = 0;
			switch(state) {
				case 0:
					fall(&state); break;
				case 1:
					build(&state); break;
				case 2:
					// can't change state so doesn't take that argument
					aim(); break;
			}
		}
		
		/*virtual void specinit() {
			dx=0.0; dy=0.0; angle=0.0;
			specs();
			vact = &fall;
		}*/
		void fall(int*);
		void build(int*);
		void aim();
}
// not very C++ though
// might do a switch-case state machine thingy for act() instead
// a turret falls first until it hits the ground
// (probably just bounces off of other objects)
// then it builds itself
//void fall(Turret* self);
//void build(Turret* self);
//void aim(Turret* self);
// ei ollukkaan huva tama
