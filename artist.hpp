#ifndef ARTIST_H
#define ARTIST_H

#include "vector"
#include "layer.hpp"

class Artist {
    /* layer 1 just fills the screen with a solid color,
     * layer 2 is for parallax background decorations,
     * layer 3 is immobile in relation to solids,
     * layer 4 is for reading solids (non-transparent pixels are solid)
     * layer 5 is drawn on top of the scene (fog etc.)
     * could all inherit from a Layer class, with different behaviour
     * have to interact with the player to render relative positions
     * split-screen complicates things further
     * -> could use new artist for each sub-screen
     * with their own players to interact with
     * but sharing the layers
     * gm could contain the layers
     */
    std::vector<Layer*> layers;
    void layer_process();

    public:
        Artist(VoaP*);
        ~Artist();

        VoaP* voap;

        void act();
        void display();
        void layer_update(double, double);
        ParallaxLayer* get_active_layer();
};

#endif
