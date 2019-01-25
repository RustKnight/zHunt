#pragma once
#include "Actor.h"


class Rifleman : public Actor {

	enum actions { AIM, CLIMB, IDLE, PICK, RUN, WALK, FIRE, RELOAD, FIRE_SLOW, FIRE_FAST };

public:
	Rifleman (Vec2 loc, olc::PixelGameEngine* in_pge, vector<string>& paths) :
		Actor (loc, in_pge, paths)
	{
		hp = 10;
		alive = true;
	}

	bool update(float fElapTm, const Vec2& cam_off) override;
	Vec2 get_fire_angle() const;

private:
	//static constexpr int max_chamber = 5;
};