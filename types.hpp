// each Interactive contains at least one of these types
// (as many as their nesting depth)
// also illustrates the inheritance tree at a quick glance
namespace Typenum {
	enum type {
		ANY, // everyone has type ANY for processing all objects
			//ACTIVE, // might be used as a flag or something
			WALL, // actually just an interface for pixel collisions
			FACTORY,
			MOVING,
				SHIP,
				MODULE,
					WEAPON,
						ROCKETGUN,
						MINELAY,
						SNIPER,
					DEFENSE,
						TRAILMOD,
						TURRET,
						ACID,
					SPECIAL,
						STARGATE,
						ENHANCE,
						SPY,
						DETONATE,
					MINERAL,
				BULLET,
					BEAM,
					TRAIL,
					EXPLOSIVE,
						MINE,
						ROCKET,
						BOMB,
			ENGINEER // for non-gameplay types that still inherit from Interactive, like GUI stuff
	}
}

//#include "types.hpp"
//	virtual void typeinit3() {
//		types.push_back(Typenum::SHIP);
//		typeinit4();
//	}
//	virtual void typeinit4() {}