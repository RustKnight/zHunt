#pragma once
#include "Actor.h"

class Rifleman : public Actor {

	enum actions { AIM, CLIMB, IDLE, PICK, RUN, WALK, FIRE, RELOAD, HURT, DIE };

public:
	Rifleman (Vec2 loc, olc::PixelGameEngine* in_pge) :
		Actor (loc, in_pge)
	{
		hp = 25;
		alive = true;
	}

	bool update(float fElapTm, const Vec2& cam_off) override;
	Vec2 get_fire_angle() const;
	void load_assets();


private:
	//static constexpr int max_chamber = 5;
};