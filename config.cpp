#include "config.hpp"
#include "ship2.hpp"

void Player::set_keys() {
	// default values for now
	// changed with an options interface (persistent player data)
	lkey = sf::Keyboard::Left;
	rkey = sf::Keyboard::Right;
	fwdkey = sf::Keyboard::Up;
	backkey = sf::Keyboard::Down;
	skey = sf::Keyboard::Z;
	ckey = sf::Keyboard::X;
}
void Player::set_ship(State* _state, Ship* _ship) {
    ship = _ship;
    // get a valid spawn pos here
    ship->initall(_state,0,0);
    ship->player_init(this);
    ship->team = team;
}

void Team::add_players(int n) {
    // don't care about negative n, probably no option to create that
    // just pushes an anonymous player with default configs
    // expected to be config'd later
    players.push_back(new Player());
    players.back()->set_keys();
    players.back()->team = this;
    if (n>1) add_players(n-1);
}
