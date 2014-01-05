#include "camera.hpp"

void Camera::camerafollow() {
	if (!follow) return;
	x += (follow->x-x)*0.2;//*0.2;// + x)/2;
	y += (follow->y-y)*0.2;//*0.2;// + y)/2;
}
