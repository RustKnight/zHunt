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

public:
	void draw() const;
	void load_spr_sheet(std::string adrs);


private:
	Vec2 location;
	olc::Sprite* spr = nullptr;
	olc::PixelGameEngine* pge;
};