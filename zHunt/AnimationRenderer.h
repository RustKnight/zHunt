#pragma once
#include "AnimationHandler.h"
#include "olcPixelGameEngine.h"
#include "spr_sqn.h"

#include "Vec2.h"
#include "Projectile.h"

// request parameters should be some enums so they don't use magic numbers like 0, 1, etc.

// WARNING Renderer MUST know which animations move the player, in order to be able to stop other animations.
// currently hardcoded

// WARNING - CURRENTLY RENDERER IS CALIBRATED FOR SPRITES THAT NEED MIRRORING TO COMPENSATE FOR INCOMPLETE FACINGS
// ZOMBIE WILL HAVE ALL 8 FACINGS

struct RenderRect {

	void get_dim (int xx, int yy, int wwidth, int hheight) {

		x = xx;
		y = yy;
		width = wwidth;
		height = hheight;

		top = y;
		bottom = y + height;
		left = x;
		right = x + width;
	}

	int top = 0;
	int bottom = 0;
	int left = 0;
	int right = 0;

private:
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;	
};


class AnimationRenderer {
public:

	AnimationRenderer(olc::PixelGameEngine* pge_in)
		: pge{ pge_in },
		action{ 0 }, facing{ 0 }, play_seq{ 0 }, eTime{ 0 },
		task_done{ false }, loop{ true }, allow_interrupt{ true }
	{}

	AnimationRenderer (olc::PixelGameEngine* pge_in, std::vector<std::string>& paths)
		:	pge {pge_in}, 
			anm_hdl{ paths },
			action{ -1 }, facing{ 0 }, play_seq {0}, eTime{0},
			task_done{false}, loop {true}, allow_interrupt {true}
	{}

	void request_animation(int act, olc::Sprite* spr_in, bool interruptable, bool reversed, bool loop_in, bool back_and_forth, bool end_lock_in, float speed);
	void update_and_play(float& elapT, const Vec2& loc, int face);


	void get_spr_ptr(olc::Sprite* spr_in);
	void update_offset(const Vec2& offset);
	bool check_collision(Projectile& bullet);
	AnimationHandler effects_handler;
	olc::Sprite* effects_sprite_sheet;

private:
	void draw_centered(float x, float y, olc::Sprite* spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, bool mirrored_x);	

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
	bool end_lock;

	olc::PixelGameEngine* pge;
	olc::Sprite* spr;
	spr_sqn requested_sqn;
	AnimationHandler anm_hdl; // total animations 
	Vec2 location;
	Vec2 off_set;

	RenderRect r_rect;
	bool colliding = false;
};