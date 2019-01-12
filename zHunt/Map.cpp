#include "Map.h"


	wchar_t Map::get_tile(int x, int y){


		if (x >= 0 && x < map_width && y >= 0 && y < map_height)
			return karte[y * map_width + x];
		else
			return L' ';
	}


	void Map::set_tile(int x, int y, wchar_t c)
	{	
			if (x >= 0 && x < map_width && y >= 0 && y < map_height)
				karte[y * map_width + x] = c;
	}

	int Map::get_width()
	{
		return map_width;
	}
	

	int Map::get_height()
	{
		return map_height;
	}


