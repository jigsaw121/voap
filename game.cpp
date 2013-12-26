#include "game.hpp"
#include <typeinfo>

GameMaster::GameMaster(VoaP* _voap) {
    voap = _voap;
    players = voap->st->players;
    std::cout<<"Starting new game with "<<players<<" players\n";

    ship_init();
}
template <class T>
void GameMaster::clear_items(std::vector<T*>* vec) {
    int i; T* s;

    std::cout<<"clearing "<<vec->size()<<" items of type "<<typeid(T).name()<<"\n";
    for (i=vec->size()-1; i>=0; i--) {
        s = (*vec)[i];
        vec->pop_back();
        delete s;
    }
}
GameMaster::~GameMaster() {
    clear_items(&ships);
    clear_items(&junkyard);
    clear_items(&minerals);

    std::cout<<"Game over\n";
}
pos GameMaster::pick_pos() {
    /* get a placement that's safe and not solid */
    pos p;

    //pfft
    p.x = 320-16 + 64*player_amt(); p.y = 16;

    return p;
}
void GameMaster::draw(Layer* l) {
    // could be templated
    unsigned int i;
    for (i=0; i<ships.size(); i++) {
        // draws everything contained by the ship
        ships[i]->draw(l);
    }
    for (i=0; i<minerals.size(); i++) {
        minerals[i]->draw();
    }
}
void GameMaster::ship_init() {
    int i;
    pos p;

    for (i=0; i<players; i++) {
        p = pick_pos();
        ships.push_back(new Ship(voap, p.x, p.y));
        ships.back()->keys = voap->st->keycodes[i];
        ships.back()->p_num = i+1;
        ships.back()->speed *= ships.back()->p_num;
        ships.back()->view = NULL;
        std::cout<<"Player "<<ships.back()->p_num<<": keycode 'up' is "<<ships.back()->keys->up<<"\n";
    }
    ships[0]->view = voap->art;

    voap->art->layer_update(0,180);
}
Ship* GameMaster::get_player(int n) {
    return ships[n];
}
void GameMaster::ship_process() {
    int i;
    for (i=0; i<player_amt(); i++) {
        ships[i]->act();
    }

    // avoid race conditions by checking trash after processing
    trash_ships();
}
void GameMaster::add_minerals(Ship* s) {
    int i;
    std::vector<Mineral*> belt = s->generate_minerals();
    std::cout<<"destroyed ship spawns "<<belt.size()<<" minerals\n";

    for (i=belt.size()-1; i>=0; i--) {
        //std::cout<<"mineral "<<i<<" at "<<belt[i]<<"\n";
        minerals.push_back(belt[i]);
        belt.pop_back();
    }
}
void GameMaster::trash_ships() {
    unsigned int i=0;
    Ship* s;

    while (i<ships.size()) {
        s = ships[i];
        if (!s->alive()) {
            // send to junkyard
            junkyard.push_back(s);
            add_minerals(s);
            ships.erase(ships.begin()+i);
        }
        else {
            // only move to next index if previous ship wasn't trashed
            i++;
        }
    }
}
void GameMaster::mineral_process() {
    unsigned int i=0;
    Mineral* m;
    // feed minerals to ships -> disappear from minerals list
    // or ships should collect minerals
    while (i<minerals.size()) {
        m = minerals[i];
        if (m->collected()) {
            std::cout<<"bling\n";
            minerals.erase(minerals.begin()+i);
            // ship doesn't store the mineral, just its value
            delete m;
        }
        else {
            m->wane();
            i++;
        }
    }

    trash_minerals();
}
void GameMaster::trash_minerals() {
    unsigned int i=0;
    Mineral* m;

    while (i<minerals.size()) {
        m = minerals[i];
        if (!m->alive()) {
            minerals.erase(minerals.begin()+i);
            std::cout<<"mineral corroded...\n";
            delete m;
        }
        else {
            i++;
        }
    }
}
int GameMaster::act() {
    /* one frame of actions
     * return 0 on success, 1 on quit
     */
    if (voap->Scr.GetInput().IsKeyDown(sf::Key::Escape)) {
        return 0;
    }

    blast_radius();
    respawn();
    ship_process();
    mineral_process();

    return 1;
}
int GameMaster::player_amt() {
    return ships.size();
}
void GameMaster::respawn() {
    unsigned int i=0; Ship* s;

    while (i<junkyard.size()) {
        s = junkyard[i];
        s->respawn--;

        if (s->respawn==0) {
            junkyard.erase(junkyard.begin()+i);
            s->respawn = voap->st->respawn;
            s->hp = s->maxhp;
            ships.push_back(s);
        }
        else {
            i++;
        }
    }
}
Ship* GameMaster::ship_collide(double hx, double hy) {
    unsigned int i;
    for (i=0; i<ships.size(); i++) {
        if (ships[i]->collide(hx, hy)) {
            return ships[i];
        }
    }

    return NULL;
}
void GameMaster::blow_up(double _x, double _y) {
    boom.push_back(new Explosion(_x,_y));
}
void GameMaster::explode(Explosion* src) {
    // process held entities for explosions
    unsigned int i = 0; Ship* s;

    while (i<ships.size()) {
        s = ships[i];
        /*if (s->explode(src)) {
            ships.erase(ships.begin()+i);
            delete s;
        }
        else {
            i++;
        }*/

        // cleanup for broken ships is done based on hp
        s->explode(src);
        i++;
    }
}
void GameMaster::blast_radius() {
    //Explosion* src;

    // there should be a delay for explosions added within
    unsigned int i = 0; Explosion* src;

    while (boom.size() > 0) {
        src = boom[i];
        explode(src);

        // only done because of said recursive explosions...
        boom.erase(boom.begin());
        delete src;
        std::cout<<"blast radius\n";
    }
}

bool GameMaster::bump(Ship* o) {
    // for objects with x,y,w,h
    int x, y;
    sf::Color c;
    ParallaxLayer* l = voap->art->get_active_layer();
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
