#include "gm.hpp"
#include "ship2.hpp"
#include <iostream>

/*GM::GM(sf::RenderWindow* _scr): State(_scr) {
    add(new Ship(this,0,0));
}*/
bool GM::mainloop() {
    if (exitflag || !scr) return false;

    int st = mstime(); double frame = 1000/2.0;

    if (lag<0) lag=0;
    double _lag = lag;
    // warn/abort/skip drawing if lag gets too high
    unsigned int i;
    //for (i=objects.begin(); i<objects.end(); i++) objects[i]->move();

    /*sf::Event event;
    while (scr->pollEvent(event))
    {
        if (event.Type == sf::Event::Closed)
            scr->Close();
    }

    scr->Clear(sf::Color::Black);*/

    for (i=0; i<objects.size(); i++) objects.at(i)->act();
    // if drawing is taking too long (lag piled up from a couple of frames),
    // might just skip a frame
    if (lag<frame*3) {
        for (i=0; i<objects.size(); i++) {
            objects.at(i)->draw();
        }
    }

    // actually remove/add from buffers
    remove2(); add2();

    /*scr->Display();*/

    // how much we're lagging from the desired fps
    // if negative (=we're ahead), gets fixed when setting _lag next frame
    lag += mstime()-st - frame;

    // if we're ahead, let's just wait
    // note that _lag is at least 0
    while (mstime()-st < frame-_lag)
        ;

    return true;
}
