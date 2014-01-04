#include <SFML/Graphics.hpp>
#include "interactive.hpp"

class Layer: public Interactive {
	public:
		Interactive* follow;
		std::string filename;
		
        Layer(/*State* _gm, double _x, double _y*/_filename): Interactive(/*_gm,_x,_y*/) { filename = _filename; }
		virtual void specinit() {
			start_camerafollow(NULL);
		}
		virtual void imginit() {
			if (filename.empty()) return;
            sf::Texture texture;
            texture.loadFromFile(filename);
            spr.setTexture(texture);
        }
		virtual void draw() {}
		sf::Vector2<float> offset() { 
			sf::Vector2<float> pos = spr.getPosition();
			// danger - still called if there's no follow
			sf::Vector2<float> cntr(pos.x-800/2/*+follow.w/2*/, pos.y-600/2/*+follow.h/2*/);
			return cntr;
		}
		virtual void act() {
			camerafollow();
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
