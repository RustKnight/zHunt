#include "Actor.h"

#define PI 3.14159265
enum facings;





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

	renderer.request_animation (8, (*vSpriteSheetPointers)[8], 0, 0, 0, 0, 0, 10.0f);
}

void Actor::become_player(bool toggle)
{
	isPlayer = toggle;
}


int Actor::get_facing(Vec2 pos)
{

	// for debug, line can be drawn

	float dx = (pos.x - location.x) * 128;
	float dy = (pos.y - location.y) * 128;


	if (isPlayer) {
		dx = pge->GetMouseX() - ((location.x - camera_offset.x) * 128);
		dy = pge->GetMouseY() - ((location.y - camera_offset.y) * 128);
	}

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

	return int(angle);
}



void Actor::set_facing(int face)
{
	facing = facings(face);
}

void Actor::look_at_vec(Vec2 pos)
{

	

	float dx = (pos.x - location.x) * 128;
	float dy = (pos.y - location.y) * 128;
		


	if (isPlayer) {
		
		dx = pge->GetMouseX() - ((location.x - camera_offset.x) * 128);
		dy = pge->GetMouseY() - ((location.y - camera_offset.y) * 128);

		
	}

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

	facing = facings(int(angle));
}

void Actor::setGoal(Vec2 in_goal)
{

	if (alive && !hit)
		goal = in_goal;
}

Vec2 Actor::getGoal() const
{
	return goal;
}

bool Actor::moveTowardsGoal(float speed_in)
{

	if (!withinDistance(goal, 20)) {

		Vec2 vec = goal - location;

		location += vec.GetNormalized() * eTime * speed_in;
	}

	else
		speed = speed_in;

	return false;
}

// original moveToGoal for Camera Sight

//bool Actor::moveTowardsGoal(float speed_in)
//{
//
//	if (!withinDistance(goal, 20)) {
//
//		cout << location.x << endl;
//
//		Vec2 vec = goal - location;
//
//		location += vec.GetNormalized() * eTime * speed;
//	}
//
//	else
//		speed = speed_in;
//
//	return false;
//}



bool Actor::withinOwnRect(Vec2 location_in) const
{
	int x = (location_in.x - camera_offset.x) * 128;
	int y = (location_in.y - camera_offset.y) * 128;

	RenderRect r_rect = renderer.get_render_rect();

	if ((y > r_rect.top && y < r_rect.bottom) && (x > r_rect.left && x < r_rect.right))
		return true;
	else
		return false;
}

bool Actor::withinDistance(Vec2 goal, int dist_radius)
{
	return distanceCheck.inRange(goal, location, dist_radius);
}

float Actor::LengthSq2Vec(Vec2* a, Vec2* b)
{
	return (*a - *b).GetLengthSq();
}

bool Actor::keepOnMap()
{
	if (location.x > 15.8f) {
		location.x = 15.8f;
		return true;
	}

	else if (location.x < 0.2f) {
		location.x = 0.2f;
		return true;
	}

	else if (location.y > 9.75f) {
		location.y = 9.75f;
		return true;
	}

	else if (location.y < 0.05f) {
		location.y = 0.05f;
		return true;
	}



	return false;
}



void Actor::load_assets(vector<string> in_mappings)
{
	renderer.passMappingData(in_mappings);
}

Vec2 Actor::get_location() const
{
	return location;
}

void Actor::set_location(Vec2 loc)
{
	location = loc;
}



bool Actor::update(float fElapTm, const Vec2& cam_off)
{
	eTime = fElapTm;
	return 0;
}

void Actor::draw()
{
	renderer.update_and_play(eTime, location, facing);
}






