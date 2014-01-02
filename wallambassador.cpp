bool WallAmbassador::collide(Interactive* obj) {
    // for objects with x,y,w,h
    int x, y;
    sf::Color c;
    Layer* l = get_active_layer();
    sf::Vector2<float> pos = l->get_pos();
	
	if (obj->x < 0 || obj->x+obj->w >= l->w || obj->y < 0 || obj->y+obj->h >= l->h) return true;
	
    for (x=0; x<obj->w; x++) {
        for (y=0; y<obj->h; y++) {
            c = l->spr.GetPixel(o->x+x, o->y+y);
			// (0,0,0) could also be any manually set transparent color
			// if I ever add a level editor
            if (c.a != 0 && (c.r!=0 || c.g!=0 || c.b!=0)) {
                //std::cout<<(int)c.r<<" "<<(int)c.g<<" "<<(int)c.b<<" "<<(int)c.a<<"\n";
                //std::cout<<o->x+x<<" "<<o->y+y<<"\n";
                return true;
            }
        }
    }
    return false;
}