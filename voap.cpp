#include "voap.hpp"

VoaP::VoaP() {
    Scr.Create(sf::VideoMode(640, 400, 32), "VoaP");
    Scr.SetFramerateLimit(60);

    frame = 0;

    st = new Settings();
    art = new Artist(this);

    esc = false;
}
VoaP::~VoaP() {
    /* Clean up all the smaller global classes */
    std::cout<<"final cleanup...\n";

    delete st;
    st = NULL;
    delete art;
    art = NULL;

    play_end();
}
void VoaP::play_init() {
    if (gm) return;

    gm = new GameMaster(this);
}
void VoaP::play_end() {
    if (!gm) return;

    //move on to previous state
    delete gm;
    gm = NULL;
}
int VoaP::act() {
    /* Process whatever game state we're in, then return play/quit */
    /* Could mess around with function pointers */

    if (!Scr.IsOpened())
        return 0;

    while (Scr.GetEvent(event))
    {
        if (event.Type == sf::Event::Closed) {
            Scr.Close();
            return 0;
        }
    }
    /* Make it so that Esc only breaks out one state per press
     */
    if (Scr.GetInput().IsKeyDown(sf::Key::P))
        play_init();

    if (!play()) {
        play_end();
        return 1;
    }

    draw();

    frame++;

    return 1;
}
void VoaP::draw() {
    /* could be different types of artists,
     * this one owned by gm
     */
    if (gm)
        art->act();
    //art->get_active_layer()->spr.Draw(Scr);
}

int VoaP::play() {
    if (!gm) return 0;

    return gm->act();
}
