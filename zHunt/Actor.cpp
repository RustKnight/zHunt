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

void Actor::changeFacing(facings face)
{
	facing = face;
}

bool Actor::walking_backwards()
{
	mouse_to_player_distance.x = pge->GetMouseX() - (location.x - camera_offset.x) * 128;
	mouse_to_player_distance.y = pge->GetMouseY() - (location.y - camera_offset.y) * 128;

	Vec2 direction = location - old_location;

	return !((direction.GetNormalized().x > 0 && mouse_to_player_distance.GetNormalized().x > 0) || (direction.GetNormalized().y > 0 && mouse_to_player_distance.GetNormalized().y > 0) || (direction.GetNormalized().x < 0 && mouse_to_player_distance.GetNormalized().x < 0) || (direction.GetNormalized().y < 0 && mouse_to_player_distance.GetNormalized().y < 0));
}

void Actor::take_damage(int damage)
{
	hp -= damage;
	facing = N;

	if (hp < 0) {
		
		renderer.request_animation(9, vSpriteSheetPointers[9], 0, 0, 0, 0, 1, 7.5f);
		alive = false;
	}
	else
		renderer.request_animation (8, vSpriteSheetPointers[8], 0, 0, 0, 0, 0, 10.0f);
}

void Actor::become_player(bool toggle)
{
	isPlayer = toggle;
}


void Actor::move_towards_vec(Vec2 in_goal)
{
	if (alive && !hit) 
		goal = (in_goal - location).Normalize();
}

void Actor::load_assets(vector<string> in_mappings)
{
	renderer.passMappingData(in_mappings);
}

Vec2 Actor::get_location() const
{
	return location;
}



bool Actor::update(float fElapTm, const Vec2& cam_off)
{
	return 0;
}

void Actor::draw()
{
	renderer.update_and_play(eTime, location, facing);
}






