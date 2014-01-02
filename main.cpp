#include <SFML/System.hpp>
#include <iostream>
#include <vector>

#include "gm.hpp"

int main(void)
{
    GM* gm = new GM();

    // usually called after menus
    while (gm->mainloop())
        ;
    delete gm;

    std::cout<<"all gone!\n";

    return 0;
};
