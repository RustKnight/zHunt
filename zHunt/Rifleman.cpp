#include "Rifleman.h"

void Rifleman::update(float fElapTm, const Vec2 & cam_off)
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
			//cout << speed << endl;
		}

		else {
			if (!pge->GetKey(olc::SHIFT).bHeld) {
				renderer.request_animation(WALK, vSpriteSheetPointers[WALK], 1, 0, 0, 0, 6.5f);
				speed = 0.8f;
				//cout << speed << endl;
			}
			else {
				renderer.request_animation(RUN, vSpriteSheetPointers[RUN], 1, 0, 0, 0, 9.5f);
				speed = 1.300f;
				//cout << speed << endl;
			}
		}
	}
	else {
		renderer.request_animation(IDLE, vSpriteSheetPointers[IDLE], 1, 0, 1, 1, 1.5f);
	}

	renderer.update_and_play(eTime, location, facing);
}
