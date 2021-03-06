#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "olcPixelGameEngine.h"
#include "olcPGEX_Sound.h"
#include <math.h>

#include "AnimationRenderer.h"
#include "AnimationHandler.h"
#include "spr_sqn.h"
#include "Value_checker.h"
#include "RectF.h"




class Actor {

	class DistanceCheck {
	public:

		bool inRange(Vec2 goal_in, Vec2 location_in, int range_in) {

			innerCircle = range_in;
			outerCircle = innerCircle * 1.60;

			float x = (goal_in.x) * 128;
			float y = (goal_in.y) * 128;

			Vec2 distance = Vec2{ x, y } - location_in * 128;


			if (!inInnerCircle) {
				if (distance.GetLengthSq() < innerCircle) {
					inInnerCircle = true;
					return true;	//stop moving
				}
				else
					return false;
			}

			else {
				if (distance.GetLengthSq() < outerCircle) {
					return true;	//stop moving
				}
			}


			inInnerCircle = false;
			return false;	// need to move
		}

	private:
		int innerCircle;
		int outerCircle; 
		bool inInnerCircle = false;
	};


	
	// WARNING temp swap AIM with IDLE
	//enum actions {IDLE, CARRIED, CLIMB, DIE, DIE_TIED, DIE2, FIRE, GRAVE, HIT, AIM,
	//				PICK, RELOAD, RUN, SIT, SMOKE, TIED, WALK, ACTIONS_SIZE};

protected:
	enum facings {N, NE, E, SE, S, SW, W, NW, FACINGS_SIZE = 8};


	enum interr {NOT_INTERRUPTABLE, INTERRUPTABLE};
	enum reversed {NOT_REVERESED, REVERSED};
	enum loop {NOT_LOOPED, LOOPED};
	enum back_forth {NOT_BACK_FORTH, BACK_FORTH};

	//enum animation_states { INTERRUPTABLE, REVERSED, LOOP, BACK_FORTH }; junk


public:
	Actor() = default;

	Actor (Vec2 loc, olc::PixelGameEngine* in_pge):
		isPlayer{false},
		location{loc},
		pge		{in_pge},
		speed	{1.3f},
		facing	{N},
		renderer{ in_pge},
		isActive {true}		
	{}


public:
	
	virtual bool update (float fElapTm, const Vec2& cam_off);
	void draw();

	int get_facing(Vec2 pos);
	void set_facing(int face);
	bool walking_backwards();
	void take_damage(int damage);
	void become_player(bool toggle);
	void setGoal(Vec2 goal);
	Vec2 getGoal() const;
	bool moveTowardsGoal(float speed);
	void look_at_vec(Vec2 pos);
	bool withinOwnRect(Vec2 location) const;
	bool withinDistance(Vec2 location, int dist_radius);
	float LengthSq2Vec(Vec2* a, Vec2* b);
	bool keepOnMap();

	bool shot = false;
	bool moving = false;
	bool running = false;

	
	int desiredPrtIndex = 0;
	void load_assets(vector<string> in_mappings);
	Vec2 get_location() const;
	void set_location(Vec2 loc);
	float timeSinceLastTele = 1000;
	AnimationRenderer renderer;
	bool finishedDieing = true;
	
	int hp;
	bool alive;
	bool hit;
	bool isActive;
	bool visible = true;

protected:
	bool isPlayer;
	
	
	Vec2 goal;
	Vec2 location;
	Vec2 old_location;
	vector <olc::Sprite*>* vSpriteSheetPointers;

	Vec2 camera_offset;
	Vec2 mouse_to_player_distance;
	Vec2 velocity;
	float speed;
	float eTime = 0.0f;

	DistanceCheck distanceCheck;
	Value_checker vc;
	
	olc::PixelGameEngine* pge;

	facings facing;
};

