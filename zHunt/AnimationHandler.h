#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "spr_sqn.h"

using namespace std;



/// Animation Handler could/should be broken down into functions (Ex: read sprite facing order, reorder facings sprites, and possibly more).


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
	bool facings_entry_loaded(char ch);


private:	
	bool comma_found = false;
	bool facing_complete = false;
	bool read_facings_order = false;
	vector<vector<vector <spr_sqn>>> a3d_mapping_data;
	vector <int> facings_order_spritesheet;
};