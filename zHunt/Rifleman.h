#pragma once
#include "Actor.h"
#include "Zombie.h"
#include "Weapon.h"
#include <algorithm>
#include "TurnAround.h"


//DONE stop beserk fire - ai cannot toggle the not firing flag on
//DONE Diagonal move of AI 50 % more ?
//DROPPED player turn as AI as well, so running and turning around is costs a bit of time and is not abused
// bullets sometimes pass target?

class Rifleman : public Actor {

	enum actions { AIM, CLIMB, IDLE, PICK, RUN, WALK, FIRE, RELOAD, HURT, DIE, SMOKE };

public:
	Rifleman (Vec2 loc, olc::PixelGameEngine* in_pge) :
								//clipMax, clipNow, damage, fireRate, fireCD, reloadTime, reload, reloading
		Actor (loc, in_pge), kar (5,		5,		3,		1.5f,			0,		4,			0,		0)
	{
		hp = 25;
		alive = true;
		isActive = false;
	}

	bool update(float fElapTm, const Vec2 & cam_off, std::vector<Zombie*> vpZom);
	void updateFireAngle(Vec2 fireAt);
	void smoke();
	void idle();
	void reload();
	void running();
	void aim();
	void fire(bool fire, Vec2 fireAt);
	void moveTowardsGoal();
	void standGround(bool agr);
	void shootAtTarget(Zombie* target);
	void follow();
	Vec2 getFireAngle();
	void getSounds(int f1, int f2, int r);
	void die();
	void loadPortalsPointer(vector<Portal*>* vpP);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	vector<Zombie*> actorsOnScreen(vector<Zombie*> vec);
	Zombie* closestTarget(vector<Zombie*> vec);



	void load_assets(vector <olc::Sprite*>* vpRfl);
	TurnAround turn;
private:
	Carabine kar;
	
	Vec2 fireAngle;
	bool fired = false;
	bool aiming = false;
	vector<Zombie*> vpZom;
	vector<Portal*>* vpPrt;

	int snd_empty;
	int snd_fire1;
	int snd_fire2;
};