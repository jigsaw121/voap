#include "interactive.hpp"
#include "layer2.hpp"
#include <iostream>

bool Interactive::collide(Interactive* obj) {
    // optimizations in searching for types
    return !( (y+w < obj->y) ||
              (y > obj->y+obj->w) ||
              (x > obj->x+obj->w) ||
              (x+w < obj->x) );
}
std::vector<Interactive*> Interactive::find(int ftype) {
    std::vector<Interactive*> out;

    // sort gm's objects so all objects of the same type are next to each other
    // (jump straight to where the wanted type is, cancel on first that isn't of the same type)
    unsigned int i; Interactive* obj;
    for (i=0; i<gm->objects.size(); i++) {
        obj = gm->objects[i];
        if (obj->type != ftype) continue;
        if (abs(obj->x-x)>obj->w+w || abs(obj->y-y)>obj->h+h) continue;
        out.push_back(obj);
    }

    return out;
}
std::vector<Interactive*> Interactive::mergevectors(std::vector<Interactive*> a, std::vector<Interactive*> b) {
    std::vector<Interactive*> out;
    out.reserve(a.size()+b.size());
    out.insert(out.end(), a.begin(), a.end());
    out.insert(out.end(), b.begin(), b.end());
    return out;
}
Interactive* Interactive::collideone(int type) {
    unsigned int i=0; Interactive* obj;
    std::vector<Interactive*> found = find(type);
    while (i<found.size()) {
        obj = found[i];
        if (obj->collide(this)) return obj;
        else i++;
    }
    return NULL;
}
std::vector<Interactive*> Interactive::collidetype(int type) {
    unsigned int i=0; Interactive* obj;
    std::vector<Interactive*> found = find(type);
    while (i<found.size()) {
        obj = found[i];
        if (!obj->collide(this)) found.erase(found.begin()+i);
        else i++;
    }
    return found;
}
std::vector<Interactive*> Interactive::collidetypes(std::vector<int> types) {
    unsigned int i; std::vector<Interactive*> colls;
    for (i=0; i<types.size(); i++) {
        colls = mergevectors(colls, collidetype(types[i]));
    }
    return colls;
}
void Interactive::remove() {
    // dying would also have a consequence of delete this; at gm's remove2()
    // but it can't be automatically implemented since sometimes temporary deactivation is useful
    gm->remove(this);
}
void Interactive::die() {
    // oh look a boolean
	// crude but it works I guess
    remove();
	dying = true;
}
sf::RenderWindow* Interactive::screen() {
    return gm->scr;
}
void Interactive::gendraw() {
    sf::Vector2<float> pos = offset();
    // really? am I supposed to do it like this?
    spr.setPosition(pos.x+x, pos.y+y);
    //std::cout<<"I'm drawn at "<<pos.x+x<<", "<<pos.y+y<<"\n";
    screen()->draw(spr);
}
void Interactive::spawn() {
    gm->add(new Interactive(/*gm,x,y*/))->initall(gm,x,y);
}
Layer* Interactive::get_active_layer() {
    return gm->aclayer;
}
sf::Vector2<float> Interactive::camera(); { 
	return gm->camera->offset(); 
}