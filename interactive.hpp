class Interactive {
	public:
		State* gm;
		double x,y,w,h;
		int type;
		
		sf::Image img;
        sf::Sprite spr;
		
		explicit Interactive(State* _gm, double _x, double _y) { 
			initall(_gm,_x,_y);
		}
		~Interactive() {
			delete img;
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
			img.Create(w, h, sf::Color(128, 128, 128, 255));
			img.SetSmooth(false);
			spr.SetImage(img);
			spr.SetCenter(0.5, 0.5);
		}
		
		void skip() {}
		
		virtual Interactive* spawn() {
			return new Interactive();
		}
		virtual void move() {}
		virtual void act() {}
		virtual void draw() {
			// really? am I supposed to do it like this?
			sf::Vector2<float> pos = get_active_layer()->get_pos();
			spr.SetPosition(pos.x+x, pos.y+y);
			screen().Draw(spr);
		}
		virtual void remove() {
			// dying would also have a consequence of delete this; at gm's remove2()
			// but it can't be automatically implemented since sometimes temporary deactivation is useful
			gm.remove(this);
		}
		
		virtual bool collide();
		std::vector<Interactive*> find(int ftype);
		std::vector<Interactive*> mergevectors(std::vector<Interactive*> a, std::vector<Interactive*> b);
		std::vector<Interactive*> Interactive::collidetype(int type);
		std::vector<Interactive*> Interactive::collidetypes(std::vector<int> types);
}