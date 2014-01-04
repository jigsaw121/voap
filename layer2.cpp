void Layer::start_camerafollow(Interactive* obj) {
	// starts camerafollowing this... in its own context
	follow = obj;
}
void Layer::camerafollow() {
	if (!follow) return;
	offset_x = (follow.x + offset_x)/2;
	offset_y = (follow.y + offset_y)/2;
}