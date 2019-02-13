#include "Portal.h"

void Portal::load_assets()
{
		load_spr_sheet("sprites\\portals\\brown_idle\\idle.png");
		load_spr_sheet("sprites\\portals\\red_idle\\idle.png");
		load_spr_sheet("sprites\\portals\\brown_open\\open.png");
		load_spr_sheet("sprites\\portals\\red_open\\open.png");

		vector <string> mappingData;
		mappingData.push_back({ "sprites\\portals\\brown_idle\\idle.txt" });
		mappingData.push_back({ "sprites\\portals\\red_idle\\idle.txt" });	
		mappingData.push_back({ "sprites\\portals\\brown_open\\open.txt" });
		mappingData.push_back({ "sprites\\portals\\red_open\\open.txt" });
		Actor::load_assets(mappingData);
}



//bool interruptable, bool reversed_in, bool loop_in, bool back_and_forth, bool end_lock_in, float speed

void Portal::update(float eTime_in, const Vec2 & cam_off, bool triggered)
{
	eTime = eTime_in;
	camera_offset = cam_off;
	renderer.update_offset(camera_offset);

	
}

void Portal::openPortal()
{
	if (!opened) {

		isActive = true;				//flag that it's safe to draw portal

		transitionDone = renderer.animationCount;

		if (!transitionDone && !opened)
			renderer.request_animation(color_open, vSpriteSheetPointers[color_open], 0, 0, 0, 0, 1, speed * 15.0f);

		else {
			renderer.override(color_idle, vSpriteSheetPointers[color_idle], 1, 0, 1, 1, 0, speed * 15.0f);
			opened = true;
		}

	}

	else
		renderer.animationCount = 0;
}


void Portal::closePortal()
{
	if (opened) {
		
		renderer.request_animation(color_open, vSpriteSheetPointers[color_open], 1, 1, 0, 0, 1, speed * 15.0f);

		transitionDone = renderer.animationCount;


		if (transitionDone) {
			isActive = false;
			opened = false;
			renderer.animationCount = 0;
		}
		
	}

}



void Portal::becomeSpawner(Vec2 spw_loc)
{
	color_idle = BROWN_IDLE;
	color_open = BROWN_OPEN;

	location = spw_loc;
	isSpawner = true;
	isTeleporter = false;
}

