#pragma once
#include "AnimationHandler.h"
#include "olcPixelGameEngine.h"
#include "spr_sqn.h"

#include "Vec2.h"
#include "RenderRect.h"

// request parameters should be some enums so they don't use magic numbers like 0, 1, etc.

// WARNING Renderer MUST know which animations move the player, in order to be able to stop other animations.
// currently hardcoded

// WARNING - CURRENTLY RENDERER IS CALIBRATED FOR SPRITES THAT NEED MIRRORING TO COMPENSATE FOR INCOMPLETE FACINGS
// ZOMBIE WILL HAVE ALL 8 FACINGS



class AnimationRenderer {
public:

	AnimationRenderer(olc::PixelGameEngine* pge_in)
		: pge{ pge_in },
		action{ -1 }, facing{ 0 }, play_seq{ 0 }, eTime{ 0 },
		task_done{ false }, loop{ true }, allow_interrupt{ true }, animationCount {0}
	{}



	void request_animation(int act, olc::Sprite* spr_in, bool interruptable, bool reversed, bool loop_in, bool back_and_forth, bool end_lock_in, float speed);
	void override (int act, olc::Sprite* spr_in, bool interruptable, bool reversed, bool loop_in, bool back_and_forth, bool end_lock_in, float speed);
	void update_and_play(float& elapT, const Vec2& loc, int face);
	bool get_task_status();

	int get_animation_seqences_count(int act, int facing) const;
	int get_current_anim() const;
	void get_spr_ptr(olc::Sprite* spr_in);
	void update_offset(const Vec2& offset);
	AnimationHandler effects_handler;
	olc::Sprite* effects_sprite_sheet;
	RenderRect get_render_rect() const;
	void portalToggle();
	int getAnimCount() const;

	void passMappingData(vector <string> in_map);

	int animationCount;

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
	bool isPortal = false;
};