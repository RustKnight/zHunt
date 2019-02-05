#pragma once
#include "Actor.h"
#include "Zombie.h"
#include "Weapon.h"
#include <algorithm>

//	N-0, NE-1, E-2, SE-3, S-4, SW-5, W-6, NW-7

class TurnAround {
public:
	void setCurrent(int current, float in_eTime) { 
		lastTarget = currentTarget;
		currentTarget = current;
		facing = lastTarget;

		eTime = in_eTime;
	}

	bool complete() {
		if ((int)facing == currentTarget)
			return true;

	//	fastestTurn();
		startTurning();
		return false;
	}

	void startTurning() {

		if (turnRight) {
				facing += roateSpeed;
				if (facing > 7)
					facing = 0;
		}
		else {
			facing -= roateSpeed * eTime;
			if (facing < 0)
				facing = 7;
		}
	}


	void fastestTurn() {

		int inc = lastTarget;
		int dec = lastTarget;

		if (inc != currentTarget || dec != currentTarget) {
			inc++;
			dec--;

			if (inc > 7)
				inc = 0;
			if (dec < 0)
				dec = 7;
		}

		if (inc == currentTarget)
			turnRight = true;
		else if (dec == currentTarget)
			turnRight = false;
	}

	int getFacing() {
		return facing;
	}

private:
	int lastTarget = 0;
	int currentTarget = 0;
	float facing = 0;
	float roateSpeed = 1.0f;
	float eTime;
	bool turnRight = true;
};

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
	void fire(bool b, Vec2 fireAt);
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