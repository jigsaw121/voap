#include "interactive.hpp"
#include "layer2.hpp"
#include "state.hpp"

int State::findintr(std::vector<Interactive*> objs, Interactive* obj) {
    unsigned int i;
    for (i=0; i<objs.size(); i++) {
        if (objs[i]==obj) return i;
    }
    return -1;
}
void State::clearall() {
    // gotta free memory, etc.
    introbuffer.clear();
    erasebuffer.clear();
    objects.clear();
}
Interactive* State::add(Interactive* obj) {
    introbuffer.push_back(obj);
	return obj;
}
Layer* State::lradd(Layer* obj) {
    introbuffer.push_back(static_cast<Interactive*>(obj));
	return obj;
}
Interactive* State::prev() {
	// for quick references on inits
	// inits are messy enough already, give them a break
    return introbuffer.back();
}
void State::add2() {
    // called every frame, introbuffer.size() can be zero and this is skipped
    while (introbuffer.size()) {
        objects.push_back(introbuffer.back());
        introbuffer.pop_back();
    }
}
void State::remove(Interactive* obj) {
    erasebuffer.push_back(obj);
}
void State::remove2() {
    // called every frame, erasebuffer.size() can be zero and this is skipped
    int f;
    //for (i=erasebuffer.begin(),i<erasebuffer.end(),i++) {
    while (erasebuffer.size()) {
        // or last element for faster removes
        // assume it's not there several times
        f = findintr(objects, erasebuffer.back());
        if (f == -1) {
            // wut?
            erasebuffer.pop_back();
            continue;
        }
        objects.erase(objects.begin()+f);
        // not necessarily deleted
        if (erasebuffer.back()->dying) delete erasebuffer.back();
        erasebuffer.pop_back();
    }
}
int State::mstime() {
    sf::Time elapse = clock.getElapsedTime();
    return elapse.asMilliseconds();
}
