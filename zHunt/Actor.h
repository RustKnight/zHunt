#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "olcPixelGameEngine.h"
#include <math.h>

#include "AnimationRenderer.h"
#include "AnimationHandler.h"
#include "spr_sqn.h"
#include "Value_checker.h"



class Actor {

	
	// WARNING temp swap AIM with IDLE
	//enum actions {IDLE, CARRIED, CLIMB, DIE, DIE_TIED, DIE2, FIRE, GRAVE, HIT, AIM,
	//				PICK, RELOAD, RUN, SIT, SMOKE, TIED, WALK, ACTIONS_SIZE};
	enum actions {AIM, CLIMB, IDLE, PICK, RUN, WALK };
	enum facings {N, NE, E, SE, S, SW, W, NW, FACINGS_SIZE = 8};

	enum interr {NOT_INTERRUPTABLE, INTERRUPTABLE};
	enum reversed {NOT_REVERESED, REVERSED};
	enum loop {NOT_LOOPED, LOOPED};
	enum back_forth {NOT_BACK_FORTH, BACK_FORTH};

	//enum animation_states { INTERRUPTABLE, REVERSED, LOOP, BACK_FORTH }; junk


public:
	Actor() = default;

	Actor (Vec2 loc, olc::PixelGameEngine* in_pge, vector<string>& paths):
		isPlayer{false},
		location{loc},
		pge		{in_pge},
		speed	{0.8f},
		action	{ IDLE },
		facing	{N},
		renderer{ in_pge,  paths }
	{}

	Actor(Vec2 loc, olc::PixelGameEngine* in_pge, vector<string>& paths, bool is_player) :
		isPlayer{ is_player },
		location{ loc },
		pge{ in_pge },
		speed{ 0.8f },
		action{ IDLE },
		facing{ N },
		renderer{ in_pge, paths }
	{}



public:
	void load_spr_sheet(std::string adrs);
	
	void update (float fElapTm, const Vec2& cam_off);
	facings lookAtMouse();
	bool walking_backwards();

	Vec2 get_location();
	AnimationRenderer renderer;
private:
	
	
private:
	bool isPlayer;

	Vec2 location;
	Vec2 old_location;

	Vec2 camera_offset;
	Vec2 mouse_to_player_distance;
	Vec2 velocity;
	float speed;
	float eTime = 0.0f;

	Value_checker vc;
	vector <olc::Sprite*> vSpriteSheetPointers;
	olc::PixelGameEngine* pge;

	actions action;
	facings facing;
};

