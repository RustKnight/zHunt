#include "AnimationRenderer.h"


void AnimationRenderer::request_animation(int act, olc::Sprite* spr_in, bool interruptable, bool reversed_in, bool loop_in, bool back_and_forth, float speed)
{
	// 0 = Walk, 1 = Run; moving always cancels whatever anim you're playing

	if (allow_interrupt || task_done || act == 4 || act == 5) {	// check if we should allow incoming animation // WARNING hardcoded exceptions, for walk and run // basically move animations
	
		if (act == action && reversed != reversed_in) {

			action = act;
			spr = spr_in;
			allow_interrupt = interruptable;
			reversed = reversed_in;
			loop = loop_in;
			back_forth = back_and_forth;
			anim_speed = speed;

			increasing = !increasing;
		}

		if (act != action) {

			action = act;
			spr = spr_in;
			allow_interrupt = interruptable;
			reversed = reversed_in;
			loop = loop_in;
			back_forth = back_and_forth;
			anim_speed = speed;

			if (reversed) {
				play_seq = float (anm_hdl.get_sqn_size(action, facing));
				increasing = false;
			}
			else {
				play_seq = 0;
				increasing = true;
			}
		}
	}
}


void AnimationRenderer::update_and_play(float& elapT, const Vec2& loc, int face)
{
	eTime = elapT;
	location = loc;
	facing = face;
	task_done = false;
	// update carried out
	bool mirror = false;

	// code that handles mirroring in case of non indexed facing
	// N-0, NE-1, E-2, SE-3, S-4, SW-5, W-6, NW-7.
	if (facing == 5 || facing == 6 || facing == 7) {
		switch (facing) {
		case 5: facing = 3; break;
		case 6: facing = 2; break;
		case 7: facing = 1; break;
		}
		mirror = true;
	}

	int num_sequences = anm_hdl.get_sqn_size(action, facing);

//	cout << "increasing: " << increasing << endl;
		if (increasing)
			play_seq += eTime * anim_speed;
		else
			play_seq -= eTime * anim_speed;


		if (int(play_seq) >= num_sequences || play_seq < 0) {	// we either reached the start or the end of our interval; 

			if (back_forth) {
				if (increasing == false)  /// we finished decreasing and want to increase
					play_seq = 1;		  /// set play_seq to 0 // or to 1 if we want small delay
				else
					play_seq = float (num_sequences - 1);
				
				increasing = !increasing;
			}

			else if (!reversed)
				play_seq = 0;
			else if (reversed)
				play_seq = num_sequences - 0.000001f;

			if (!loop && !back_forth) //one time
				task_done = true; // could have used allow_interrupt as bool, but chose another for clarity
		}
	//	cout << play_seq << endl;


	const spr_sqn& requested_sqn = anm_hdl.get_coords(action, facing, int(play_seq));

	// maybe we shouldn't try to draw if off the screen
	draw_centered((location.x - off_set.x) * 128, (location.y - off_set.y) * 128, spr, requested_sqn.x, requested_sqn.y, requested_sqn.w, requested_sqn.h, 2, mirror);
//	pge->DrawPartialSprite_BottomUp( (location.x - off_set.x) * 128, (location.y - off_set.y) * 128, spr, requested_sqn.x, requested_sqn.y, requested_sqn.w, requested_sqn.h, 1);
	//cout << play_seq << endl;
}




void AnimationRenderer::get_spr_ptr(olc::Sprite* spr_in)
{
	spr = spr_in;
	cout << spr << endl;
}

void AnimationRenderer::update_offset(const Vec2& offset)
{
	off_set = offset;
}





void AnimationRenderer::draw_centered(float x, float y, olc::Sprite * spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, bool mirrored_x) const
{
	float center_x = x - (w*scale) / 2.0f;
	float center_y = y + (h*scale) / 2.0f;

	if (mirrored_x)
		pge->DrawPartialSprite_BottomUp_mirrored_horizontally(int32_t(center_x), int32_t(center_y), spr, ox, oy, w, h, scale);
	else
		pge->DrawPartialSprite_BottomUp(int32_t(center_x), int32_t(center_y), spr, ox, oy, w, h, scale);
	
	//pge->FillCircle(400, 300, 2, olc::RED);
	//pge->DrawRect(int32_t(center_x), int32_t(center_y) - h * scale, (w*scale), (h*scale));
}




