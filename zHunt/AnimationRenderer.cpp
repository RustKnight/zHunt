#include "AnimationRenderer.h"




void AnimationRenderer::update(float& elapT, const Vec2& loc, int face)
{

	anim_update();

	eTime = elapT;
	location = loc;
	facing = face;
}

void AnimationRenderer::get_spr_ptr(olc::Sprite* spr_in)
{
	spr = spr_in;
}



void AnimationRenderer::anim_loop(int act, int facing)
{
	int num_sequences = array_size(act, facing);
	play_seq += eTime * anim_speed;

	if (int(play_seq) >= num_sequences)
		play_seq = 0;


	const spr_sqn& requested_sqn = anm_hdl.get_coords(act, facing, int(play_seq));

	draw_centered(location.x, location.y, spr, requested_sqn.x, requested_sqn.y, requested_sqn.w, requested_sqn.h, 1);
}


bool AnimationRenderer::anim_once(int act, int facing)
{

	if (play_seq != 0 && done_playing)
		play_seq = 0;

	done_playing = false;

	int num_sequences = array_size(act, facing);
	play_seq += eTime * anim_speed;

	if (int(play_seq) >= num_sequences) {
		play_seq = 0;
		done_playing = true;
	}

	const spr_sqn& requested_sqn = anm_hdl.get_coords(act, facing, int(play_seq));

	draw_centered(location.x, location.y, spr, requested_sqn.x, requested_sqn.y, requested_sqn.w, requested_sqn.h, 1);
	return done_playing;
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


void AnimationRenderer::anim_que(int act, bool loop_in, float speed)
{
	anim_speed = speed;
	qued_anim = act;
	loop = loop_in;
}


void AnimationRenderer::anim_update()
{

	if (done_playing)
		current_anim = qued_anim;
	else
		loop = 0;


	// these 2 conditions control which anim function is called
	if (loop)
		anim_loop(current_anim, facing);
	else
		anim_once(current_anim, facing);
}
