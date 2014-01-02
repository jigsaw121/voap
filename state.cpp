State::add(Interactive* obj) {
	introbuffer.push_back(obj);
}
void State::add2() {
	// called every frame, introbuffer.size() can be zero and this is skipped
	while (introbuffer.size()) {
		objects.push_back(introbuffer.back());
		introbuffer.pop_back();
	}
}
State::remove(Interactive* obj) {
	erasebuffer.push_back(obj);
}
void State::remove2() {
	// called every frame, erasebuffer.size() can be zero and this is skipped
	int i,f;
	//for (i=erasebuffer.begin(),i<erasebuffer.end(),i++) {
	while (erasebuffer.size()) {
		// or last element for faster removes
		// assume it's not there several times
		f = objects.find(erasebuffer.back());
		if (f == -1) {
			// wut?
			erasebuffer.pop_back();
			continue;
		}
		objects.erase(objects.begin()+f);
		// not necessarily deleted
		//delete erasebuffer.back();
		erasebuffer.pop_back();
	}
}
int State::mstime() {
	sf::Time elapse = clock.getElapsedTime();
	return elapse.asMilliseconds();
}