class State {
	public:
		int exitflag = 0;
		sf::Clock clock;
		std::vector<Interactive*> objects;
		std::vector<Interactive*> introbuffer;
		std::vector<Interactive*> erasebuffer;

		explicit State() { /*clock.start();*/ }

		void add(Interactive*);
		void add2();
		void remove(Interactive*);
		void remove2();
		int mstime();
		virtual bool mainloop();
}