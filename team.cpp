#include "team.hpp"

Ship* Team::next_up() {
    if (queue.size()==0) {
        // rely on players to set queue -> lose on no queue?
        // when factory is destroyed, endgame mode is set
        // if everyone is destroyed before the enemy team loses, gg
        return NULL;
    }
    Ship* s;
    s = queue.back();
    queue.erase(queue.end()-1);
    // or set a new default ship into back on queue?
    return s;
}
