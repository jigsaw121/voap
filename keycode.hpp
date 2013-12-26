#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef KEYCODE_H
#define KEYCODE_H

struct keycode {
    sf::Key::Code up;
    sf::Key::Code down;
    sf::Key::Code left;
    sf::Key::Code right;
    sf::Key::Code shoot1;
    sf::Key::Code shoot2;
    keycode(sf::Key::Code _up, sf::Key::Code _down, sf::Key::Code _left, sf::Key::Code _right, sf::Key::Code _shoot1, sf::Key::Code _shoot2) {
        up = _up; down = _down; left = _left; right = _right; shoot1 = _shoot1; shoot2 = _shoot2;
        std::cout<<"set keycode\n";
    }
};

#endif
