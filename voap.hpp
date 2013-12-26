#ifndef VOAP_H
#define VOAP_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "settings.hpp"
#include "game.hpp"
#include "artist.hpp"

class Artist;
class GameMaster;

class VoaP {
    /* A "master" class */
    public:
        VoaP();
        ~VoaP();
        int act();

        bool esc;
        int frame;

        void play_init();
        int play();
        void play_end();
        void draw();

        sf::RenderWindow Scr;
        sf::RenderWindow win;
        sf::Event event;

        Settings* st;
        GameMaster* gm;
        Artist* art;
};

#endif
