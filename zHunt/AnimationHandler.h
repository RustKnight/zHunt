#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "spr_sqn.h"

using namespace std;


class AnimationHandler {
public:
	AnimationHandler() = default;
	AnimationHandler(int total_animations) :
		
		a3d_mapping_data (total_animations, vector<vector <spr_sqn>> (8, vector<spr_sqn>(8)))
	{
		load_mapping_info();
	}

	const spr_sqn& get_coords(int anim, int face, int sqn) const;


private:
	void load_mapping_info();

private:	
	vector<vector<vector <spr_sqn>>> a3d_mapping_data;
};