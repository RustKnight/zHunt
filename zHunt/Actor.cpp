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
	
	double angle = atan2(dy,dx);
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
	old_distance = mouse_to_player_distance;
	facing = facings(lookAtMouse());


	if (pge->GetKey(olc::UP).bHeld)
		location.y -= fElapTm * speed;
	if (pge->GetKey(olc::DOWN).bHeld)
		location.y += fElapTm * speed;
	if (pge->GetKey(olc::LEFT).bHeld)
		location.x -= fElapTm * speed;
	if (pge->GetKey(olc::RIGHT).bHeld)
		location.x += fElapTm * speed;

	
	if (pge->GetKey(olc::P).bPressed) {
		renderer.request_animation(PICK_UP, 0, 0, 0, 0, 4.5f);
	}
	
	else if (pge->GetKey(olc::K).bPressed) {
		renderer.request_animation(SMOKE, 0, 0, 1, 1, 1.0f);
	}

	else if (pge->GetKey(olc::C).bPressed) {
		renderer.request_animation(CLIMB, 0, 0, 1, 1, 2.5f);
	}

	//{ INTERRUPTABLE, REVERSED, LOOP, BACK_FORTH }

	if (old_location != location) {
		mouse_to_player_distance.x = pge->GetMouseX() - location.x;
		mouse_to_player_distance.y = pge->GetMouseY() - location.y;

		Vec2 direction = location - old_location;
		
		
		if ( (direction.GetNormalized().x > 0 && mouse_to_player_distance.GetNormalized().x > 0) || (direction.GetNormalized().y > 0 && mouse_to_player_distance.GetNormalized().y > 0)  || (direction.GetNormalized().x < 0 && mouse_to_player_distance.GetNormalized().x < 0) || (direction.GetNormalized().y < 0 && mouse_to_player_distance.GetNormalized().y < 0)) {
			speed = 70.0f; cout << speed << endl;
			renderer.request_animation(WALK, 1, 0, 0, 0, 6.5f);
		}
		else {
			speed = 45.0f; cout << speed << endl;
			renderer.request_animation(WALK, 1, 1, 0, 0, 4.0f);
		}
	}
	else 
		renderer.request_animation(IDLE, 1, 0, 1, 1, 1.5f);
	


	renderer.update_and_play(eTime, location, facing);
}	




