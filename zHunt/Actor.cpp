#include "Actor.h"

void Actor::draw()
{
	draw_curr_anim(facing, action);
}


void Actor::draw_curr_anim(facings facing, actions act)
{
	int num_sequences = array_size(facing, act);

	play_seq += eTime * anim_speed;

	if (int(play_seq) >= num_sequences)
		play_seq = 0;
		
	
	draw_centered(location.x, location.y, spr, a3d_mapping_data[facing][act][int(play_seq)].x, a3d_mapping_data[facing][act][int(play_seq)].y, a3d_mapping_data[facing][act][int(play_seq)].w, a3d_mapping_data[facing][act][int(play_seq)].h, 2);
}

int Actor::array_size(facings facing, actions act) const
{
	for (int i = 0; i < 25; ++i)
		if (a3d_mapping_data[facing][act][i].x == 32167)
			return i;
}


void Actor::load_spr_sheet(std::string adrs)
{
	spr = new olc::Sprite{ adrs };
}



void Actor::draw_centered(float x, float y, olc::Sprite * spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale) const
{
	float center_x = x - (w*scale) / 2.0f;
	float center_y = y - (h*scale) / 2.0f;

	pge->DrawPartialSprite(int32_t (center_x), int32_t (center_y), spr, ox, oy, w, h, scale);
	
	
	pge->FillCircle(location.x, location.y, 2, olc::RED);
	pge->DrawRect(center_x, center_y, (w*scale), (h*scale));
}

void Actor::update(float fElapTm)
{
	eTime = fElapTm;
	old_location = location;

	if (pge->GetKey(olc::UP).bHeld)
		location.y -= fElapTm * speed;
	if (pge->GetKey(olc::DOWN).bHeld)
		location.y += fElapTm * speed;
	if (pge->GetKey(olc::LEFT).bHeld)
		location.x -= fElapTm * speed;
	if (pge->GetKey(olc::RIGHT).bHeld)
		location.x += fElapTm * speed;


	if (old_location != location)
		action = WALKING;
	else
		action = STANDING;
}



void Actor::load_mapping_info()
{
		a3d_mapping_data[S][STANDING][0] = spr_sqn {599, 452, 28, 41};
		a3d_mapping_data[S][STANDING][1] = spr_sqn {632, 452, 28, 39};
		a3d_mapping_data[S][STANDING][2] = spr_sqn {664, 452, 29, 40};
		a3d_mapping_data[S][STANDING][3] = spr_sqn {664, 452, 29, 40};
		a3d_mapping_data[S][STANDING][4] = spr_sqn {632, 452, 28, 39};
		a3d_mapping_data[S][STANDING][5] = spr_sqn {599, 452, 28, 41};

		a3d_mapping_data[S][WALKING][0] = spr_sqn{ 4,195,21,39 };
		a3d_mapping_data[S][WALKING][1] = spr_sqn{ 31,194,22,40 };
		a3d_mapping_data[S][WALKING][2] = spr_sqn{ 59,192,23,41 };
		a3d_mapping_data[S][WALKING][3] = spr_sqn{ 87,194,23,38 };
		a3d_mapping_data[S][WALKING][4] = spr_sqn{ 114,196,23,38 };
		a3d_mapping_data[S][WALKING][5] = spr_sqn{ 143,194,23,39 };
		a3d_mapping_data[S][WALKING][6] = spr_sqn{ 171,193,23,41 };
		a3d_mapping_data[S][WALKING][7] = spr_sqn{ 199,194,23,40 };
}

