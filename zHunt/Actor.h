#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "olcPixelGameEngine.h"


class Actor {
	
public:
	Actor() = default;
	Actor (Vec2 loc, olc::PixelGameEngine* in_pge):
		location {loc},
		pge {in_pge}
	{}

	void draw() const;


private:
	Vec2 location;
	olc::PixelGameEngine* pge;
};