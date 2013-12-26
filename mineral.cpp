#include "mineral.hpp"

Mineral::Mineral(VoaP* _voap, double _x, double _y, int _value) {
    x = _x; y = _y;
    // value equals lifetime -> early gathering pays
    // (exposure to gases causes rapid corrosion)
    value = _value;
    voap = _voap;

    img.LoadFromFile("rox.png");
    img.SetSmooth(false);
    spr.SetImage(img);
    spr.SetSubRect(sf::IntRect(0,0,32,32));
    spr.SetPosition(x,y);

    //lifetime = 64+value*4;
}
void Mineral::wane() {
    // retard check
    if (value > 0) {
        value--;
    }
}
void Mineral::draw() {
    sf::Vector2<float> pos = voap->art->get_active_layer()->surface()->GetPosition();
    spr.SetPosition(pos.x+x, pos.y+y);
    voap->Scr.Draw(spr);
}
bool Mineral::alive() {
    return (value > 0);
}
bool Mineral::collected() {
    if (value==0) {
        return false;
    }
    Ship* s = voap->gm->ship_collide(x,y);
    if (s) {
        s->gather(value);
        value = 0;
        return true;
    }
    return false;
}
