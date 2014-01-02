#ifndef GM_H
#define GM_H
#include "state.hpp"

class GM: public State {
    // game states are a stack, this is the in-game one
    // when esc is pressed whenever you're here, it drops back into the menu
    // probably adds some listener object that can do anims for that etc.
    public:
        explicit GM(sf::RenderWindow* _scr)/*: State(_scr)*/;
        virtual bool mainloop();
};
#endif
