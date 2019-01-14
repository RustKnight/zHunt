#include "AnimationHandler.h"


const spr_sqn& AnimationHandler::get_coords(int anim, int face, int sqn) const
{
	return a3d_mapping_data[anim][face][sqn];
}



void AnimationHandler::load_mapping_info()
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

		string dest = "sprites_mapping.txt";
		std::ifstream file{ dest };
		enum identifier { ACTION, FACING, SQN, X, Y, W, H };


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


		for (char ch; file.get(ch);) {

			if (isdigit(ch))
				str += ch;

															// if we have a digit/s and the incoming char is not a digit, it means we have the entire number
			if (!str.empty() && !isdigit(ch)) {
				num = stoi(str);							// store the newly found number
				str = "";									// empty str
					
				switch (identifier(id)) {		// assign number to the correct object, based on id

				case ACTION:
					anim = num;
					break;
				case FACING:
					face = num;
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

				id++;										// increment id that controlls where the value of num is assigned 
			}


			if (ch == '\n') {								// end of line : reset id, use loaded values to create an spr_sqn object 
															// and assign to coresponding array index
				id = 0;
				a3d_mapping_data[anim][face][index] = spr_sqn{ x, y, w, h };
			}
		}

	}




