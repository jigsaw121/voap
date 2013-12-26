#include "artist.hpp"
#include <sstream>

Artist::Artist(VoaP* _voap) {
    voap = _voap;
    // init layers
    layers.push_back(new BGLayer(voap, 160, 178, 223));
    // think of rx, ry as "distance from camera"
    /* actually could have n background layers
     * just specifying the three vars
     * and sorting in-game
     * specifying the background color & solid layer separately
     */
    layers.push_back(new ParallaxLayer(voap, "bg0b.png", false, -0.80, -0.80));
    layers.push_back(new ParallaxLayer(voap, "bg0.png", false, -0.64, -0.64));
    layers.push_back(new ParallaxLayer(voap, "testlvl_s.png", true, 0, 0));
    layers.push_back(new ParallaxLayer(voap, "bg3.png", false, 0.48, 0.48));
    /*// lags behind the above layer
    layers.push_back(new ParallaxLayer);
    // parallax layer with zero movement?
    layers.push_back(new ParallaxLayer);
    layers.push_back(new SolidLayer);
    // moves faster than the previous layer
    layers.push_back(new ParallaxLayer);
    */
}
Artist::~Artist() {
    // clear layers
    int i; Layer* l;
    for (i=layers.size()-1; i>=0; i--) {
        l = layers[i];
        layers.pop_back();
        delete l;
    }
}
void Artist::display() {
    /*if (voap->frame%4==0) {
        std::stringstream frame_str;
        frame_str << voap->frame;
        voap->Scr.Capture().SaveToFile("screenshot"+frame_str.str()+".png");
    }*/

    voap->Scr.Display();
}
void Artist::layer_process() {
    unsigned int i;
    for (i=0; i<layers.size(); i++) {
        layers[i]->act();
        if (layers[i]->active) {
            // interrupt to draw everything in this layer
            voap->gm->draw(layers[i]);
        }
    }
}
void Artist::layer_update(double dx, double dy) {
    unsigned int i;
    // don't nudge bglayer
    for (i=1; i<layers.size(); i++) {
        layers[i]->nudge(dx, dy);
    }
}
ParallaxLayer* Artist::get_active_layer() {
    // huhu
    return static_cast<ParallaxLayer*>(layers[3]);
}
void Artist::act() {
    /* interact with player, draw layers
     * the solid layer (where entities are drawn) probably requires
     * more complex procedures & sub-procedures
     * for layers, could just call act method
     * and command from here to draw entities after solid layer
     * finally draw top layer, do post-processing/screenshots etc
     * and update the screen
     */
    layer_process();
    display();
}
