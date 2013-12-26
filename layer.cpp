#include "layer.hpp"

Layer::Layer(VoaP* _voap) {
    voap = _voap;
}

BGLayer::BGLayer(VoaP* _voap, int r, int g, int b) {
    voap = _voap;
    active = false;
    color = new sf::Color(r,g,b);
}
void BGLayer::draw() {
    voap->Scr.Clear(*color);
}
void BGLayer::act() {
    draw();
}

ParallaxLayer::ParallaxLayer(VoaP* _voap, std::string src, bool _active, double _rx, double _ry) {
    voap = _voap;
    active = _active;
    img.LoadFromFile(src);
    img.SetSmooth(false);
    spr.SetImage(img);
    spr.SetPosition(0,0);
    sf::Color c = img.GetPixel(0,0);
    std::cout<<(int)c.r<<" "<<(int)c.g<<" "<<(int)c.b<<" "<<(int)c.a<<"\n";
    // think of rx, ry as "distance from camera"
    // makes calculations easier too (both in code and in head)
    rx = _rx; ry = _ry;
}
void ParallaxLayer::draw() {
    voap->Scr.Draw(spr);
}
void ParallaxLayer::nudge(double dx, double dy) {
    /* shift images in relation to player
     * needs to do calculations for variable speed ships
     * everything moves with the player's speed
     * in addition, there's a parallax nudge
     * assuming player stays at the center of the screen
     */
    spr.Move(dx+dx*rx, dy+dy*ry);
}
void ParallaxLayer::act() {
    draw();
}
