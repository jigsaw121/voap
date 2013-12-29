# Pseudo-C++ in a Python file
# SO IT HAS COME TO THIS

class Interactive(object):
	def __init__(self):
		self.img = None

class Factory(Interactive):
	def __init__(self):
		super()
	int menu = 0;
	menus = std::vector<Menu*> gen_menus()
	std::vector<Menu*> Factory::gen_menus() {
		
	}
	void Factory::selection() {
		if (down) {
			menu++;
		}
	}
	
	int cap(int* n, int max) {
		if (*n<0) *n=0;
		if (*n>max) *n=max;
	}

	void Menu::remove() {
		//rewind to first menu, remove all subs recursively & free memory
	}
	
	void Menu::selection() {
		if (accept) {
			//add(options[index]);
			options[index]->behave();
			remove();
			return;
		}
		if (submenu && down) {
			switchto(submenu);
			return;
		}
		if (left) index--;
		if (right) index++;
		cap(&index, options.length);
	}


enum types {SHIP_TYPE=1, WEAPON_TYPE, MINERAL_TYPE};

class Interactive {
	public:
		double x,y;
		
		explicit Interactive() { init(); }
		~Interactive() {}
		virtual void init() {
			type = 0;
		}
		virtual Interactive* spawn() {
			return new Interactive();
		}
		virtual void move() {}
		virtual void act() {}
		void skip() {}
		virtual void draw() {}
}

class MovingObj: public Interactive {
	public:
		double dx,dy,angle,speed,slow,grav;
		
		explicit MovingObj(): Interactive() {
			dx=0.0; dy=0.0; angle=0.0; 
			specs();
		}
		virtual void specs() {
			speed=1.0;
			slow=0.1;
			grav=0.1;
		}
		virtual void move() {}
}

class Ship: public MovingObj {
	public:
		Module* m1, m2;
		double turn;
		
		explicit Ship(): MovingObj() {
			turn = 0.4;
		}
		virtual void specs() {
			speed=1.0;
			slow=0.1;
			grav=0.1;
		}
		virtual void init() {
			types stype;
			stype = SHIP_TYPE;
			type = stype;
		}
		virtual Interactive* spawn() {
			return new Ship();
		}
		virtual void move();
		virtual void act();
		virtual void bump();
}

void Ship::move() {
	if (lkey) angle -= turn;
	if (rkey) angle += turn;
	
	if (fwdkey) {
		dx += cos(angle)*speed; dy += sin(angle)*speed;
	}
	if (backkey) {
		dx /= slow*2; dy /= slow*2;
	}
	
	dx /= slow; dy /= slow;
	dy += grav;
	
	x += dx; y += dy;
}

void Ship::bump() {

}

void Ship::act() {
	move();
	bump();
}
	
Ship::leavefac() {
	if (up) {
		act = defact;
		act();
	}
}

/*
screw casts yo
void Factory::install(Interactive* obj) {
	// where to convert weapons to minerals?
	if (obj->type==MINERAL_TYPE) add_minerals(static_cast<*Mineral>(obj));
	else register(static_cast<*Weapon>(obj));
}
*/

void FacMenu::act() {
	// draw images of the options I guess
	// and select things and animate transitions when the selection changes 
}

