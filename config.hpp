// holds the settings, state of a match
class Config {
	public:
		// teams have a factory, player settings for ship control
		std::vector<Team*> teams;

		explicit Config() {}
};

class Team {
	public:
		std::vector<Player*> players;
		// when the factory is dead, the team loses
		Factory* fac;

		explicit Team() {}
};

class Player {
	// track stats and keycodes, deploy queue, etc.
	public:
		sf::Keyboard::Key lkey,rkey,fwdkey,backkey,skey,ckey;

		explicit Player() {}

		void set_keys();
};