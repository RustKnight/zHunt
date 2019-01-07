#include "AnimationRenderer.h"


void AnimationRenderer::request_animation(int act, bool interruptable, bool loop_in, bool back_and_forth, float speed)
{
	// 0 = Walk, 1 = Run; moving always cancels whatever anim you're playing

	if (act != action && (allow_interrupt || task_done || act == 0 || act == 1)) {	// check if we should allow incoming animation
		play_seq = 0;

		action = act;
		allow_interrupt = interruptable;
		loop = loop_in;
		back_forth = back_and_forth;
		anim_speed = speed;
	}
}


void AnimationRenderer::play_animation(float& elapT, const Vec2& loc, int face)
{
	eTime = elapT;
	location = loc;
	facing = face;
	task_done = false;

	int num_sequences = array_size(action, facing);
	play_seq += eTime * anim_speed;


		if (int(play_seq) >= num_sequences) {
			play_seq = 0;

			if (!loop)
				task_done = true; // could have used allow_interrupt as switch, but chose another bool for clarity
		}


	const spr_sqn& requested_sqn = anm_hdl.get_coords(action, facing, int(play_seq));

	draw_centered(location.x, location.y, spr, requested_sqn.x, requested_sqn.y, requested_sqn.w, requested_sqn.h, 1);
}



void AnimationRenderer::get_spr_ptr(olc::Sprite* spr_in)
{
	spr = spr_in;
}



int AnimationRenderer::array_size(int act, int facing) const
{
	for (int i = 0; i < sqn_size; ++i)
		if (anm_hdl.get_coords(act, facing, i).x == 32167)
			return i;

	return sqn_size;
}



void AnimationRenderer::draw_centered(float x, float y, olc::Sprite * spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale) const
{
	float center_x = x - (w*scale) / 2.0f;
	float center_y = y + (h*scale) / 2.0f;

	pge->DrawPartialSprite_BottomUp(int32_t(center_x), int32_t(center_y), spr, ox, oy, w, h, scale);

	//pge->FillCircle(400, 300, 2, olc::RED);
	//pge->DrawRect(int32_t(center_x), int32_t(center_y) - h * scale, (w*scale), (h*scale));
}




