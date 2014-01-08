#include "module.hpp"
#include "ship2.hpp"

void Module::swap(Ship* s) {
    unsigned int i;
    for (i=0; i<s->cargo.size(); i++) {
        if (matchtype(s->cargo[i]->types, Typenum::MODULE)) {
            s->modi = s->cargo[i]; s->cargo.erase(s->cargo.begin()+i);
            s->cargo.push_back(this);
            return;
        }
    }
    // otherwise nothing needs to be done
}

/*
// makes more sense to have it as a ship function since everything is from its perspective

void Ship::swap(Module* m) {
    unsigned int i;
    for (i=0; i<cargo.size(); i++) {
        if (matchtype(cargo[i]->types, Typenum::MODULE)) {
            modi = cargo[i]; cargo.erase(cargo.begin()+i);
            cargo.push_back(m);
            return;
        }
    }
    // otherwise nothing needs to be done
}
*/

void Module::set_host(Ship* s) {
    // drawing, collections should cease when host is set
    // no need to check if there's already a host because the logic already prevents that
    host = s;
    s->cargo.push_back(this);
}

void Module::collectme(Ship* s) {
    if (host!=NULL) return;

    set_host(s);
}
