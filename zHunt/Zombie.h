#pragma once
#include "Actor.h"


class Zombie : public Actor {
	enum actions { ATTACK, DIE, HIT, IDLE, WALK };

public:
	Zombie(Vec2 loc, olc::PixelGameEngine* in_pge, vector<string>& paths) :
	Actor (loc, in_pge, paths)
	{}


	void randomize_location();
	void look_at_vec(Vec2 pos);
	void move_towards_vec(Vec2 goal);

public:
	void update(float fElapTm, const Vec2& cam_off) override ;

private:
	float speed = 0.4f;
};