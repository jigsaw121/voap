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
	
Ship::leavefac() {
	if (up) {
		act = defact;
		act();
	}
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

// any weapon creates a prototype of itself (overridden)
Weapon* Weapon::register_fac() {
	return new Weapon();
}

template <class T>
void Level::remove(T* obj) {
	erasebuffer.push_back(T);
}

template <class T>
void Level::remove2() {
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

