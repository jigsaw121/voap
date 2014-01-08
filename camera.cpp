#include "camera.hpp"

void Camera::camerafollow() {
    if (!follow) return;
    x += ((follow->x)-x)*lerp;//*0.2;// + x)/2;
    y += ((follow->y)-y)*lerp;//*0.2;// + y)/2;
}
