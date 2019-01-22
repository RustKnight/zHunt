#include "Zombie.h"


void Zombie::randomize_location()
{

	location.x = rand() % 16;
	location.y = rand() % 10;

}

void Zombie::look_at_vec(Vec2 pos)
{

#define PI 3.14159265

		// we determine the vector between the mouse position and the location of the character
		float dx = ((pos.x - camera_offset.x) * 128) - ((location.x - camera_offset.x) * 128);
		float dy = ((pos.y - camera_offset.y) * 128) - ((location.y - camera_offset.y) * 128);
		//	pge->DrawLine(pge->GetMouseX(), pge->GetMouseY(), (location.x - camera_offset.x) * 128, (location.y - camera_offset.y) * 128, olc::RED);


		float angle = atan2(dy, dx);
		angle = (roundf(angle / ((2 * PI) / 8) + 4));
		if (angle == 8)
			angle = 0;

		switch (int(angle)) {
			//N = 2, NE = 3, E = 4, SE = 5, S = 6, SW = 7, W = 0, NW = 1,
		case 0:
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

		facing = facings (int (angle));
}

void Zombie::update(float fElapTm, const Vec2 & cam_off)
{
	eTime = fElapTm;
	old_location = location;
	//facing = lookAtMouse();

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


		if (pge->GetKey(olc::I).bPressed)
			renderer.request_animation(DIE, vSpriteSheetPointers[DIE], 0, 0, 0, 0, 13.5f);

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
			//cout << speed << endl;
		}

		else {
			renderer.request_animation(WALK, vSpriteSheetPointers[WALK], 1, 0, 0, 0, 6.5f);
			speed = 0.8f;
			//cout << speed << endl;
		}		
	}

	else 
		renderer.request_animation(IDLE, vSpriteSheetPointers[IDLE], 1, 0, 1, 1, 1.5f);
	

	renderer.update_and_play(eTime, location, facing);
}