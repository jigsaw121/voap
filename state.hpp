#ifndef STATE_H
#define STATE_H

#include <SFML/System.hpp>
#include "interactive.hpp"
#include <vector>

class State {
	public:
		int exitflag;
		sf::Clock clock;
		std::vector<Interactive*> objects;
		std::vector<Interactive*> introbuffer;
		std::vector<Interactive*> erasebuffer;

		explicit State() { exitflag = 0;/*clock.start();*/ }

		void add(Interactive*);
		void add2();
		void remove(Interactive*);
		void remove2();
		int mstime();
		virtual bool mainloop();
};

#endif
