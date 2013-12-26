#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include "vector"
#include <SFML/Graphics.hpp>

#include "ship.hpp"
#include "game.hpp"

class Ship;
struct pos;

class Bullet {
    public:
        Ship* host;
        double x, y;
        double w, h;
        virtual void set_width() {w=4; h=4; std::cout<<w<<" "<<h<<"\n";};
        virtual void init();
        double dir;
        double speed;
        double dmg;
        void empty() {std::cout<<"nop\n";}

        explicit Bullet(Ship*);
        ~Bullet();
        virtual void move();
        void act();
        bool fizzle();
        bool oop();
        virtual bool hit();
        void draw();
        bool bump();
        //template <class T>
        // most bullets don't explode, rockets etc do
        //template <class T>
        //void blast(T*);
        virtual bool explode(Explosion*) { return false; }

        sf::Image img;
        sf::Sprite spr;
};

class KnockerBullet: public Bullet {
    public:
        explicit KnockerBullet(Ship*, pos*, double);
        ~KnockerBullet() {};
        bool hit();
};

class Mine: public Bullet, public Explosive {
    public:
        explicit Mine(Ship*);
        ~Mine() {};
        bool hit();
        virtual void move() {};
        virtual void init();
};

class Rocket: public Bullet, public Explosive {
    public:
        explicit Rocket(Ship*);
        ~Rocket() {};
        virtual void set_width() {w=6; h=6; std::cout<<w<<" "<<h<<"\n";};
        virtual bool hit();
        virtual void move();
        virtual void init();

        void (Rocket::*accel)();
        void speeddown() {speed-=0.25; if (speed<0.3) accel=&Rocket::speedup;}
        void speedup() {speed++;}

        // test for collisions
        virtual bool explode(Explosion*);
};

class Weapon {
    protected:
        Ship* host;
        std::string id;
        int cooldown;
        int maxcool;
    public:
        Weapon();
        ~Weapon();
        virtual void init();
        std::vector<Bullet*> bullets;
        virtual void shoot();
        void act();
        void bullet_mgmt();
        void bullet_draw();
        void draw();
        pos bullet_pos(double, double, double, double);
        //template <class T>
        //void blast(T*);
        void explode(Explosion*);

        //sf::Image img;
        //sf::Sprite spr;
};

class LaserSpray: public Weapon {
    public:
        LaserSpray(Ship*);
        void init();
};
class Knocker: public Weapon {
    public:
        Knocker(Ship*);
        void init();
        void shoot();
};
class Rockets: public Weapon {
    public:
        Rockets(Ship*);
        void init();
        void shoot();
};
class MineDrop: public Weapon {
    public:
        MineDrop(Ship*);
        void init();
        void shoot();
};

#endif
