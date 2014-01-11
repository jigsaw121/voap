#include "gm.hpp"
#include "ship2.hpp"
#include "layer2.hpp"
#include "camera.hpp"
#include <iostream>
//#include <SFML/Keyboard.hpp>

GM::GM(sf::RenderWindow* _scr): State(_scr) {
    conf = NULL;
    reset();
}
void GM::reset() {
    // just gotta remember to call initall every time it's needed
    // and if things change, to call a different one
    // these are pushed in the reverse order... not too intuitive
    // especially with the prev() references
    if (conf==NULL) {
        conf = new Config();
        //tiimi->name = "Naksuttajat";
        // this stuff is gonna need to be encapsulated
        // but I'm in my sketching mode
        // a lot of this relies on an eventual config menu anyway
        // (in which there'll be preset configs too)
        conf->teams.push_back(new Team());
        conf->teams.back()->id=0;
        conf->teams.back()->add_players(1);
        // ship type could be a generator class
        // with valid ships based on the faction
        conf->teams.back()->players.back()->set_ship(this, new Ship());
    }

    clearall();

    Interactive* intr;// = add(new Ship());
	// a factory generates ships/modules of its type
	// and a ship generates bullets of its type
    //intr->initall(this,0,0,0);
    unsigned int i,j;
    for (i=0; i<conf->teams.size(); i++) {
        for (j=0; j<conf->teams[i]->players.size(); j++) {
            intr = add(conf->teams[i]->players[j]->ship);
        }
    }

    aclayer = new Layer("aurpilkutyryry.png");
    add(aclayer)->initall(this,0,0);
    aclayer->start_camerafollow(intr);

    camera = new Camera();
    add(camera)->initall(this,0,0);
    camera->start_camerafollow(intr);

    BGLayer* bg = new BGLayer();
    add(bg)->initall(this,0,0);
}
bool GM::mainloop() {
    if (exitflag || !scr) return false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        reset();
        return true;
    }

    int st = mstime(); double frame = 1000/60.0;

    if (lag<0) lag=0;
    double _lag = lag;
    // warn/abort/skip drawing if lag gets too high
    unsigned int i;
    //for (i=objects.begin(); i<objects.end(); i++) objects[i]->move();

    sf::Event event;
    while (scr->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            scr->close();
            return false;
        }
    }

    for (i=0; i<objects.size(); i++) objects[i]->act();
    // if drawing is taking too long (lag piled up from a couple of frames),
    // might just skip a frame
    if (lag<frame*60) {
        for (i=0; i<objects.size(); i++) {
            objects[i]->draw();
        }
    }

    // actually remove/add from buffers
    remove2(); add2();

    scr->display();

    // how much we're lagging from the desired fps
    // if negative (=we're ahead), gets fixed when setting _lag next frame
    lag += mstime()-st - frame;
    if (lag>0) std::cout<<"Target "<<frame<<", ref "<<lag<<"\n";

    // if we're ahead, let's just wait
    // note that _lag is at least 0
    while (mstime()-st < frame-_lag)
        ;

    return true;
}
