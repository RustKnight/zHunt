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
	
	
	// stop randomizing zombie spawn
	// maybe AI can look at the same point (mouse loc) as player if no target present
	// if you run to portal - Hans doesn't face properly
	// maybe Heinrich says "Ein Verletzter!" then Halt

	class Scripter {
	public:
		Scripter (zHunt* pZ): z{pZ}, scriptState { 0 }
		{}

		enum scriptStates {WALK_TO_HEINRICH, SND_HANS, SND_HEINRICH, LOOK_WEST, PAN_WEST_PORTAL, OPEN_WEST_PORTAL,
							PAN_BACK_FAST, GET_CLOSE, ASK_GET_ANSWER, HANS_ALLIGN, Z_APPROACH		};

		bool playScript(float eTime) {

			switch (scriptState) {

			case WALK_TO_HEINRICH:


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
					z->zSpawn.spawnZat(2); // 2 is our east spawn portal
					resetSpecialStates();
					z->ai.moveTo((z->vRifles[0]->get_location() + Vec2{ -0.6f, -0.4 }));
					scriptState++;
				}
				
				break;

			case HANS_ALLIGN:
							
				if (z->ai.noMoveOrders()) {
					z->vRifles[0]->setGoal(z->vZombies[0]->get_location());	// needed to make him face correctly
					z->vRifles[0]->set_facing(6);
					scriptState++;
				}
				break;

			case Z_APPROACH: 

				z->toggle_hunger = true; 

				if (z->vZombies[0]->withinDistance(z->vRifles[1]->get_location(), 85000)) {
					playSound(eTime, z->snd_halt);
					z->vRifles[0]->aim();				
				}

				if (z->vZombies[0]->withinDistance(z->vRifles[1]->get_location(), 40000)) {
					z->ai.toggleAggro();
					resetSpecialStates();
					scriptState++;
				}


				break;










			default:
				z->vRifles[1]->isActive = true;
				isOn = false;
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

	int snd_hans;
	int snd_heinrich;
	int snd_halt;
	int snd_hmm;
	int snd_wasist;
	int snd_tiere;
};
