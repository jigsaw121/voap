#include "layer2.hpp"

void Layer::start_camerafollow(Interactive* obj) {
	// starts camerafollowing this... in its own context
	follow = obj;
}
void Layer::camerafollow() {
	if (!follow) return;
	x += (follow->x-x);//*0.2;// + x)/2;
	y += (follow->y-y);//*0.2;// + y)/2;
}
