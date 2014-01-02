#include "movingobj.hpp"
#include "ship2.hpp"

class Ship;

class Module: public MovingObj {
	// MovingObj because there'll be physical modules on ship drops
	// before that, they're not updated (and not added to gm)
	// alternatively, encapsulate them in a separate moving fragment...
	public:
		Ship* host;

		explicit Module(State* _gm, double _x, double _y, Ship* _host): MovingObj(_gm,_x,_y) { host = _host; }
		virtual void move();
		// when a ship dies it calls this
		virtual void die_consequence() {}
};
