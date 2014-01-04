#include <SFML/Graphics.hpp>
#include "interactive.hpp"

class Layer: public Interactive {
	public:
        Layer(State* _gm, double _x, double _y): Interactive(_gm,_x,_y) {}
		virtual void draw() {
		}
};

class BGLayer: public Layer {
	public:
        BGLayer(State* _gm, double _x, double _y): Layer(_gm,_x,_y) {}
		virtual void draw() {
			screen()->clear(sf::Color(160,60,40));
		}
};
