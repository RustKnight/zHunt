#include "Zombie.h"


void Zombie::randomize_stats(float speed_in)
{
	speed = speed_in;
	location.x = rand() % 16;
	location.y = rand() % 10;
	random_death_anim = rand() % 8;
}

void Zombie::look_at_vec(Vec2 pos)
{

#define PI 3.14159265

		// we determine the vector between the mouse position and the location of the character
		float dx = (pos.x * 128) - (location.x * 128);
		float dy = (pos.y * 128) - (location.y * 128);
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

void Zombie::move_towards_vec(Vec2 goal)
{
	if (alive) {
		Vec2 go_to = (goal - location).Normalize();
		location += go_to * eTime * speed;

		if (old_location != location)
			renderer.request_animation(WALK, vSpriteSheetPointers[WALK], 1, 0, 0, 0, 0, speed * 30.0f);
		else
			renderer.request_animation(IDLE, vSpriteSheetPointers[IDLE], 1, 0, 1, 1, 0, speed * 5.0f);

		look_at_vec(goal);
	}

	else {
		facing = facings (random_death_anim);
		renderer.request_animation(DIE, vSpriteSheetPointers[DIE], 0, 0, 0, 0, 1, 13.5f);
	}
}



bool Zombie::update(float fElapTm, const Vec2 & cam_off)
{
	if (hp < 0) 
		alive = false;
		
	
	eTime = fElapTm;
	old_location = location;

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
			renderer.request_animation(DIE, vSpriteSheetPointers[DIE], 0, 0, 0, 0, 0, 13.5f);
	}


	return 0;
}

