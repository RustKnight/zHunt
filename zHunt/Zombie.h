#pragma once
#include "Actor.h"


class Zombie : public Actor {
	enum actions { ATTACK, DIE, HIT, IDLE, WALK };

public:

	Zombie(Vec2 loc, olc::PixelGameEngine* in_pge, vector<string>& paths) 
		:
	Actor (loc, in_pge, paths)
	{}

	Zombie(Vec2 loc, olc::PixelGameEngine* in_pge, vector<string>& paths, bool is_player)
		:
		Actor(loc, in_pge, paths, is_player)
	{}



public:
	void update(float fElapTm, const Vec2& cam_off) override ;

};