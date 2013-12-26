#ifndef GAME_H
#define GAME_H

#include <vector>

#include "mineral.hpp"
#include "explosive.hpp"
#include "layer.hpp"
#include "ship.hpp"

class Ship;
class Layer;
class ParallaxLayer;

struct pos {
    int x,y;
};

class GameMaster {
    std::vector<Ship*> ships;
    std::vector<Ship*> junkyard;
    std::vector<Mineral*> minerals;
    std::vector<Explosion*> boom;

    pos pick_pos();
    void ship_init();
    void ship_process();
    void trash_ships();
    void mineral_process();
    void trash_minerals();
    void add_minerals(Ship*);

    template <class T>
    void clear_items(std::vector<T*>*);

    public:
        GameMaster(VoaP*);
        ~GameMaster();

        VoaP* voap;
        int players;

        int act();
        Ship* get_player(int);
        int player_amt();
        Ship* ship_collide(double, double);
        // draws everything in the game into the active layer
        void draw(Layer*);
        void respawn();
        //template <class T>
        void blast_radius();
        void blow_up(double, double);
        void explode(Explosion*);
        bool bump(Ship*);
        //bool bump(Bullet*);
};

//template <class T>
#endif
