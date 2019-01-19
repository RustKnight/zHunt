#include "AnimationHandler.h"


const spr_sqn& AnimationHandler::get_coords(int anim, int face, int sqn) const
{
	return a3d_mapping_data[anim][face][sqn];
}

const int AnimationHandler::get_sqn_size(int anim, int face) const
{
	return a3d_mapping_data[anim][face].size();
}



void AnimationHandler::load_mapping_info(vector<string>& vec) {

	enum identifier { X, Y, W, H };
	vector<vector<vector <spr_sqn>>> animations;
	vector<vector <spr_sqn>> facings;
	vector <spr_sqn> sequences;


	for (string path : vec) {

		std::ifstream file{ path };
		if (!file.is_open()) {
			cout << "File not open.";
		}

		string str = "";
		int num;
		int id = 0;

		int anim;
		int face;
		int index = 0;

		int16_t x;
		int16_t y;
		int16_t w;
		int16_t h;

		bool comma_found = false;
		bool facing_complete = false;

		for (char ch; file.get(ch);) {

			if (ch == 'E')
				facing_complete = true;
			if (ch == ',')
				comma_found = true;


			if (comma_found) {

				if (isdigit(ch))
					str += ch;

				if (!str.empty() && !isdigit(ch)) {
					num = stoi(str);							// store the newly found number
					str = "";									// empty str

					switch (identifier(id)) {		// assign number to the correct object, based on id

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

					id++;										// increment id that controlls where the value of num is assigned 
				}

				if (ch == '\n') {								// end of line : reset id, use loaded values to create an spr_sqn object 
																// and assign to coresponding array index
					id = 0;
					comma_found = false;
					sequences.push_back(spr_sqn{ x, y, w, h });

					if (facing_complete) {
						facings.push_back(sequences);
						facing_complete = false;
						sequences.clear();
					}
				}

			}
		}
		//iter_swap(facings.begin() + 0, facings.begin() + 4);		// need to allign facings entry to match current system
		//iter_swap(facings.begin() + 1, facings.begin() + 5);		// order is N, N-E, E, S-E, S, S-W, W, N-W
		//iter_swap(facings.begin() + 2, facings.begin() + 6);
		//iter_swap(facings.begin() + 3, facings.begin() + 7);

		animations.push_back(facings);
		facings.clear();
	}

	a3d_mapping_data = animations;
}


// Legacy comment regarding previous version of the animation handler's resource loader

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