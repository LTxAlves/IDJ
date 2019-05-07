#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime) :    Component(associated),
                                                                                                                    distanceLeft(maxDistance),
                                                                                                                    damage(damage){

    Sprite* bullet1 = (new Sprite(associated, sprite, frameCount, frameTime)); //sprite for bullet
    associated.AddComponent(bullet1); //adds bullet

    associated.angleDeg = angle; //saves angleto rotate sprite

    angle = angle * (PI/180); //from degrees to radians

    this->speed = Vec2(speed * cos(angle), speed * sin(angle)); //speed vector from polar form
    this->damage = damage; //saves damage
    this->distanceLeft = maxDistance; //saves distance left to move
}

void Bullet::Update(float dt){

    Vec2 distToMove = speed * dt; //which distance to movein a frame
    associated.box += distToMove; //moves box
    distanceLeft -= distToMove.Magnitude(); //updates distance left before destruction of bullet

    if(distanceLeft <= 0)
        associated.RequestDelete(); //deletes if moved what it was supposed to
}

void Bullet::Render(){

    //does nothing
}

bool Bullet::Is(string type){

    return !type.compare("Bullet");
}

int Bullet::GetDamage(){

    return damage;
}