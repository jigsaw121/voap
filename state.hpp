#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include "interactive.hpp"
#include <vector>
#include <iostream>

class Interactive;

class State {
    public:
        int exitflag, lag;
        sf::Clock clock;
        sf::RenderWindow* scr;
        Layer* aclayer;
        std::vector<Interactive*> objects;
        std::vector<Interactive*> introbuffer;
        std::vector<Interactive*> erasebuffer;

        explicit State(sf::RenderWindow* _scr) {
            exitflag = lag = 0;
            scr = _scr;
            //std::cout<<&clock;
            /*clock.start();*/
        }

        int findintr(std::vector<Interactive*> objs, Interactive* obj);

        Interactive* prev();
        Interactive* add(Interactive*);
        void add2();
        void remove(Interactive*);
        void remove2();
        int mstime();
        virtual bool mainloop() { return false; }
};

#endif
