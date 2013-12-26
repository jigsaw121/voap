class Team {
    std::vector<Ship*> ships;   // set in menu, get from gm on init
    std::vector<Ship*> queue;

    public:
        Team();
        ~Team();

        int minerals;   // shared mineral pool
        // on respawn, this becomes a player's next ship
        Ship* next_up();
};
