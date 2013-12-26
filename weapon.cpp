#include <iostream>
#include <math.h>
#include "weapon.hpp"

Bullet::Bullet(Ship* _host) {
    host = _host;
    dir = _host->dir;
    speed = 6;
    dmg = 1;
    x = _host->x+16; y = _host->y+16;
    set_width();
}
void Bullet::init() {
    set_width();

    img.Create(w, h, sf::Color(196, 128, 196, 255));
    img.SetSmooth(false);
    spr.SetImage(img);
}
Bullet::~Bullet() {
}

void Bullet::move() {
    // different types of movement for soem weapons
    // but collision checking is reusable
    if (speed==0) {
        return;
    }
    x -= cos(dir)*speed;
    y -= sin(dir)*speed;

    while (bump()) {
        // would fizzle
        // maybe change the fizzle function (if no flag booleans)
        // or just check on whether speed is 0
        x += cos(dir);
        y += sin(dir);
        speed = 0;
    }
    //std::cout<<"bullet at "<<x<<", "<<y<<"\n";
}
bool Bullet::bump() {
    // for objects with x,y,w,h
    int ox, oy;
    sf::Color c;
    ParallaxLayer* l = (host->voap->art->get_active_layer());
    sf::Vector2<float> pos = l->spr.GetPosition();
    for (ox=0; ox<w; ox++) {
        for (oy=0; oy<h; oy++) {
            c = l->spr.GetPixel(x+ox, y+oy);
            if (c.a != 0 && (c.r!=0 || c.g!=0 || c.b!=0)) {
                return true;
            }
        }
    }
    return false;
}
void Bullet::act() {
    move();
    //fizzle();
}
void Bullet::draw() {
    sf::Vector2<float> pos = host->voap->art->get_active_layer()->surface()->GetPosition();
    spr.SetPosition(pos.x+x, pos.y+y);
    host->voap->Scr.Draw(spr);
    //fizzle();
}
bool Bullet::hit() {
    Ship* s = host->bullet_collide(x,y);
    if (s) {
        s->damage(dmg);
        s->push(2, dir);
        return true;
    }
    return false;
}
bool Bullet::oop() {
    //level width, level height should be in settings or gm
    //test values for now
    return (x<= -w || x>=2048 || y<= -h || y>=2048);
}
bool Bullet::fizzle() {
    return oop() || hit();
}

Weapon::Weapon() {
    //host = _host;
    id = "generic weapon";
}
Weapon::~Weapon() {
    std::cout<<"fizz\n";

    int i, c=0;
    Bullet* b;

    for (i=bullets.size()-1; i>=0; i--) {
        b = bullets[i];
        bullets.pop_back();
        delete b;
        c++;
    }
    if (c) {
        std::cout<<"fizzled "<<c<<" bullets\n";
    }
}
void Weapon::init() {
    std::cout<<"weapon initialization\n";
}
void Weapon::shoot() {
    if (cooldown == 0) {
        bullets.push_back(new Bullet(host));
        bullets.back()->init();
        std::cout<<id<<" shoots ("<<bullets.size()<<" bullets)\n";
        cooldown = maxcool;
    }
}
void Weapon::bullet_mgmt() {
    unsigned int i = 0;
    Bullet* b;
    /* easier to do bullet checking from the weapon
     * can pop items from bullets instantly
     * (no need for "hospice" list)
     */
    while (i<bullets.size()) {
        b = bullets[i];
        b->act();

        if (b->fizzle()) {
            std::cout<<"bullet fizzled\n";
            bullets.erase(bullets.begin()+i);
            delete b;
        }
        else {
            // only move forward if nothing was erased
            i++;
        }
    }
}
void Weapon::act() {
    bullet_mgmt();

    if (cooldown > 0)
        cooldown--;
}
void Weapon::bullet_draw() {
    unsigned int i;
    for (i=0; i<bullets.size(); i++) {
        bullets[i]->draw();
    }
}
void Weapon::draw() {
    bullet_draw();
}
pos Weapon::bullet_pos(double cx, double cy, double angle, double dist) {
    /*         p
     *         | xdist
     * c-------|
     *   ydist
     */
    // can recursively calculate more complex targets
    pos p;
    p.x = cx; p.y = cy;

    p.x += cos(angle)*dist;
    p.y += sin(angle)*dist;

    return p;
}

Rockets::Rockets(Ship* _host) {
    host = _host;
    id = "rocket launcher";
    maxcool = 36;
    cooldown = maxcool;
    init();
}
void Rockets::init() {
    std::cout<<id<<"\n";
}
void Rockets::shoot() {
    if (cooldown == 0) {
        bullets.push_back(new Rocket(host));
        bullets.back()->init();

        std::cout<<id<<" shoots ("<<bullets.size()<<" bullets)\n";
        cooldown = maxcool;
    }
}

