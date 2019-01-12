#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "olcPixelGameEngine.h"
#include <math.h>

#include "AnimationRenderer.h"
#include "AnimationHandler.h"
#include "spr_sqn.h"
#include "Value_checker.h"


// all parts responsible in playing an animation will be moved into a class of its own, contained within an actor class


class Actor {

	//tools

	enum actions {	WALK, RUN, RELOAD, AIM, RECOIL, DIE, HURT, DIE2, GRAVE,
					CLIMB, PICK_UP, TIED, SIT, TIED_DIE, CARRIED, IDLE, SMOKE, ACTIONS_SIZE};
	enum facings {N = 2, NE = 3, E = 4, SE = 5, S = 6, SW = 7, W = 0, NW = 1, FACINGS_SIZE = 8};

	enum interr {NOT_INTERRUPTABLE, INTERRUPTABLE};
	enum reversed {NOT_REVERESED, REVERSED};
	enum loop {NOT_LOOPED, LOOPED};
	enum back_forth {NOT_BACK_FORTH, BACK_FORTH};

	//enum animation_states { INTERRUPTABLE, REVERSED, LOOP, BACK_FORTH }; junk


public:
	Actor() = default;
	Actor (Vec2 loc, olc::PixelGameEngine* in_pge):
		location{loc},
		pge		{in_pge},
		speed	{0.8f},
		action	{ IDLE },
		facing	{N},
		renderer{ in_pge,  ACTIONS_SIZE }
	{
	}


public:
	void load_spr_sheet(std::string adrs);
	
	void update (float fElapTm, const Vec2& cam_off);
	int lookAtMouse();
	bool walking_backwards();

	Vec2 get_location();
	AnimationRenderer renderer;
private:
	
	
private:
	//string dest{ "C://Users//Carmen//Desktop//output.txt" };
	//ofstream out{ dest };
	
	Vec2 location;
	Vec2 old_location;

	Vec2 camera_offset;
	Vec2 mouse_to_player_distance;
	Vec2 velocity;
	float speed;
	float eTime = 0.0f;

	Value_checker vc;
	olc::Sprite* spr = nullptr;
	olc::PixelGameEngine* pge;

	actions action;
	facings facing;

	float dx;
	float dy;
};


