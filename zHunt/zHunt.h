#pragma once
#include "olcPixelGameEngine.h"
#include "RectF.h"
#include "Vec2.h"
#include "Value_checker.h"

#include "Actor.h"
#include "Map.h"
#include "Camera.h"



class zHunt : public olc::PixelGameEngine
{
public:
	zHunt(vector<string>& paths);

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
	Actor clone;
	olc::Sprite* fields;
	Camera camera;
	

	Value_checker VC;
};
