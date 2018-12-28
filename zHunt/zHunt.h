#pragma once
#include "olcPixelGameEngine.h"
#include "RectF.h"
#include "Vec2.h"
#include "Actor.h"




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
	Actor actor;
};
