#include "Portal.h"

void Portal::load_assets()
{
		load_spr_sheet("sprites\\portals\\portals.png");
		vector <string> mappingData;
		mappingData.push_back({ "sprites\\portals\\portals.txt" });
		mappingData.push_back({ "sprites\\portals\\portals.txt" });	// two times pushback so that portal can initiate properly.
		Actor::load_assets(mappingData);
}

void Portal::spawn()
{

	
}

void Portal::update(float eTime_in, const Vec2 & cam_off, bool triggered)
{
	eTime = eTime_in;
	camera_offset = cam_off;
	renderer.update_offset(camera_offset);
	facing = facings (IDLE_RED);

	
	if (triggered) {
		renderer.request_animation(0, vSpriteSheetPointers[0], 0, 0, 1, 1, 0, 7.5f);
	}

}
