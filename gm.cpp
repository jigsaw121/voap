#include "gm.hpp"

bool GM::mainloop() {
	if (exitflag) return false;

	int st = mstime(); double frame = 1000/60.0;

	if (lag<0) lag=0;
	double _lag = lag;
	// warn/abort/skip drawing if lag gets too high
	int i;
	//for (i=objects.begin(); i<objects.end(); i++) objects[i]->move();
	for (i=0; i<objects.size(); i++) objects.at(i)->act();
	// if drawing is taking too long (lag piled up from a couple of frames),
	// might just skip a frame
	if (lag<frame*3) {
		for (i=0; i<objects.size(); i++) {
			objects.at(i)->draw();
		}
	}

	// actually remove/add from buffers
	remove2(); add2();

	// how much we're lagging from the desired fps
	// if negative (=we're ahead), gets fixed when setting _lag next frame
	lag += mstime()-st - frame;

	// if we're ahead, let's just wait
	// note that _lag is at least 0
	while (mstime()-st < frame-_lag)
		;

	return true;
}
