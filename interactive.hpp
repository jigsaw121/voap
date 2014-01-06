#ifndef INTERACTIVE_HPP
#define INTERACTIVE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "types.hpp"

class Ship;
class State;
class Layer;

class Interactive {
    public:
        State* gm;
        double x,y,w,h;
        bool dying;
        std::vector<Typenum::type> types;

        sf::Sprite spr;
        sf::Texture texture;

        explicit Interactive(/*State* _gm, double _x, double _y*/) {
            /*initall(_gm,_x,_y);*/
        }
        ~Interactive() {
            //delete texture;
            //delete spr;
        }
        virtual void initall(State* _gm, double _x, double _y) {
            // in case there's ever some weird behaviour
            gm = _gm;
			dying = false;
            dimsinit();
            shareinit(_x,_y);
            typeinit();
            imginit();
			specinit();
        }
		virtual void specinit() {}
        virtual void shareinit(double _x, double _y) { x = _x; y = _y; }
        // default-y values for the rest of the init functions
        virtual void dimsinit() { w = 24; h = 24; }
		// could just have a type vector
		// so you could search for any type, all inheritants, or just one specific type
		// (even under specific conditions if necessary)
        virtual void typeinit() { //type = 0;
			types.push_back(Typenum::ANY);
			typeinit2();
		}
		virtual void typeinit2() {}
        virtual void imginit() {
            texture.create(w,h);
            sf::Image image;
            image.create(w, h, sf::Color(128, 128, 128, 255));
            texture.update(image);
            //img.setSmooth(false);
            spr.setTexture(texture);
            //spr.setOrigin(20, 20);
        }

        void skip() {}
        void cap(double* n, double low, double hi) {
            if (*n<low) *n=low;
            else if (*n>hi) *n=hi;
        }

        virtual void spawn();
        virtual void move() {}
        virtual void act() {}
		// override for optional draws
		virtual void gendraw();
        virtual void draw() { gendraw(); }
        virtual void remove();
        virtual void die();

		// implemented for modules only
		virtual void set_host(Ship*) {}
		virtual void collectme(Ship*) {}
		virtual void explode() {}

        sf::RenderWindow* screen();

        virtual bool collide(Interactive* obj);
        bool matchtype(std::vector<Typenum::type>, int);
        std::vector<Interactive*> find(int ftype);
        std::vector<Interactive*> mergevectors(std::vector<Interactive*> a, std::vector<Interactive*> b);
        std::vector<Interactive*> collidetype(int type);
        std::vector<Interactive*> collidetypes(std::vector<int> types);
        Interactive* collideone(int type);

		Layer* get_active_layer();
		sf::Vector2<float> camera();
};

#endif
