#include "Rifleman.h"

bool Rifleman::update(float fElapTm, const Vec2 & cam_off)
{
	bool fired = false;
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

		//r{ NOT_INTERRUPTABLE, INTERRUPTABLE }
		//sed{ NOT_REVERESED, REVERSED };
		//{NOT_LOOPED, LOOPED};
		//forth{ NOT_BACK_FORTH, BACK_FORTH };

		//{ INTERRUPTABLE, REVERSED, LOOP, BACK_FORTH }
	}


	if (pge->GetKey(olc::R).bPressed)
		renderer.request_animation(RELOAD, vSpriteSheetPointers[RELOAD], 0, 0, 0, 0, 0, 3.0f);
	else if (pge->GetKey(olc::K).bPressed) {
		//	renderer.request_animation(SMOKE, 0, 0, 1, 1, 1.0f);  smoke not yet implemented
	}
	


	if (old_location != location) {

		if (walking_backwards()) {
			renderer.request_animation(WALK, vSpriteSheetPointers[WALK], INTERRUPTABLE, REVERSED, NOT_LOOPED, NOT_BACK_FORTH, 0, 4.0f);
			speed = 0.32f;
			//cout << speed << endl;
		}

		else {
			if (!pge->GetKey(olc::SHIFT).bHeld) {
				renderer.request_animation(WALK, vSpriteSheetPointers[WALK], 1, 0, 0, 0, 0, 6.5f);
				speed = 0.8f;
				//cout << speed << endl;
			}
			else {
				renderer.request_animation(RUN, vSpriteSheetPointers[RUN], 1, 0, 0, 0, 0, 9.5f);
				speed = 1.300f;
				//cout << speed << endl;
			}
		}
	}

	else if (pge->GetMouse(1).bHeld) {
		renderer.request_animation(AIM, vSpriteSheetPointers[AIM], 1, 0, 1, 0, 0, 3.0f);

		if (pge->GetMouse(0).bPressed) {
			renderer.request_animation(FIRE_SLOW, vSpriteSheetPointers[FIRE_SLOW], 0, 0, 0, 0, 0, 15.5f);
			fired = true;
		}

		else if (pge->GetMouse(2).bHeld) {
			renderer.request_animation(FIRE_FAST, vSpriteSheetPointers[FIRE_FAST], 0, 0, 0, 0, 0, 15.5f);
			fired = true;
		}
	}
	else 
		renderer.request_animation(IDLE, vSpriteSheetPointers[IDLE], 1, 0, 1, 1, 0, 1.5f);


	return fired;
}

Vec2 Rifleman::get_fire_angle() const
{
	float dx = pge->GetMouseX() - ((location.x - camera_offset.x) * 128);
	float dy = pge->GetMouseY() - ((location.y - camera_offset.y) * 128);

	return Vec2{ dx, dy }.Normalize();
}
