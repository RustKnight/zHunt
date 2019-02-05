#pragma once
#include "Actor.h"
#include "Zombie.h"
#include "Weapon.h"
#include <algorithm>
#include "TurnAround.h"

class Rifleman : public Actor {

	enum actions { AIM, CLIMB, IDLE, PICK, RUN, WALK, FIRE, RELOAD, HURT, DIE };

public:
	Rifleman (Vec2 loc, olc::PixelGameEngine* in_pge) :
								//clipMax, clipNow, damage, fireRate, fireCD, reloadTime, reload, reloading
		Actor (loc, in_pge), kar (5,		5,		3,		1.5f,			0,		4,			0,		0)
	{
		hp = 25;
		alive = true;
	}

	bool update(float fElapTm, const Vec2 & cam_off, std::vector<Zombie*> vpZom);
	void updateFireAngle(Vec2 fireAt);
	void reload();
	void running();
	void aim();
	void fire(bool fire, Vec2 fireAt);
	void moveTowardsGoal();
	void standGround();
	void shootAtTarget(Zombie* target);
	void follow();
	Vec2 getFireAngle();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	vector<Zombie*> actorsOnScreen(vector<Zombie*> vec);
	Zombie* closestTarget(vector<Zombie*> vec);

	void load_assets();

private:
	Carabine kar;
	TurnAround turn;
	Vec2 fireAngle;
	bool fired = false;
	bool aiming = false;
	vector<Zombie*> vpZom;
};