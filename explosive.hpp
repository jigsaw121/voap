#ifndef EXPLOSIVE_H
#define EXPLOSIVE_H

class Explosive {
    public:
        explicit Explosive() {}
        ~Explosive() {}
        void knockback();
        bool blast_dmg();
};

class Explosion {
    public:
        double x, y;
        double radius;
        Explosion(double _x, double _y) { x=_x;y=_y;radius = 30.0; }
        ~Explosion() {}

        bool in_range(double cx, double cy) { return abs(x-cx)*abs(x-cx) + abs(y-cy)*abs(y-cy) <= radius; }
};

#endif
