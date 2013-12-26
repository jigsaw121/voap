#include "settings.hpp"
#include <SFML/Graphics.hpp>

#define MAX_PLAYERS 4

Settings::Settings() {
    int i;
    players = 3;
    respawn = 300;

    //blah, just test player 1 for now
    keycodes.push_back(new keycode(sf::Key::W, sf::Key::S, sf::Key::A, sf::Key::D, sf::Key::Z, sf::Key::X));
    for (i=1; i<MAX_PLAYERS; i++) {
        keycodes.push_back(new keycode(sf::Key::Escape, sf::Key::Escape, sf::Key::Escape, sf::Key::Escape, sf::Key::Escape, sf::Key::Escape));
    }
}
Settings::~Settings() {
    int i;
    for (i=0; i<MAX_PLAYERS; i++) {
        keycodes.pop_back();
    }
}
