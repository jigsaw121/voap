#ifndef SHIP_H
#define SHIP_H

#include <iostream>

#include "weapon.hpp"
#include "layer.hpp"
#include "mineral.hpp"

class Weapon;
class Layer;
class Mineral;
class Tangent;
class Artist;

class Ship {
    Weapon* w1;
    Weapon* w2;
    void set_weapon();
    void move(int fwd);
    void tangent_move(Tangent*);
    void gravity();

    public:
        Ship(VoaP*, int, int);
        ~Ship();

        Artist* view;
        void layer_update(double, double);

        VoaP* voap;
        keycode* keys;
        Tangent* tng;
        Tangent* push_tng;

        double hp;
        double maxhp;
        double x,y;
        double dir;
        double speed;
        double grav;
        double gacc;
        int p_num;
        int minerals;
        int respawn;
        sf::Image img;
        sf::Sprite spr;

        void draw(Layer*);
        void weapon_draw();
        void set_pos(int _x, int _y) {x = _x; y = _y; std::cout<<x<<" "<<y<<"\n";}
        int act();
        void input();
        void shoot();
        bool collide(double, double);
        Ship* bullet_collide(double, double);
        void damage(double);
        bool alive();
        void gather(int);
        std::vector<Mineral*> generate_minerals();
        void push(double, double);
        //template <class T>
        //void blast(T*);
        void explode(Explosion* src);
};

class Tangent {
    public:
        Tangent(double, double);
        ~Tangent() {};
        double dir;
        double acc;
        void slow() {if (acc>=0.02) acc-=0.02; else acc=0;};
};

#endif
