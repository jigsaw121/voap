#include "vector"
#include "keycode.hpp"

class Settings {
    public:
        Settings();
        ~Settings();
        int players;
        int respawn;
        std::vector<keycode*> keycodes;
};