FacMenu* FacMenu::add_option(std::string id, Interactive* cons, Factory* fact) {
	FacMenu* nxt = new FacMenu(fact, id);
	options.push_back(nxt);
	// event function called for onclick
	nxt->onclick = cons;
	// returned in case it needs extra modifications for events, etc.
	return nxt;
}
void Interactive::install(Factory* ignore) {
}
void Mineral::install(Factory* f) {
	f->minerals += value;
}
void Weapon::install(Factory* f) {
	// actually needs to push a blueprint/identifier of itself for duplication...
	// which smells like a factory pattern
	// let's just use the weapons' virtual method spawn()
	f->registered.push_back(this);
}
void Interactive::deploy(Factory* ignore) {
}
void Module::deploy(Factory* f) {
	// deploy to visitor ship
}
void Weapon::deploy(Factory* f) {
	// swap the factory user's weapon with this
	// (the old weapon can then be redeployed to someone else or converted to minerals)
	f->visitor->weapon()->install(f);
	f->visitor->change_weapon(this);
}
FacMenu* FacMenu::option(std::string getid) {
	// returns the facmenu with the matching id from its own options
}
void FacMenu::event_default() {
	// by default, a submenu will be entered
	// you've set the right index before coming here
	if (options.length==0) return;
	gm.remove(this);
	gm.add(options[index]);
}
void FacMenu::event_install() {
	onclick.install(fact);
}
void FacMenu::event_deploy() {
	onclick.deploy(fact);
}
void FacMenu::event_queue() {
	// construct ship from parts and push it to the stack for the next respawner
}

FacMenu* Factory::spawn_menu(Ship* s) {
	FacMenu* top = new FacMenu(this, "factory");
	FacMenu* tmp, tmp2; int i;
	
	top->add_option("queue", top, this);
	top->add_option("install", top, this);
	top->add_option("deploy", top, this);
	
	// set submenu selections
	tmp = top->option("install");
	for (i = s->cargo.begin(); i < s->cargo.end(); i++) {
		// installing does different things for minerals and module cargo like weapons
		tmp2 = tmp.add_option(s->cargo[i]->describe(), s->cargo[i], this);
		tmp2->event = tmp2->event_install;
	}
	tmp = top->option("deploy");
	for (i = s->cargo.begin(); i < s->cargo.end(); i++) {
		// only modules can be deployed (and have a meaningful deploy() method)
		if (!s->cargo->[i]->is_module()) continue;
		
		tmp2 = tmp.add_option(s->cargo[i]->describe(), s->cargo[i], this);
		tmp2->event = tmp2->event_deploy;
	}
	
	// the topmost menu will be activated first
	return top;
}

if (ship->collide(factory)) {
	ship->act = ship->leavefac;
	gm.add(factory->spawn_menu(player));
}

if (ship->collide(weapon)) {
	// weapons never merge
	ship->minerals.push_back(weapon);
	lvl.remove(weapon);
}

if (ship->collide(mineral)) {
	// minerals merge to the first item
	if (minerals.length>0 && minerals[0]->type==MINERAL_TYPE) {
		minerals[0]->value += mineral->value;
	}
	else minerals.insert(0, mineral);
}

// create install menus from ship's cargo (minerals in one bunch)

// to register weapon at factory
if (cargo->type==WEAPON_TYPE) {
	factory->weapons.push(cargo.register_fac())
}

Weapon* Interactive::register_fac() {
	return null;
}

class Module: public MovingObj() {
	// MovingObj because there'll be physical modules on ship drops
	// before that, they're not updated (and not added to gm)
	// alternatively, encapsulate them in a separate moving fragment...
	public:
		explicit Module(): MovingObj() {}
		virtual void move();
}
void Module::move() {
	// just falls until it hits something in bump()
	dx+=cos(angle);
	dy+=grav;
	y+=dy;
}
class Weapon: public Module() {
	public:
		explicit Weapon(): Module() {}
		virtual void shoot() {}
		virtual void act();
}
class Flamer: public Weapon() {
	public:
		explicit Flamer(): Weapon() {}
		virtual void shoot();
}
void Flamer::shoot() {
	// by default, shoots plain flames, spreading in slightly varied angle/speed
	// can also shoot sticky flames that follow an enemy ship around, dealing constant damage
}

class Rocket: public Explosive() {
	public:
		explicit Rocket(): Explosive() {}
}
void Rocket::move() {
	// behaviour: slow down at the start, then accelerate
	// note that speed starts out as negative
	double sp = abs(speed);
	cap(&sp, 16);
	dx += cos(angle)*sp;
	dy += sin(angle)*sp;
	
	speed+=0.1;
}

