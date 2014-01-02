#include <SFML/System.hpp>
#include <iostream>
#include <vector>

#include "gm.hpp"

int main(void)
{
    sf::RenderWindow scr(sf::VideoMode(800,600), "voap");

    GM* gm = new GM(&scr);

    // usually called after menus
    while (gm->mainloop())
        ;
    delete gm;

    std::cout<<"all gone!\n";

    return 0;
};
