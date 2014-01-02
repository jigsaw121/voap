class Ship: public MovingObj {
	public:
		Module* m1, m2;
		double turn;
		
		explicit Ship(): MovingObj() {
		}
		virtual void specs() {
			speed=1.0;
			slow=0.1;
			grav=0.1;
			turn=0.4;
		}
		virtual void init() {
			types stype;
			stype = SHIP_TYPE;
			type = stype;
		}
		virtual Interactive* spawn() {
			return new Ship();
		}
		virtual void move();
		virtual void act();
		virtual void bump();
}