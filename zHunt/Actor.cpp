#include "Actor.h"



void Actor::load_spr_sheet(std::string adrs)
{
	olc::Sprite* spr = new olc::Sprite{ adrs };
	vSpriteSheetPointers.push_back(spr);
}



Actor::facings Actor::lookAtMouse(){
#define PI 3.14159265

	// we determine the vector between the mouse position and the location of the character
	float dx = pge->GetMouseX() - ((location.x - camera_offset.x) * 128);
	float dy = pge->GetMouseY() - ((location.y - camera_offset.y) * 128);
//	pge->DrawLine(pge->GetMouseX(), pge->GetMouseY(), (location.x - camera_offset.x) * 128, (location.y - camera_offset.y) * 128, olc::RED);


	float angle = atan2(dy,dx);
	angle = (roundf (angle / ((2 * PI) / 8) + 4) );
	if (angle == 8)
		angle = 0;

	switch (int (angle) ) {
		//N = 2, NE = 3, E = 4, SE = 5, S = 6, SW = 7, W = 0, NW = 1,
	case 0 :
		angle = W;
		break;
	case 1:
		angle = NW;
		break;
	case 2:
		angle = N;
		break;
	case 3:
		angle = NE;
		break;
	case 4:
		angle = E;
		break;
	case 5:
		angle = SE;
		break;
	case 6:
		angle = S;
		break;
	case 7:
		angle = SW;
		break;
	}

	return facings(int (angle) );
}

bool Actor::walking_backwards()
{
	mouse_to_player_distance.x = pge->GetMouseX() - (location.x - camera_offset.x) * 128;
	mouse_to_player_distance.y = pge->GetMouseY() - (location.y - camera_offset.y) * 128;

	Vec2 direction = location - old_location;

	return !((direction.GetNormalized().x > 0 && mouse_to_player_distance.GetNormalized().x > 0) || (direction.GetNormalized().y > 0 && mouse_to_player_distance.GetNormalized().y > 0) || (direction.GetNormalized().x < 0 && mouse_to_player_distance.GetNormalized().x < 0) || (direction.GetNormalized().y < 0 && mouse_to_player_distance.GetNormalized().y < 0));
}

Vec2 Actor::get_location()
{
	return location;
}



void Actor::update(float fElapTm, const Vec2& cam_off)
{
	eTime = fElapTm;
	old_location = location;
	facing = lookAtMouse();

	camera_offset = cam_off;
	renderer.update_offset(camera_offset);

	if (isPlayer) {

		if (pge->GetKey(olc::W).bHeld)
			location.y -= eTime * speed;
		if (pge->GetKey(olc::S).bHeld)
			location.y += eTime * speed;
		if (pge->GetKey(olc::A).bHeld)
			location.x -= eTime * speed;
		if (pge->GetKey(olc::D).bHeld)
			location.x += eTime * speed;


		if (pge->GetKey(olc::P).bPressed) 
			renderer.request_animation(PICK, vSpriteSheetPointers[PICK], 0, 0, 0, 0, 4.5f);
		

		else if (pge->GetKey(olc::K).bPressed) {
		//	renderer.request_animation(SMOKE, 0, 0, 1, 1, 1.0f);  smoke not yet implemented
		}

		else if (pge->GetKey(olc::C).bPressed) 
			renderer.request_animation(CLIMB, vSpriteSheetPointers[CLIMB], 0, 0, 1, 1, 4.5f);

		//r{ NOT_INTERRUPTABLE, INTERRUPTABLE }
		//sed{ NOT_REVERESED, REVERSED };
		//{NOT_LOOPED, LOOPED};
		//forth{ NOT_BACK_FORTH, BACK_FORTH };

		//{ INTERRUPTABLE, REVERSED, LOOP, BACK_FORTH }
	}


		if (old_location != location) {

			if (walking_backwards()) {
				renderer.request_animation(WALK, vSpriteSheetPointers[WALK], INTERRUPTABLE, REVERSED, NOT_LOOPED, NOT_BACK_FORTH, 4.0f);
				speed = 0.32f; 
				cout << speed << endl;
			}

			else {
				if (!pge->GetKey(olc::SHIFT).bHeld) {
					renderer.request_animation(WALK, vSpriteSheetPointers[WALK], 1, 0, 0, 0, 6.5f);
					speed = 0.8f; 
					cout << speed << endl;
				}
				else {
					renderer.request_animation(RUN, vSpriteSheetPointers[RUN], 1, 0, 0, 0, 6.5f);
					speed = 1.300f; 
					cout << speed << endl;
				}
			}
		}
		else {
			renderer.request_animation(IDLE, vSpriteSheetPointers[IDLE], 1, 0, 1, 1, 1.5f);
		}

	renderer.update_and_play(eTime, location, facing);
}






