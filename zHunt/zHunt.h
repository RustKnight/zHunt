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
	// wait for hans to reach heinrich(player)
	// if hans is in range stop smoking(idle) turn to hans
	// hans.wav
	// heinrich.wav
	// both turn to west
	// pan to West portal
	// open portal
	// pan to player and give control/get out of cinema mode
	// let player get close to portal
	// 
	
	
	
	// last tests
	// add cinematic on/off option in txt
	// add music when dead?
 

	class Scripter {
	public:
		Scripter (zHunt* pZ): z{pZ}, scriptState { WALK_TO_HEINRICH }
		{}

		enum scriptStates {WALK_TO_HEINRICH, SND_HANS, SND_HEINRICH, LOOK_WEST, PAN_WEST_PORTAL, OPEN_WEST_PORTAL,
							PAN_BACK_FAST, GET_CLOSE, ASK_GET_ANSWER, HANS_ALLIGN, Z_APPROACH, OPEN_REST_PORTALS, TRIGGER_ALL, TIERE, END	};

		bool playScript(float eTime) {

			switch (scriptState) {

			case WALK_TO_HEINRICH:
				z->vRifles[1]->isActive = false;

				if (z->vRifles[0]->withinDistance(z->vRifles[1]->get_location(), 25000)) {
					tick -= eTime * 6.5f;

					if (tick < 1) {
						resetSpecialStates();
						scriptState++;
						break;
					}

					z->vRifles[1]->set_facing(tick);
					z->vRifles[1]->idle();
				}

				else {
					z->vRifles[1]->smoke();
					z->vRifles[1]->set_facing(4);
				}
				break;

			case SND_HANS:

				if (playSound(eTime, z->snd_hans)) {
					resetSpecialStates();
					scriptState++;
				}
				break;

			case SND_HEINRICH:

				if (playSound(eTime, z->snd_heinrich)) {
					resetSpecialStates();

					// Hans look West
					z->vRifles[0]->setGoal(Vec2{ 0, z->vRifles[0]->get_location().y });

					scriptState++;
				}


				break;

			case LOOK_WEST:

				if (tick < -3) {
					resetSpecialStates();
					playSound(eTime, z->snd_hmm);
					scriptState++;
					break;
				}

				//quick hack for turning beyond 0


				if (tick < -1)
					z->vRifles[1]->set_facing(7);
				if (tick < -2)
					z->vRifles[1]->set_facing(6);


				if (tick >= 0)
					z->vRifles[1]->set_facing(tick);


				tick -= eTime * 6.5f;

				break;


			case PAN_WEST_PORTAL:

				// clean up after previous sound call
				resetSpecialStates();

				if (!z->cameraSight.withinDistance(z->vPortals[2]->get_location(), 3500)) {

					z->cameraSight.update(eTime, z->camera.get_offset());
					z->cameraSight.setGoal(z->vPortals[2]->get_location());
					z->cameraSight.moveTowardsGoal(1.5f); // 0.8 is the normal walking speed
				}
				else
					scriptState++;

				break;


			case OPEN_WEST_PORTAL:

				z->vPortals[2]->visible = true;
				if (z->vPortals[2]->getStatus()) {
					z->vPortals[2]->isActive = false;
					scriptState++;
				}

				break;


			case PAN_BACK_FAST:

				if (!z->cameraSight.withinDistance(z->vRifles[1]->get_location(), 1050)) {

					z->cameraSight.update(eTime, z->camera.get_offset());
					z->cameraSight.setGoal(z->vRifles[1]->get_location());
					z->cameraSight.moveTowardsGoal(2.5f);
				}

				else {
					isOn = false;
					z->vRifles[1]->isActive = true;
					scriptState++;
				}

				break;

			case GET_CLOSE:

				if (z->vRifles[1]->withinDistance(z->vPortals[2]->get_location(), 105000)) {

					z->cameraSight.set_location(z->vRifles[1]->get_location());
					z->vRifles[1]->idle();
					isOn = true;
					z->vRifles[1]->isActive = false;

					scriptState++;

				}
				break;

			case ASK_GET_ANSWER:


				if (playSound(eTime, z->snd_wasist)) {
					resetSpecialStates();
					z->ai.moveTo((z->vRifles[0]->get_location() + Vec2{ -0.6f, -0.4 }));
					scriptState++;
				}

				break;

			case HANS_ALLIGN:

				if (z->ai.noMoveOrders()) {

					z->zSpawn.spawnZat(2); // 2 is our east spawn portal
					playSound(eTime, z->snd_wounded);
					resetSpecialStates();
					scriptState++;
				}
				break;

			case Z_APPROACH:
				z->vRifles[0]->setGoal(z->vZombies[0]->get_location());	// needed to make him face correctly
				z->vRifles[0]->set_facing(6);
				z->toggle_hunger = true;


				if (!z->vZombies[0]->alive)
					scriptState++;

				else if (z->vZombies[0]->withinDistance(z->vRifles[1]->get_location(), 55000)) {
					z->ai.setAggro(true);
					resetSpecialStates();
				}

				else if (z->vZombies[0]->withinDistance(z->vRifles[1]->get_location(), 75000)) {
					playSound(eTime, z->snd_halt);
					z->vRifles[0]->aim();
				}

				

				break;

			case OPEN_REST_PORTALS:// must brake after this switch


				switch (int(tick)) {

				case 0:

					if (!z->cameraSight.withinDistance(z->vPortals[0]->get_location(), 3500)) {

						z->cameraSight.update(eTime, z->camera.get_offset());
						z->cameraSight.setGoal(z->vPortals[0]->get_location());
						z->cameraSight.moveTowardsGoal(3.0f); // 0.8 is the normal walking speed
					}

					else {
						z->vPortals[0]->visible = true;

						if (z->vPortals[0]->getStatus()) {
							z->vPortals[0]->isActive = false;
							tick++;
						}
					}

					break;


				case 1:

					if (!z->cameraSight.withinDistance(z->vPortals[3]->get_location(), 3500)) {

						z->cameraSight.update(eTime, z->camera.get_offset());
						z->cameraSight.setGoal(z->vPortals[3]->get_location());
						z->cameraSight.moveTowardsGoal(3.0f); // 0.8 is the normal walking speed
					}

					else {
						z->vPortals[3]->visible = true;

						if (z->vPortals[3]->getStatus()) {
							z->vPortals[3]->isActive = false;
							tick++;
						}
					}

					break;


				case 2:

					if (!z->cameraSight.withinDistance(z->vPortals[1]->get_location(), 3500)) {

						z->cameraSight.update(eTime, z->camera.get_offset());
						z->cameraSight.setGoal(z->vPortals[1]->get_location());
						z->cameraSight.moveTowardsGoal(3.0f); // 0.8 is the normal walking speed
					}

					else {
						z->vPortals[1]->visible = true;

						if (z->vPortals[1]->getStatus()) {
							z->vPortals[1]->isActive = false;
							tick++;
						}
					}

					break;


				case 3:

					if (!z->cameraSight.withinDistance(z->vRifles[1]->get_location(), 1050)) {

						z->cameraSight.update(eTime, z->camera.get_offset());
						z->cameraSight.setGoal(z->vRifles[1]->get_location());
						z->cameraSight.moveTowardsGoal(3.0f);
					}

					else {
						scriptState++;
						resetSpecialStates();
					}

					break;


				}

				break;

				case TRIGGER_ALL:
			
					z->vRifles[1]->isActive = true;
					isOn = false;
					z->ai.setAggro(true);
					z->toggle_hunger = true;

					for (Portal* p : z->vPortals) {
						if (p->isSpawner) {
							p->isActive = true;
							p->visible = true;
						}
					}
					
					scriptState++;

				break;

				case TIERE:


					if (z->zombieCount > 30) {
						for (Portal* p : z->vPortals) {
							p->isActive = true;
							p->visible = true;
						}
						resetSpecialStates();
						scriptState++;
					}

					else if (z->zombieCount > 20)
						playSound(eTime, z->snd_tiere);



				break;

				case END:

					// needed because of misfortunate coupling
					for (Portal* p : z->vPortals) 
						p->visible = true;
					
					
					if (!z->vRifles[0]->alive && !z->vRifles[1]->alive) {
						playSound(eTime, z->snd_gameOver);
						if (z->cinematicEffect.closeView() )
							z->playing = false;
					}

					break;

			}


			return isOn;
		}




		bool playSound(float eTime, int sndID) {
			tick += eTime * 0.9f;

			if (!soundPlaying) {
				olc::SOUND::PlaySample(sndID, false);
				soundPlaying = true;
			}

			if (tick > 1)
				return true;

			return false;
		}



		void resetSpecialStates() {
			tick = 0;
			soundPlaying = false;
		}

		void setScriptAt(int stage) {

			scriptState = stage;

		}


	private:
		zHunt* z;
		int scriptState;
		bool isOn = true;
		bool soundPlaying = false;
		float tick = 4;
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

	Scripter script;
	CinematicEffect cinematicEffect;
	Map map;
	Rifleman rifleman;
	olc::Sprite* fields;
	Camera camera;
	Actor cameraSight;
	bool toggle_camera = true;
	bool toggle_hunger = false;
	bool playing = true;
	bool withoutIntro = true;
	bool debugPath = false;

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
	int zombieCount;
	
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

	int snd_hans;
	int snd_heinrich;
	int snd_halt;
	int snd_hmm;
	int snd_wasist;
	int snd_tiere;
	int snd_wounded;
	int snd_wounded_alt;
	int snd_gameOver;
};