MineDrop::MineDrop(Ship* _host) {
    host = _host;
    id = "mine dropper";
    maxcool = 64;
    cooldown = maxcool;
    init();
}
void MineDrop::init() {
    std::cout<<id<<"\n";
}
void MineDrop::shoot() {
    if (cooldown == 0) {
        bullets.push_back(new Mine(host));
        bullets.back()->init();

        std::cout<<id<<" drops mine ("<<bullets.size()<<" mines)\n";
        cooldown = maxcool;
    }
}

LaserSpray::LaserSpray(Ship* _host) {
    host = _host;
    id = "laser spray";
    maxcool = 4;
    cooldown = maxcool;
    init();
}
void LaserSpray::init() {
    std::cout<<id<<"\n";
}

Knocker::Knocker(Ship* _host) {
    host = _host;
    id = "knocker";
    maxcool = 12;
    cooldown = maxcool;
}
void Knocker::init() {
    std::cout<<id<<"\n";
}
void Knocker::shoot() {
    if (cooldown == 0) {
        pos p;
        p = bullet_pos(host->x+16, host->y+16, host->dir-0.785, 4);
        bullets.push_back(new KnockerBullet(host, &p, host->dir+0.02));
        bullets.back()->init();

        p = bullet_pos(host->x+16, host->y+16, host->dir+0.785, 4);
        bullets.push_back(new KnockerBullet(host, &p, host->dir-0.02));
        bullets.back()->init();

        std::cout<<id<<" shoots ("<<bullets.size()<<" bullets)\n";
        cooldown = maxcool;
    }
}

KnockerBullet::KnockerBullet(Ship* _host, pos* p, double _dir): Bullet(_host) {
    host = _host;
    x = p->x; y = p->y;
    dir = _dir;
    speed = 8;
    dmg = 4;
}
bool KnockerBullet::hit() {
    Ship* s = host->bullet_collide(x,y);
    if (s) {
        s->damage(dmg);
        s->push(2, dir);
        return true;
    }
    return false;
}

Rocket::Rocket(Ship* _host): Bullet(_host), Explosive() {
    accel = &Rocket::speeddown;
}
void Rocket::init() {
    set_width();

    img.LoadFromFile("rockit.png");
    img.SetSmooth(false);
    spr.SetImage(img);
    spr.Rotate((3.14159/2-dir)*180/3.14159);
    float spr_w=spr.GetSize().x/2, spr_y=spr.GetSize().y/2;
    spr.SetCenter(spr_w, spr_y);
}
bool Rocket::hit() {
    Ship* s = host->bullet_collide(x,y);
    if (s) {
        s->damage(dmg);
        // get angle? for knockback at least
        // push could set forced tangent instead
        s->push(2+speed/8, dir);
        std::cout<<"kaboom!\n";
        host->voap->gm->blow_up(x,y);
        // knockback (careful with recursion)
        // on next frame, other explosives will collide
        // host->voap->gm->blow_up(x,y);
        // call explosions from destructor
        // ensures not colliding with self
        // & no need to copy for virtual functions like explode()
        return true;
    }
    return false;
}

Mine::Mine(Ship* _host): Bullet(_host), Explosive() {
    //accel = &Rocket::speeddown;
}
void Mine::init() {
    set_width();

    img.Create(w, h, sf::Color(196, 128, 196, 255));
    img.SetSmooth(false);
    spr.SetImage(img);
}
bool Mine::hit() {
    Ship* s = host->bullet_collide(x,y);
    if (s) {
        s->damage(dmg);
        // get angle? for knockback at least
        // push could set forced tangent instead
        s->push(12, dir);
        std::cout<<"kaboom!\n";
        host->voap->gm->blow_up(x,y);
        // knockback (careful with recursion)
        // on next frame, other explosives will collide
        // host->voap->gm->blow_up(x,y);
        // call explosions from destructor
        // ensures not colliding with self
        // & no need to copy for virtual functions like explode()
        return true;
    }
    return false;
}


void Rocket::move() {
    // different types of movement for soem weapons
    // but collision checking is reusable
    if (speed==0) {
        return;
    }
    (this->*accel)();
    x -= cos(dir)*speed;
    y -= sin(dir)*speed;

    while (bump()) {
        // would fizzle
        // maybe change the fizzle function (if no flag booleans)
        // or just check on whether speed is 0
        x += cos(dir);
        y += sin(dir);
        speed = 0;
    }
    //std::cout<<"bullet at "<<x<<", "<<y<<"\n";
}
//template <class T>
//void Bullet::blast(T* src) {
//    /* laser behavior: do nothing
//     * otherwise, check hits if not target
//     * interesting things might happen, like two rockets colliding
//     */
//}
/*template <class T>
void Weapon::blast(T* src) {
    // weapon might be destroyed by the blast
    int i;
    for (i=0; i<bullets.size(); i++) {
        bullets[i]->blast(src);
    }
}*/
void Weapon::explode(Explosion* src) {
    unsigned int i = 0; Bullet* b;

    while (i<bullets.size()) {
        b = bullets[i];
        if (b->explode(src)) {
            bullets.erase(bullets.begin()+i);
            delete b;
        }
        else {
            i++;
        }
    }
}
bool Rocket::explode(Explosion* e) {
    return e->in_range(x,y);
}
