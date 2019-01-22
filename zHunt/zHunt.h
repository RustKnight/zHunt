#pragma once
#include "olcPixelGameEngine.h"
#include "RectF.h"
#include "Vec2.h"
#include "Value_checker.h"

#include "Actor.h"
#include "Zombie.h"
#include "Map.h"
#include "Camera.h"



class zHunt : public olc::PixelGameEngine
{
public:
	zHunt(vector <vector<string>>& paths);

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
	Zombie zombie;
	olc::Sprite* fields;
	Camera camera;
	bool toggle_camera = true;

	Value_checker VC;
};
