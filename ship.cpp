#include "ship.hpp"

Tangent::Tangent(double _dir, double _acc) {
    dir = _dir;
    acc = _acc;
}

Ship::Ship(VoaP* _voap, int _x, int _y) {
    dir = 1.57;
    voap = _voap;
    speed = 3;
    maxhp = 32;
    hp = maxhp;
    minerals = 0;
    grav = 0;
    gacc = 0.04;
    respawn = voap->st->respawn;
    // empty tangent
    tng = new Tangent(dir, 0);
    // "forced" tangent
    push_tng = new Tangent(dir, 0);

    //img.Create(32, 32, sf::Color(128, 128, 128, 255));
    img.LoadFromFile("sippi.png");
    img.SetSmooth(false);
    spr.SetImage(img);
    spr.SetCenter(0.5, 0.5);
    // p_num, keycodes, assigned when gm hands out player order

    w1 = new Knocker(this);
    w2 = new Rockets(this);
    set_pos(_x, _y);
}
Ship::~Ship() {
    //delete w;
    delete w1;
    delete w2;
    delete tng;
    delete push_tng;
    std::cout<<"hnnng\n";
}
void Ship::move(int fwd) {
    double dx, dy;
    grav = 0;

    dx = cos(dir)*speed*fwd;
    dy = sin(dir)*speed*fwd;
    x -= dx;
    y -= dy;
    tng = new Tangent(dir+((fwd<0)*3.14159),speed/2);
    if (voap->gm->bump(this)) {
        x += dx;
        y += dy;
        tng = new Tangent(dir+3.14159,speed/2);
        return;
    }
    layer_update(dx, dy);
    std::cout<<"Ship "<<p_num<<" moving, at "<<x<<", "<<y<<"\n";
    //std::cout<<"bullet at "<<x<<", "<<y<<"\n";
}
void Ship::push(double amt, double pdir) {
    /* for gradual movement, store vectors, calculate and decrease them every frame
     * the problem is meaningful units
     */
    push_tng = new Tangent(pdir, amt);
    grav = 0;
}
void Ship::weapon_draw() {
    // draw weapons & make them draw their bullets
    w1->draw();
    w2->draw();
}
void Ship::draw(Layer* l) {
    //if (l->surface() != NULL) {
        // maybe a bglayer has *somehow* become active
        //l->surface()->Draw(spr);
    sf::Vector2<float> pos = voap->art->get_active_layer()->surface()->GetPosition();
    spr.SetPosition(pos.x+x, pos.y+y);
    voap->Scr.Draw(spr);
    weapon_draw();
    //}
}
void Ship::layer_update(double dx, double dy) {
    if (view == NULL) {
        return;
    }

    view->layer_update(dx, dy);
}
void Ship::tangent_move(Tangent* t) {
    if (t->acc==0) {
        return;
    }
    double dx, dy;
    dx = cos(t->dir)*t->acc;
    dy = sin(t->dir)*t->acc;
    x -= dx;
    y -= dy;
    layer_update(dx, dy);

    t->slow();
}
void Ship::gravity() {
    y+=grav;
    layer_update(0, -grav);
    grav += gacc;

    while (voap->gm->bump(this)) {
        y--;
        layer_update(0, 1);
        grav = 0;
    }
}
void Ship::input() {
    /* if this particular ship's key combination was pressed,
     * move accordingly
     */
    if (voap->Scr.GetInput().IsKeyDown(keys->up)) {
        move(1);
        //std::cout<<"Ship "<<p_num<<" moving up, at "<<x<<", "<<y<<"\n";
    }
    else if (voap->Scr.GetInput().IsKeyDown(keys->down)) {
        move(-1);
        //y += speed;
        //std::cout<<"Ship "<<p_num<<" moving down, at "<<x<<", "<<y<<"\n";
        //layer_update(0.0, -speed);
    }
    else {
        // carry on to whatever direction it was going
        tangent_move(tng);
        if (voap->gm->bump(this)) {
            tng = new Tangent(tng->dir+3.14159,tng->acc);
            tangent_move(tng);
        }
    }

    tangent_move(push_tng);
    if (voap->gm->bump(this)) {
        push_tng = new Tangent(push_tng->dir+3.14159,push_tng->acc);
        tangent_move(push_tng);
    }

    gravity();

    if (voap->Scr.GetInput().IsKeyDown(keys->left)) {
        dir -= 0.08;
        spr.Rotate(0.08*180/3.14159);
        float spr_w=spr.GetSize().x/2, spr_y=spr.GetSize().y/2;
        //std::cout<<"Ship "<<p_num<<" moving left, at "<<x<<", "<<y<<"\n";
        //layer_update(speed, 0.0);
    }
    if (voap->Scr.GetInput().IsKeyDown(keys->right)) {
        dir += 0.08;
        spr.Rotate(-0.08*180/3.14159);
        float spr_w=spr.GetSize().x/2, spr_y=spr.GetSize().y/2;
        //std::cout<<"Ship "<<p_num<<" moving right, at "<<x<<", "<<y<<"\n";
        //layer_update(-speed, 0.0);
    }
}
/*void Ship::set_weapon() {
    w = new Weapon();
}*/
int Ship::act() {
    input();
    shoot();
    w1->act();
    w2->act();
    return 0;
}
void Ship::shoot() {
    if (voap->Scr.GetInput().IsKeyDown(keys->shoot1)) {
        w1->shoot();
    }
    if (voap->Scr.GetInput().IsKeyDown(keys->shoot2)) {
        w2->shoot();
    }
}
Ship* Ship::bullet_collide(double hx, double hy) {
    // does my bullet collide with anyone else's
    int i;
    Ship* s;
    for (i=0; i<voap->gm->player_amt(); i++) {
        // don't bump with own bullets...
        // don't compare with p_num because of possible junkyard ships
        s = voap->gm->get_player(i);
        if (s != this) {
            if (s->collide(hx, hy)) {
                std::cout<<"bump\n";
                return s;
            }
        }
    }

    return NULL;
}
bool Ship::collide(double hx, double hy) {
    /* could use a hitbox entity
     * going with magic numbers before different ship types
     * assume bullet width 4, ship width 32
     */
    return ( ((hx >= x && hx < x+32) ||
              (hx+4 >= x && hx+4 < x+32)) &&
             ((hy >= y && hy < y+32) ||
              (hy+4 >= y && hy+4 < y+32)) );
}
void Ship::damage(double dmg) {
    // override for side effects
    hp -= dmg;
}

bool Ship::alive() {
    /* check after processing
     * to avoid race conditions
     */
    return hp>0;
}
void Ship::gather(int _value) {
    minerals += _value;
}
std::vector<Mineral*> Ship::generate_minerals() {
    std::vector<Mineral*> belt;
    int mineral_count = 1280;
    while (mineral_count > 0) {
        // split off a chunk
        // use variable, random sizes
        belt.push_back(new Mineral(voap,x,y,160));
        mineral_count -= 160;
    }
    return belt;
}

//template <class T>
//void Ship::blast(T* src) {
//    /* if within radius, and not the object hit by the explosive,
//     * take damage from source
//     * check subs nonetheless
//     */
//    if (false) {
//        // implement radius function
//        damage(src->dmg);
//    }
//
//    w1->blast(src);
//    w2->blast(src);
//}

void Ship::explode(Explosion* src) {
    w1->explode(src);
    w2->explode(src);
    // take damage etc
    // cleanup for broken ships happens without returns
}
