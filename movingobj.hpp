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
		virtual void push(double _dx, double _dy) { dx+=_dx; dy+=_dy; }
}
