#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

#include "gm.hpp"

int main(void)
{
    std::cout<<"zz\n";
    sf::RenderWindow scr;
    scr.create(sf::VideoMode(640,400,32), "voap");

    GM* gm = new GM(&scr);

    // usually called after menus
    while (gm->mainloop())
        ;
    delete gm;

    std::cout<<"all gone!\n";

    return 0;
};
