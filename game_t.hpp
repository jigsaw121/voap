template <class T>
bool GameMaster::bump(T* o) {
    // for objects with x,y,w,h
    int x, y;
    sf::Color c;
    ParallaxLayer* l = static_cast<ParallaxLayer*>(voap->art->get_active_layer());
    sf::Vector2<float> pos = l->spr.GetPosition();
    for (x=0; x<32; x++) {
        for (y=0; y<32; y++) {
            c = l->spr.GetPixel(o->x+x, o->y+y);
            if (c.a != 0 && (c.r!=0 || c.g!=0 || c.b!=0)) {
                std::cout<<(int)c.r<<" "<<(int)c.g<<" "<<(int)c.b<<" "<<(int)c.a<<"\n";
                std::cout<<o->x+x<<" "<<o->y+y<<"\n";
                return true;
            }
        }
    }
    return false;
}

