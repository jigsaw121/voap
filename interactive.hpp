#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include <SFML/Graphics.hpp>
#include "state.hpp"
#include <vector>

class State;

class Interactive {
    public:
        State* gm;
        double x,y,w,h;
        int type;

        sf::Sprite spr;

        explicit Interactive(State* _gm, double _x, double _y) {
            //initall(_gm,_x,_y);
        }
        ~Interactive() {
            //delete img;
            //delete spr;
        }
        virtual void initall(State* _gm, double _x, double _y) {
            // in case there's ever some weird behaviour
            gm = _gm;
            dimsinit();
            shareinit(_x,_y);
            typeinit();
            imginit();
        }
        virtual void shareinit(double _x, double _y) { x = _x; y = _y; }
        // default-y values for the rest of the init functions
        virtual void dimsinit() { w = 24; h = 24; }
        virtual void typeinit() { type = 0; }
        virtual void imginit() {
            /*sf::Texture texture;
            texture.create(w,h);
            sf::Image image;
            image.create(w, h, sf::Color(128, 128, 128, 255));
            texture.update(image);
            //img.setSmooth(false);
            spr.setTexture(texture);
            spr.setOrigin(0.5, 0.5);*/
        }

        void skip() {}

        virtual Interactive* spawn() {
            return new Interactive(gm,x,y);
        }
        virtual void move() {}
        virtual void act() {}
        virtual void draw();
        virtual void remove();

        sf::RenderWindow* screen();

        virtual bool collide(Interactive* obj);
        std::vector<Interactive*> find(int ftype);
        std::vector<Interactive*> mergevectors(std::vector<Interactive*> a, std::vector<Interactive*> b);
        std::vector<Interactive*> collidetype(int type);
        std::vector<Interactive*> collidetypes(std::vector<int> types);
        Interactive* collideone(int type);
};
#endif
