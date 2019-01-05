#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "olcPixelGameEngine.h"
#include <math.h>

#include "AnimationHandler.h"
#include "spr_sqn.h"
#include "Value_checker.h"


// all parts responsible in playing an animation will be moved into a class of its own, contained within an actor class


class Actor {

	//tools

	enum actions {	WALK, RUN, RELOAD, AIM, RECOIL, DIE, HURT, DIE2, GRAVE,
					CLIMB, PICK_UP, TIED, SIT, TIED_DIE, CARRIED, IDLE, SMOKE, ACTIONS_SIZE};
	enum facings {N = 2, NE = 3, E = 4, SE = 5, S = 6, SW = 7, W = 0, NW = 1, FACINGS_SIZE = 8};




public:
	Actor() = default;
	Actor (Vec2 loc, olc::PixelGameEngine* in_pge):
		location{loc},
		pge		{in_pge},
		speed	{80.0f},
		action	{ WALK },
		facing	{N},
		anm_hdl { ACTIONS_SIZE }
	{}


public:
	void draw();
	void load_spr_sheet(std::string adrs);
	void draw_centered(float x, float y, olc::Sprite* spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale) const;
	
	//temp
	void update (float fElapTm);
	int lookAtMouse();

private:
	void anim_loop(actions act, facings facing);
	bool anim_once(actions act, facings facing);
	int array_size(actions act, facings facing) const;	// build a function that checks values from start to end |||for (x : arr)||| and when it // meets x = 32167 it stops counting and returns the size
	
	void anim_que(actions act, bool loop);
	void anim_update();
	

	// Private Data Members
private:
	Vec2 location;
	Vec2 old_location;
	Vec2 velocity;
	float speed;

	AnimationHandler anm_hdl;
	Value_checker vc;

	olc::Sprite* spr = nullptr;
	olc::PixelGameEngine* pge;

	static constexpr int sqn_size = 8; // this is the greatest number of sequences of any given animation
	actions action;
	facings facing;
	float play_seq = 0.0f;
	float anim_speed = 3;				// might need an animation speed according to the size of the anim_seq

	bool busy = false;
	actions qued_anim = IDLE;
	actions current_anim = IDLE;
	bool loop = true;
	bool done_playing = true;

	float eTime = 0.0f;
};


