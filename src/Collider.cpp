#include "Collider.h"
#include "GameObject.h"
#include "Constants.h"

#ifdef DEBUG
    #include "Camera.h"
    #include "Game.h"

    #include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) :   Component(associated),
                                                                        scale(scale),
                                                                        offset(offset){


}

void Collider::Update(float){

	box = associated.box * scale;
    box.CenterAt(associated.box.CenterPoint() + offset.GetRotated(associated.angleDeg * DEGTORAD));
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center(box.CenterPoint());
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated(-associated.angleDeg * DEGTORAD) + center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};

	int x1 = point.x;

	point = (Vec2(box.x + box.w, box.y) - center).GetRotated(-associated.angleDeg * DEGTORAD) + center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};

	int x = point.x;
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated(-associated.angleDeg * DEGTORAD) + center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};

	points[1].x = points[2].x;
	points[2].x = x;
	
	point = (Vec2(box.x, box.y + box.h) - center).GetRotated(-associated.angleDeg * DEGTORAD) + center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	points[0].x = points[3].x;
	points[4].x = points[3].x;
	points[3].x = x1;

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(string type){

    return !type.compare("Collider");
}

void Collider::SetScale(Vec2 scale){

    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset){

    this->offset = offset;
}