class TrailMod: public Module() {
	// attributes changed depending on ship
	public:
		explicit Weapon(): Module() {}
		virtual void act();
}
void TrailMod::act() {
	// module follows ship, constantly spawns trail atoms that block/hurt
	// trails disappear after a while
	// can be toggled on/off to save power
	gm.add(/* new trail of the current type at this pos */);
}

// any weapon creates a prototype of itself (overridden)
Weapon* Weapon::register_fac() {
	return new Weapon();
}

class Explosive: public MovingObj() {
	public:
		explicit Explosive(): MovingObj() {}
		void explode() {
			remove();
			gm.add(new Boom(/* at the same position with the same references */))
		};
}
void Explosive::bump() {
	// by default, explodes on collisions
	if (collide(/* any interactive type/walls, not itself etc. */)) {
		explode();
	}
}
class Bomb: public Explosive() {
	public:
		explicit Bomb(): Explosive() {
			// gets an initial push from the dropping ship
			// so even dy might be negative at the start
			// a grenade would be just a bomb with a stronger initial push, heh
		}
		virtual void move();
}
void Bomb::move() {
	// just falls until it hits something in bump()
	dx+=cos(angle);
	dy+=grav;
	y+=dy;
}
class Mine: public Explosive() {
	public:
		explicit Mine(): Explosive() {}
		// maybe a silly for it not to move since it inherits from MovingObj
		// but whatever man I ain't gonna make a disposable intermediate class
		// mines are disabled when the host dies
		// can also be rendered useless by other means
		virtual void move() {}
} 

class Boom: public Interactive() {
	public:
		explicit Boom(): Interactive() {}
		virtual void act();
}
void Boom::act() {
	if (collide(/*any type except for this one*/)) {
		// some types blow up when damaged, creating more booms on the next frames
		// could break walls too
		target.damage();
	}
}

class WallAmbassador: public Interactive() {
	// haha dese names man
	// basically an interface to handle wall collisions
	// -> collide with this instead of the image layers directly
	// an inherited version could destroy the walls on collision too
	// quadtrees and shiz whenever needed, even a couple of huge layers run smoothly right now
	public:
		explicit WallAmbassador(): Interactive() {}
}

template <class T>
void State::remove(T* obj) {
	erasebuffer.push_back(T);
}

template <class T>
void State::remove2() {
	// called every frame, erasebuffer.length can be zero and this is skipped
	int i,f;
	//for (i=erasebuffer.begin(),i<erasebuffer.end(),i++) {
	while (erasebuffer.length) {
		// or last element for faster removes
		// assume it's not there several times
		f = objects.find(erasebuffer[0]);
		if (f == -1) {
			// wut?
			erasebuffer.pop(0);
			continue;
		}
		objects.erase(objects.begin()+f,objects.begin()+f+1);
		delete erasebuffer[0];
		erasebuffer.pop(0);
	}
}

class State {
	public:
		std::vector<Interactive*> objects;
		std::vector<Interactive*> introbuffer;
		std::vector<Interactive*> erasebuffer;
		void add();
		void add2();
		void remove();
		void remove2();
		virtual void mainloop();
}

class GM: public State {
	// game states are a stack, this is the in-game one
	// when esc is pressed whenever you're here, it drops back into the menu
	// probably adds some listener object that can do anims for that etc.
	public:
		explicit GM(): State() {
		}
		virtual void mainloop();
}

bool GM::act() {

}

void GM::mainloop() {
	int i;
	//for (i=objects.begin(); i<objects.end(); i++) objects[i]->move();
	for (i=objects.begin(); i<objects.end(); i++) objects[i]->act();
	for (i=objects.begin(); i<objects.end(); i++) objects[i]->draw();
	
	// remove/add from buffers
	remove2();
	add2();
}