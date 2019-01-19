#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "spr_sqn.h"

using namespace std;

// must first be able to read the order of facings before starting to load mapping data
// copy all facings in continuation of the first series Ex : 0, 1, 2, 3 SIZE -> 4		; copy
//															0, 1, 2, 3 / 4 [0], 5 [1], 6 [2], 7 [3] -> SIZE 8
// swap first copied member with first !!value!! of order of facings
// swap second copied member with second !!value!! of order of facings
// delete surplus
// facings are now alligned with actor ENUMs

class AnimationHandler {
public:
	AnimationHandler() = default;

	AnimationHandler(vector<string>& paths)
	{
		load_mapping_info(paths);
	}

	const spr_sqn& get_coords(int anim, int face, int sqn) const;
	const int get_sqn_size(int anim, int face) const;

private:
	void load_mapping_info(vector<string>& vec);

private:	
	vector<vector<vector <spr_sqn>>> a3d_mapping_data;
};