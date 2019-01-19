#pragma once
#include "AnimationHandler.h"
#include "olcPixelGameEngine.h"
#include "spr_sqn.h"

#include "Vec2.h"


// request parameters should be some enums so they don't use magic numbers like 0, 1, etc.
// handle cases of facing where mirroring is needed
// watch out for proper facing allignment [file_read <-> with coded read]



class AnimationRenderer {
public:

	AnimationRenderer (olc::PixelGameEngine* pge_in, std::vector<std::string>& paths)
		:	pge {pge_in}, 
			anm_hdl{ paths },
			action{ -1 }, facing{ 0 }, play_seq {0}, eTime{0},
			task_done{false}, loop {true}, allow_interrupt {true}
	{}

	void request_animation(int act, bool interruptable, bool reversed, bool loop_in, bool back_and_forth, float speed);
	void update_and_play(float& elapT, const Vec2& loc, int face);


	void get_spr_ptr(olc::Sprite* spr_in);
	void update_offset(const Vec2& offset);

private:
	void draw_centered(float x, float y, olc::Sprite* spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, bool mirrored_x) const;
	
	
	

private:
	static constexpr int sqn_size = 8; // this is the greatest number of sequences of any given animation

	int action;
	int facing;

	float play_seq;
	float anim_speed;				// might need an animation speed according to the size of the anim_seq
	float eTime;
	

	bool allow_interrupt;
	bool back_forth;
	bool task_done;
	bool loop;
	bool increasing;
	bool reversed;

	olc::PixelGameEngine* pge;
	olc::Sprite* spr;
	AnimationHandler anm_hdl; // total animations 
	Vec2 location;
	Vec2 off_set;
};