#include "Bullet.h"
#include "Sprite.h"
#include "Collider.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount, float frameTime, bool targetsPlayer) :   Component(associated),
                                                                                                                                                                        targetsPlayer(targetsPlayer),
                                                                                                                                                                        distanceLeft(maxDistance),
                                                                                                                                                                        damage(damage){

    Sprite* bullet2 = (new Sprite(associated, sprite, frameCount, frameTime)); //sprite for bullet
    Collider* bulletCollider = (new Collider(associated)); //collider for bullet
    associated.AddComponent(bullet2); //adds bullet sprite
    associated.AddComponent(bulletCollider); //adds bullet collider

    associated.angleDeg = angle; //saves angle to rotate sprite

    angle = angle * (DEGTORAD); //from degrees to radians

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

void Bullet::NotifyCollision(GameObject& other){

    if((other.GetComponent("Alien") != nullptr && !targetsPlayer) || (other.GetComponent("Minion") != nullptr && !targetsPlayer) || (other.GetComponent("PenguinBody") != nullptr && targetsPlayer))
        associated.RequestDelete();
}