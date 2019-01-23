#pragma once
#include "Actor.h"


class Rifleman : public Actor {

public:
	Rifleman (Vec2 loc, olc::PixelGameEngine* in_pge, vector<string>& paths) :
		Actor (loc, in_pge, paths)
	{}


	void update(float fElapTm, const Vec2& cam_off) override;
};