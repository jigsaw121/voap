#ifndef STATE_H
#define STATE_H

#include <SFML/System.hpp>
#include "interactive.hpp"
#include <vector>

class Interactive;

class State {
	public:
		int exitflag, lag;
		sf::Clock clock;
		sf::RenderWindow* scr;
		std::vector<Interactive*> objects;
		std::vector<Interactive*> introbuffer;
		std::vector<Interactive*> erasebuffer;

		explicit State(sf::RenderWindow* _scr) {
		    exitflag = lag = 0;
            scr = _scr;
            /*clock.start();*/
        }

        int findintr(std::vector<Interactive*> objs, Interactive* obj);

		void add(Interactive*);
		void add2();
		void remove(Interactive*);
		void remove2();
		int mstime();
		virtual bool mainloop();
};

#endif
