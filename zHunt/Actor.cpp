#include "Actor.h"

void Actor::draw()
{
	anim_loop(action, facing);

}



void Actor::anim_loop(actions act, facings facing)
{
	int num_sequences = array_size(act, facing);
	play_seq += eTime * anim_speed;

	if (int(play_seq) >= num_sequences)
		play_seq = 0;
	

	const spr_sqn& requested_sqn = anm_hdl.get_coords(act, facing, int(play_seq));
	
	draw_centered(location.x, location.y, spr, requested_sqn.x, requested_sqn.y, requested_sqn.w, requested_sqn.h, 1);
}


bool Actor::anim_once(actions act, facings facing)
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


int Actor::array_size(actions act, facings facing) const
{
	for (int i = 0; i < sqn_size; ++i)
		if (anm_hdl.get_coords(act, facing, i).x == 32167)
			return i;

	return sqn_size;
}



void Actor::load_spr_sheet(std::string adrs)
{
	spr = new olc::Sprite{ adrs };
}



void Actor::draw_centered(float x, float y, olc::Sprite * spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale) const
{
	float center_x = x - (w*scale) / 2.0f;
	float center_y = y + (h*scale) / 2.0f;

	pge->DrawPartialSprite_BottomUp(int32_t(center_x), int32_t(center_y), spr, ox, oy, w, h, scale);
	
	//pge->FillCircle(400, 300, 2, olc::RED);
	//pge->DrawRect(int32_t(center_x), int32_t(center_y) - h * scale, (w*scale), (h*scale));
}


void Actor::anim_que(actions act, bool loop_in)
{	
	qued_anim = act;
	loop = loop_in;
}


void Actor::anim_update()
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


int Actor::lookAtMouse()
{
#define PI 3.14159265

	// we determine the vector between the mouse position and the location of the character
	float dx = pge->GetMouseX() - location.x;
	float dy = pge->GetMouseY() - location.y;
	
	float angle = atan2(dy,dx);
	angle = roundf (angle / ((2 * PI) / 8) + 4);
	if (angle == 8)
		angle = 0;

	switch (int (angle) ) {
		//N = 2, NE = 3, E = 4, SE = 5, S = 6, SW = 7, W = 0, NW = 1,
	case 0 :
		angle = 6;
		break;
	case 1:
		angle = 7;
		break;
	case 2:
		angle = 0;
		break;
	case 3:
		angle = 1;
		break;
	case 4:
		angle = 2;
		break;
	case 5:
		angle = 3;
		break;
	case 6:
		angle = 4;
		break;
	case 7:
		angle = 5;
		break;
	}

	return angle;
}



void Actor::update(float fElapTm)
{
	eTime = fElapTm;
	old_location = location;
	facing = facings(lookAtMouse());

	anim_update();

	if (pge->GetKey(olc::UP).bHeld)
		location.y -= fElapTm * speed;
	if (pge->GetKey(olc::DOWN).bHeld)
		location.y += fElapTm * speed;
	if (pge->GetKey(olc::LEFT).bHeld)
		location.x -= fElapTm * speed;
	if (pge->GetKey(olc::RIGHT).bHeld)
		location.x += fElapTm * speed;

	if (pge->GetKey(olc::W).bPressed) {
		int ac = int(action);
		ac++;
		action = actions(ac);
	}

	if (pge->GetKey(olc::S).bPressed) {
		int ac = int(action);
		ac--;
		action = actions(ac);
	}

	if (pge->GetKey(olc::P).bPressed) {
		anim_que(PICK_UP, 0);
	}

	else if (pge->GetKey(olc::K).bPressed) {
		anim_que(SMOKE, 0);
	}

	else if (old_location != location) {
		anim_que(WALK, 1);
		//done_playing = true;  dirty way of stoping a play_once animation
	}

	else
		anim_que(IDLE, 1);

}	




