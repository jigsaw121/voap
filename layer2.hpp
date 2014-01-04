class Layer: public Interactive {
	public:
		virtual void draw() {
		}
};

class BGLayer: public Layer {
	public:
		virtual void draw() {
			screen()->clear(sf::Color(160,60,40));
		}
};