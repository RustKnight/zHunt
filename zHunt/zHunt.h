#pragma once
#include <algorithm>
#include <chrono>
#include <random>

#include "olcPixelGameEngine.h"
#include "RectF.h"
#include "Vec2.h"
#include "Value_checker.h"

#include "Actor.h"
#include "Zombie.h"
#include "Rifleman.h"
#include "Projectile.h"
#include "Map.h"
#include "Camera.h"



class zHunt : public olc::PixelGameEngine
{
public:
	zHunt(vector <vector<string>>& paths);

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	//tool functions
	Vec2 placeInCenter() const;

	//getters
	float getWinWidth()	const;
	float getWinHeight()const;


private:
	float winWidth;
	float winHeight;

	Map map;
	Rifleman rifleman;
	Zombie zombie;
	olc::Sprite* fields;
	Camera camera;
	bool toggle_camera = true;
	bool toggle_hunger = true;

	vector<Zombie> vZombies;
	vector<Actor*> vActors;
	vector<Projectile> vBullets;
	Value_checker VC;
};
