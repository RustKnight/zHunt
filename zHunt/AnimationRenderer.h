#pragma once
#include "AnimationHandler.h"
#include "olcPixelGameEngine.h"
#include "spr_sqn.h"

#include "Vec2.h"


// needs to know about SQNs and must have an AnimationRenderer object, PixelGE

// checks on update (elapsed time)

// request parameters (anim [loop, once, back/forth], play_speed


class AnimationRenderer {
public:

	AnimationRenderer (olc::PixelGameEngine* pge_in, int tot_anim)
		:	pge {pge_in}, 
			action {0}, 
			facing {0}, 
			anm_hdl{ tot_anim }		
	{}

	void anim_que(int act, bool loop, float speed);
	void anim_update();
	void update(float& elapT, const Vec2& loc, int face);
	void get_spr_ptr(olc::Sprite* spr_in);


private:
	void draw_centered(float x, float y, olc::Sprite* spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale) const;
	void anim_loop(int act, int facing);
	bool anim_once(int act, int facing);
	int array_size(int act, int facing) const;	// build a function that checks values from start to end |||for (x : arr)||| and when it // meets x = 32167 it stops counting and returns the size

	


private:
	static constexpr int sqn_size = 8; // this is the greatest number of sequences of any given animation

	int action;
	int facing;
	int current_anim = 0;
	int qued_anim = 0;

	float play_seq = 0.0f;
	float anim_speed;				// might need an animation speed according to the size of the anim_seq
	float eTime = 0.0f;

	bool busy = false;
	bool loop = true;
	bool done_playing = true;

	olc::PixelGameEngine* pge;
	olc::Sprite* spr;
	AnimationHandler anm_hdl; // total animations 
	Vec2 location;
};