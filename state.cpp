State::add(Interactive* obj) {
	introbuffer.push_back(obj);
}
State::remove(Interactive* obj) {
	erasebuffer.push_back(obj);
}
void State::add2() {
	// called every frame, introbuffer.length can be zero and this is skipped
	while (introbuffer.length) {
		objects.push_back(introbuffer[0]);
		introbuffer.pop(0);
	}
}
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
