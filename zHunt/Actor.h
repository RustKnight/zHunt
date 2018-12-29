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
	void draw_centered(float x, float y, olc::Sprite* spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale) const;


private:
	Vec2 location;
	Vec2 velocity;
	float speed;

	olc::Sprite* spr = nullptr;
	olc::PixelGameEngine* pge;
};