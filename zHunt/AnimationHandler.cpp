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



	for (string path : vec) {				// read loop for all animations files

		std::ifstream file{ path };
		if (!file.is_open()) {				
			cout << "File not open.";
		}

		string str = "";
		int num;
		int id = 0;
		
		int16_t x;
		int16_t y;
		int16_t w;
		int16_t h;
				

		for (char ch; file.get(ch);) {				// read loop for entire file


			if (facings_entry_loaded(ch)) {

				if (ch == '<')
					facing_complete = true;
				if (ch == ',')
					comma_found = true;


				if (comma_found) {


					if (facings_order_spritesheet.empty())
						cout << "Facings entry order was not read!\n";

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
		}

		

		int limit = facings.size();				// need an external stop condition for loop. otherwise, since vector limit keeps changing, stop condition will never hit
		for (int i = 0; i < limit; ++i)
			facings.push_back(facings[i]);		// we make some room for swaping operation, by expanding the vector 2times with the same values

		int copied_values_offset = facings_order_spritesheet.size();	// index from where our copied values start 

		for (int i = 0; i < facings_order_spritesheet.size(); ++i)		// use read in facings to arrange them properly
			iter_swap(facings.begin() + facings_order_spritesheet[i], facings.begin() + (i + copied_values_offset));

		facings.resize	(facings_order_spritesheet.size());			// get rid of coppied values

		animations.push_back(facings);
		facings.clear();
		facings_order_spritesheet.clear();
	}

	if (!facings_entry_loaded(' '))
		cout << "Sprites facing order of entry was not read!\n";

	a3d_mapping_data = animations;
}

void AnimationHandler::load_mapping_info_string(string s)
{
	odd_mapping.push_back(s);
	load_mapping_info(odd_mapping);
}


bool AnimationHandler::facings_entry_loaded(char ch)
{

	if (ch == '$')
		read_facings_order = !read_facings_order;

	if (read_facings_order) {				//	as long as we're reading facings order, don't start saving coords yet
		if (isdigit(ch)) {
			string s;
			s += ch;
			facings_order_spritesheet.push_back(stoi(s));
		}
		return false;
	}

	return true;
}




// must first be able to read the order of facings before starting to load mapping data
// copy all facings in continuation of the first series Ex : 0, 1, 2, 3 SIZE -> 4		; copy
//															0, 1, 2, 3 / 4 [0], 5 [1], 6 [2], 7 [3] -> SIZE 8
// swap first copied member with first !!value!! of order of facings
// swap second copied member with second !!value!! of order of facings
// delete surplus
// facings are now alligned with actor ENUMs