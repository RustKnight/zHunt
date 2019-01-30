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
#include "AnimationHandler.h"
#include "Effect.h"
#include "Controller.h"



class zHunt : public olc::PixelGameEngine
{
public:
	zHunt();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	//tool functions
	Vec2 placeInCenter() const;
	void sort_actors_by_height();
	void draw_effect_on_actor(Actor& actor);

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

	vector<Zombie*> vZombies;
	vector<Actor*> vActors;
	Controller control;

	
	vector<Projectile> vBullets;
	Value_checker VC;
	Effect effect;
};
