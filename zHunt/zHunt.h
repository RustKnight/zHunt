#pragma once
#include "olcPixelGameEngine.h"
#include "RectF.h"
#include "Vec2.h"
#include "Actor.h"
#include "Map.h"
#include "Value_checker.h"


class zHunt : public olc::PixelGameEngine
{
public:
	zHunt();

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	//tool functions
	Vec2 placeInCenter() const;

	//getters
	float getWinWidth()	const;
	float getWinHeight()const;


private:
	float winWidth;
	float winHeight;
	Map map;
	Actor actor;
	olc::Sprite* fields;

	int tile_width = 128;
	int tile_height = 128;
	int tiles_visible_x = int(winWidth) / tile_width;
	int tiles_visible_y = int(winHeight) / tile_height;

	float cameraPos_x = 0.0f;
	float cameraPos_y = 0.0f;
	float offset_x;
	float offset_y;

	Vec2 location = { 1, 1 };
	float speed = 2;

	Value_checker VC;
};
