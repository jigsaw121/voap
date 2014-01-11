#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <SFML/Window.hpp>
#include "factory.hpp"

class Ship;
class State;
class Team;

class Player {
	// track stats and keycodes, deploy queue, etc.
	public:
        Team* team;
        Ship* ship;
		sf::Keyboard::Key lkey,rkey,fwdkey,backkey,skey,ckey;

		explicit Player() {}

		void set_keys();
		void set_ship(State*, Ship*);
};

class Team {
	public:
		std::vector<Player*> players;
		// when the factory is dead, the team loses
		Factory* fac;
		int id;

		explicit Team() {}
		void add_players(int);
};

// holds the settings, state of a match
class Config {
	public:
		// teams have a factory, player settings for ship control
		std::vector<Team*> teams;

		explicit Config() {}
};

#endif
