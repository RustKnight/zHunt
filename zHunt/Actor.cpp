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
	

	draw_centered(location.x, location.y, spr, a3d_mapping_data[act][facing][int(play_seq)].x, a3d_mapping_data[act][facing][int(play_seq)].y, a3d_mapping_data[act][facing][int(play_seq)].w, a3d_mapping_data[act][facing][int(play_seq)].h, 2);
}


int Actor::array_size(facings facing, actions act) const
{
	for (int i = 0; i < sqn_size; ++i)
		if (a3d_mapping_data[act][facing][i].x == 32167)
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
	
	pge->FillCircle(400, 300, 2, olc::RED);
	pge->DrawRect(int32_t(center_x), int32_t(center_y) - h * scale, (w*scale), (h*scale));

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
		

	//if (old_location != location)
	//	action = WALK;
	//else
	//	action = WALK;
}



void Actor::load_mapping_info()
{
	using namespace std;
	// index of 3d array will be requested on demand by file input. loop no longer needed. 
	// data will have 3 ints and 4 ints - first int is the anim type, second will be facing, the int after will be
	// the number of the anim seq, respectivly the third array index. These 3 ints before the actual coords will be responsible
	// to set the correct array indexes before writting the actual data to it

	//	for (int act = 0; act < actions; ++act
	//		for (int facing = 0; facing < facings; ++facing
	//			for (int sqn = 0; sqn < total_sqn; ++sqn			
	//				a3d_mapping_data[act][facing][sqn] = text_file_input

	/*read values of interest (individually?) and store them in named ints (x,y,w,h), use ints to init. spr_sqn and assign*/
	/*figure out how to properly read values from a txt and develop method of accurate association between array and read values */
	// run through all stored animations and test them if they work properly

	// ask on discord after implementation is done, how it should been the "better" way of doing this

	string dest = "C:\\Users\\Carmen\\source\\repos\\zHunt\\zHunt\\sprites_mapping.txt";
	std::ifstream file{ dest };
	enum identifier { ACTION, FACING, SQN, X, Y, W, H };




	if (!file.is_open()) {
		cout << "File not open.";
	}

	string str = "";
	int num;
	int id = 0;

	actions anim;
	facings face;
	int index = 0;

	int16_t x;
	int16_t y;
	int16_t w;
	int16_t h;


	for (char ch; file.get(ch);) {

		if (isdigit(ch))
			str += ch;

		// if we have a digit/s and the incoming char is not a digit, it means we have the entire number
		if (!str.empty() && !isdigit(ch)) {
			num = stoi(str);				// store the newly found number
			str = "";						// empty str

			switch (identifier(id)) {		// assign number to the correct object, based on id

			case ACTION:
				anim = actions (num);
				break;
			case FACING:
				face = facings (num);
				break;
			case SQN:
				index = num;
				break;
			case X:
				x = num;
				break;
			case Y:
				y = num;
				break;
			case W:
				w = num;
				break;
			case H:
				h = num;
				break;
			}

			id++;				// increment id that controlls where the value of num is assigned 
		}


		if (ch == '\n') {		// end of line : reset id, use loaded values to create an spr_sqn object 
								// and assign to coresponding array index
			id = 0;
			a3d_mapping_data[anim][face][index] = spr_sqn{ x, y, w, h };
		}
	}


	//	a3d_mapping_data[N][WALKING][0] = spr_sqn	{ 4,195,21,39	};
		
}


