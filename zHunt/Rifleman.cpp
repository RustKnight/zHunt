#include "Rifleman.h"

bool Rifleman::update(float fElapTm, const Vec2 & cam_off)
{
	eTime = fElapTm;
	camera_offset = cam_off;
	old_location = location;
	renderer.update_offset(camera_offset);
	bool fired = false;


	if (isPlayer && alive) {

		facing = lookAtMouse();


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
		renderer.request_animation(RELOAD, vSpriteSheetPointers[RELOAD], 0, 0, 0, 0, 0, 2.0f);
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
			renderer.request_animation(FIRE, vSpriteSheetPointers[FIRE], 0, 0, 0, 0, 0, 15.5f);
			fired = true;
		}

		else if (pge->GetMouse(2).bHeld) {
			renderer.request_animation(FIRE, vSpriteSheetPointers[FIRE], 0, 0, 0, 0, 0, 15.5f);
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

void Rifleman::load_assets()
{

	load_spr_sheet("sprites\\rifleman\\NEW\\aim\\r_aim.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\climb\\r_climb.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\idle\\r_idle.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\pick\\r_pick.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\run\\r_run.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\walk\\r_walk.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\fire\\r_fire.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\reload\\r_reload.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\hurt\\r_hurt.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\die\\r_die.png");


	vector <string> mappingData;

	mappingData.push_back({ "sprites\\rifleman\\NEW\\aim\\r_aim.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\climb\\r_climb.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\idle\\r_idle.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\pick\\r_pick.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\run\\r_run.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\walk\\r_walk.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\fire\\r_fire.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\reload\\r_reload.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\hurt\\r_hurt.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\die\\r_die.txt" });

	Actor::load_assets(mappingData);

}

