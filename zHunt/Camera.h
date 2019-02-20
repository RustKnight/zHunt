#pragma once
#include "olcPixelGameEngine.h"
#include "Vec2.h"

#include "Map.h"

class Camera {
public:
	Camera(olc::PixelGameEngine* pge_in, Map* map_in, int winW, int winH, Vec2 subject_pos) :
		pge{ pge_in }, map{ map_in }, window_width {winW}, window_height{ winH }, cameraPos_x{ subject_pos.x }, cameraPos_y{ subject_pos.y }
	{}

public:
	void load_fields(std::string adrs);
	void update(Vec2 actor_loc);
	void screen_in_view();

	Vec2 get_offset();

private:
	olc::PixelGameEngine* pge;
	olc::Sprite* fields;
	Map* map;

	int window_width;
	int window_height;

	int tile_width = 128;
	int tile_height = 128;
	int tiles_visible_x = window_width / tile_width;
	int tiles_visible_y = window_height / tile_height;

	float cameraPos_x = 0.0f;
	float cameraPos_y = 0.0f;
	float offset_x;
	float offset_y;

	float fTileOffsetX;
	float fTileOffsetY;
};