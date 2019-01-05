#include "Actor.h"



void Actor::load_spr_sheet(std::string adrs)
{
	spr = new olc::Sprite{ adrs };
	renderer.get_spr_ptr(spr);
}




int Actor::lookAtMouse()
{
#define PI 3.14159265

	// we determine the vector between the mouse position and the location of the character
	float dx = pge->GetMouseX() - location.x;
	float dy = pge->GetMouseY() - location.y;
	
	float angle = atan2(dy,dx);
	angle = roundf (angle / ((2 * PI) / 8) + 4);
	if (angle == 8)
		angle = 0;

	switch (int (angle) ) {
		//N = 2, NE = 3, E = 4, SE = 5, S = 6, SW = 7, W = 0, NW = 1,
	case 0 :
		angle = 6;
		break;
	case 1:
		angle = 7;
		break;
	case 2:
		angle = 0;
		break;
	case 3:
		angle = 1;
		break;
	case 4:
		angle = 2;
		break;
	case 5:
		angle = 3;
		break;
	case 6:
		angle = 4;
		break;
	case 7:
		angle = 5;
		break;
	}

	return angle;
}



void Actor::update(float fElapTm)
{
	eTime = fElapTm;
	old_location = location;
	facing = facings(lookAtMouse());

	renderer.anim_update();
	renderer.update(eTime, location, facing);

	if (pge->GetKey(olc::UP).bHeld)
		location.y -= fElapTm * speed;
	if (pge->GetKey(olc::DOWN).bHeld)
		location.y += fElapTm * speed;
	if (pge->GetKey(olc::LEFT).bHeld)
		location.x -= fElapTm * speed;
	if (pge->GetKey(olc::RIGHT).bHeld)
		location.x += fElapTm * speed;

	if (pge->GetKey(olc::W).bPressed) {
		int ac = int(action);
		ac++;
		action = actions(ac);
	}

	if (pge->GetKey(olc::S).bPressed) {
		int ac = int(action);
		ac--;
		action = actions(ac);
	}

	if (pge->GetKey(olc::P).bPressed) {
		renderer.anim_que(PICK_UP, 0);
	}

	else if (pge->GetKey(olc::K).bPressed) {
		renderer.anim_que(SMOKE, 0);
	}

	else if (old_location != location) {
		renderer.anim_que(WALK, 1);
		//done_playing = true;  dirty way of stoping a play_once animation
	}

	else
		renderer.anim_que(IDLE, 1);

}	




