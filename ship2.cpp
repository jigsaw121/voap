double rad(double n) {
	return n*180/3.14159;
}

void Ship::move() {
	if (lkey) {
		angle -= turn;
		spr.Rotate(rad(turn));
	}
	if (rkey) {
		angle += turn;
		spr.Rotate(-rad(turn));
	}
	
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
	if (/* wallbump */) { x -= dx; y -= dy; }
	if (/* shipbump */) { x -= dx; y -= dy; }
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