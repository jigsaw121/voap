#ifndef LAYER2_H
#define LAYER2_H
#include "interactive.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Layer: public Interactive {
	public:
		Interactive* follow;
		std::string filename;

        explicit Layer(/*State* _gm, double _x, double _y*/std::string _filename): Interactive(/*_gm,_x,_y*/) { filename = _filename; }
		virtual void specinit() {
			start_camerafollow(NULL);
		}
		virtual void imginit() {
			if (filename.empty()) return;
            texture.loadFromFile(filename);
            spr.setTexture(texture);
        }
        virtual void draw() {
            spr.setPosition(offset());
            screen()->draw(spr);
        }
		sf::Vector2<float> offset() {
			//sf::Vector2<float> pos = spr.getPosition();
			// danger - still called if there's no follow
			sf::Vector2<float> cntr((-x+320)/*+follow.w/2*/, (-y+240)/*+follow.h/2*/);
			return cntr;
		}
		void start_camerafollow(Interactive*);
		void camerafollow();
		virtual void act() {
			camerafollow();
			//if (!follow) return;
			//std::cout<<x<<", "<<y<<" "<<follow->x<<", "<<follow->y<<"\n";
		}
};

class BGLayer: public Layer {
	public:
        BGLayer(/*State* _gm, double _x, double _y*/): Layer(/*_gm,_x,_y*/"") {}
		virtual void imginit() {}
		virtual void draw() {
			screen()->clear(sf::Color(160,60,40));
		}
		virtual void act() {}
};

#endif
