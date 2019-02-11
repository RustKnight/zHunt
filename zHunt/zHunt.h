#pragma once
#include <algorithm>
#include <chrono>
#include <random>

#include "olcPixelGameEngine.h"
#include "RectF.h"
#include "Vec2.h"
#include "Value_checker.h"

#include "Ai.h"
#include "Actor.h"
#include "Zombie.h"
#include "Rifleman.h"
#include "Portal.h"
#include "Projectile.h"
#include "Map.h"
#include "Camera.h"
#include "AnimationHandler.h"
#include "Effect.h"
#include "Controller.h"


#include "olcPGEX_Sound.h"

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
	Portal portal;
	olc::Sprite* fields;
	Camera camera;
	bool toggle_camera = true;
	bool toggle_hunger = false;

	vector<Rifleman*> vRifles;
	vector<Zombie*> vZombies;
	vector<Actor*> vActors;
	Controller control;
	Ai ai;
	
	vector<Projectile> vBullets;
	Value_checker VC;
	Effect effect;

	int snd_fire1;
	int snd_fire2;
	int snd_reload;

	int snd_zom1_hit;
	int snd_zom2_hit;
	int snd_zom3_hit;
};
