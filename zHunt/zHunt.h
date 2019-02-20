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
#include "zSpawner.h"
#include "CinematicEffect.h"


#include "olcPGEX_Sound.h"

class zHunt : public olc::PixelGameEngine
{

	class Scripter {
	public:
		Scripter (zHunt* pZ): z{pZ}, scriptState {0}
		{}

		bool playScript() {

			switch (scriptState) {
			case 0:

				break;

			}

		}

	private:
		zHunt* z;
		int scriptState;
	};



public:
	zHunt();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	void loadResources();

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

	CinematicEffect cinematicEffect;
	Map map;
	Rifleman rifleman;
	olc::Sprite* fields;
	Camera camera;
	bool toggle_camera = true;
	bool toggle_hunger = false;

	vector <olc::Sprite*> vZomSprites;
	vector <olc::Sprite*> vRflSprites;
	vector <olc::Sprite*> vPrtSprites;

	vector<Rifleman*> vRifles;
	vector<Portal*> vPortals;
	vector<Zombie*> vZombies;
	vector<Actor*> vActors;
	Controller control;
	Ai ai;
	zSpawner zSpawn;
	
	vector<Projectile> vBullets;
	Value_checker VC;
	Effect effect;

	int snd_fire1;
	int snd_fire2;
	int snd_reload;

	int snd_zom1_hit;
	int snd_zom2_hit;
	int snd_zom3_hit;

	int snd_empty;
};
