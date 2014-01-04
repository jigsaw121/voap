#ifndef GM_HPP
#define GM_HPP
#include "layer2.hpp"
#include "state.hpp"
#include "ship2.hpp"

class GM: public State {
    // game states are a stack, this is the in-game one
    // when esc is pressed whenever you're here, it drops back into the menu
    // probably adds some listener object that can do anims for that etc.
    public:
        explicit GM(sf::RenderWindow* _scr);
        //~GM() {}
        virtual bool mainloop();
};
#endif
