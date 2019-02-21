#include "Zombie.h"




void Zombie::randomize_stats(float speed_in)
{
	speed = speed_in;
	random_death_anim = rand() % 8;
}

void Zombie::randomizeStartLocation()
{
	location.x = float (rand() % 16);
	location.y = float (rand() % 10);
}



void Zombie::is_hit()
{	
	hit = true;
	hp -= 5 + rand() % 5;

	if (hp < 0) {
		alive = false;
		renderer.animationCount = 0;
	}

	if (alive)
		renderer.request_animation(HIT, (*vSpriteSheetPointers)[HIT], 0, 0, 0, 0, 0, 5.5f);
}

void Zombie::attack_target(Actor& target)
{
	renderer.request_animation(ATTACK, (*vSpriteSheetPointers)[ATTACK], 0, 0, 0, 0, 0, 8.0f);
	
	target.take_damage(5 + rand() % 16);
}

bool Zombie::attack_cooldown_over()
{
	// if speed of cooldown matches speed of animation - we get synced constant attacks
	// if a brake between attacks is wanted, then another float that grows slower than att_anim_cd_over should be implemented
	// if (att_anim_cd_over && att_cd_over) -> attack;

	if ((int)att_cooldown >= renderer.get_animation_seqences_count(ATTACK, facing)) {
		att_cooldown = 0;
		return true;
	}

	return false;
}



void Zombie::load_assets(vector <olc::Sprite*>* vpZomSpr)
{

	vSpriteSheetPointers = vpZomSpr;


	vector <string> map;

	map.push_back({ "sprites\\zombie\\attack\\z_attack.txt" });
	map.push_back({ "sprites\\zombie\\die\\z_die.txt" });
	map.push_back({ "sprites\\zombie\\hit\\z_hit.txt" });
	map.push_back({ "sprites\\zombie\\idle\\z_idle.txt" });
	map.push_back({ "sprites\\zombie\\walk\\z_walk.txt" });

	Actor::load_assets(map);
}



bool Zombie::in_range(Vec2 target)
{
	
	if (distanceCheck.inRange(target, location, 1000))
		return true;

	return false;
}



void Zombie::stay()
{
	//location = old_location;
	renderer.request_animation(IDLE, (*vSpriteSheetPointers)[IDLE], 1, 0, 1, 1, 0, speed * 5.0f);
}

void Zombie::moveTowardsGoal()
{
	Vec2 vec = goal - location;

	location += vec.GetNormalized() * eTime * speed;
	moving = true;
}


void Zombie::loadZfeed(int* x)
{
	ZomFeedOnDead = x;
}

int Zombie::closestFlesh(vector<Vec2>* vRflPosition, bool rf0, bool rf1)
{
	int closestFleshIndex;
	Vec2 rifle0 = (*vRflPosition)[0];
	Vec2 rifle1 = (*vRflPosition)[1];
	
	bool teleporting0;
	bool teleporting1;

	int portalEntryIndex0;
	int portalExitIndex0;
	int portalEntryIndex1;
	int portalExitIndex1;

	float distToRifle0 = calculatePath(rifle0, teleporting0, portalEntryIndex0, portalExitIndex0);
	float distToRifle1 = calculatePath(rifle1, teleporting1, portalEntryIndex1, portalExitIndex1);


	if (distToRifle0 < distToRifle1) {

		if (teleporting0) {
			desiredPrtIndex = portalExitIndex0;
			setGoal((*vpPrt)[portalEntryIndex0]->get_location());
			closestFleshIndex = 0;
		}
		else {
			setGoal(rifle0);
			closestFleshIndex = 0;
			desiredPrtIndex = -1;
		}
	}

	else {
		if (teleporting1) {
			desiredPrtIndex = portalExitIndex1;
			setGoal((*vpPrt)[portalEntryIndex1]->get_location());
			closestFleshIndex = 1;
		}
		else {
			setGoal(rifle1);
			closestFleshIndex = 1;
			desiredPrtIndex = -1;
		}
	}




	if (!rf0 && closestFleshIndex == 0)
		(*ZomFeedOnDead)++;
	if ((*ZomFeedOnDead) > 6) {
		setGoal(rifle1);
		closestFleshIndex = 1;
	}



	return closestFleshIndex;
}

float Zombie::calculatePath(const Vec2& PathRifle, bool& teleporting, int& InIndexPortal, int& OutIndexPortal) const
{
	teleporting = false;

	float walkingDistance = (PathRifle - location).GetLengthSq();
	float closestToZom = closestToActor(location, InIndexPortal);
	float closestToRifle = closestToActor(PathRifle, OutIndexPortal);

	if (InIndexPortal == OutIndexPortal)
		return walkingDistance;

	float totalPortals = closestToZom + closestToRifle;

	if (walkingDistance < totalPortals)
		return walkingDistance;
	else {
		teleporting = true;
		return totalPortals;
	}
}

float Zombie::closestToActor(const Vec2& Actor, int& portalIndex) const
{
	// non pair teleport (closest to rifle)
	if (!(*vpPrt)[0]->pairing) {

		float closest = 9999999;

		for (size_t i = 0; i < (*vpPrt).size(); i++) {

			if ((*vpPrt)[i]->getStatus() && !(*vpPrt)[i]->isSpawner && (*vpPrt)[i]->isReady()) {

				float distToPortal_i = ((*vpPrt)[i]->get_location() - Actor).GetLengthSq();

				if (closest > distToPortal_i) {
					closest = distToPortal_i;
					portalIndex = int (i);
				}

			}
		}

		return closest;
	}


	return 0.0f;
}

void Zombie::changeSpeed(float speed_in)
{
	speed = speed_in;
}

bool Zombie::update(float fElapTm, const Vec2 & cam_off)
{
	eTime = fElapTm;
	camera_offset = cam_off;
	renderer.update_offset(camera_offset);
	timeSinceLastTele += fElapTm * 1.0f;

	if (!alive && renderer.animationCount > 0)
		finishedDieing = true;

	for (Portal* p : *vpPrt) {
		if (p->visible)
			p->tryTeleport(*this);
	}

	if (renderer.get_current_anim() != HIT)
		hit = false;


	if (alive && !hit) {

		if (moving)
			renderer.request_animation(WALK, (*vSpriteSheetPointers)[WALK], 1, 0, 0, 0, 0, speed * 30.0f);
		else
			renderer.request_animation(IDLE, (*vSpriteSheetPointers)[IDLE], 1, 0, 1, 1, 0, speed * 5.0f);


		look_at_vec(goal);

		if (att_cooldown < 200.0f)
			att_cooldown += eTime * 4.0f;

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
				renderer.request_animation(DIE, (*vSpriteSheetPointers)[DIE], 0, 0, 0, 0, 0, 13.5f);
		}
	}


	else if (alive)
		renderer.request_animation(IDLE, (*vSpriteSheetPointers)[IDLE], 1, 0, 1, 1, 0, speed * 5.0f);

	if (!alive) {
		facing = facings(random_death_anim);
		renderer.override (DIE, (*vSpriteSheetPointers)[DIE], 0, 0, 0, 0, 1, 13.5f);

	}

	moving = false;


	return 0;
}

