#include <iostream>
#include <vector>

#include "voap.hpp"

int main(void)
{
    VoaP* voap = new VoaP();

    // usually called after menus
    voap->play_init();
    while (voap->act())
        ;
    delete voap;

    std::cout<<"all gone!\n";

    return 0;
}
