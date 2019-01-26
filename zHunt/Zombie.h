#pragma once
#include "Actor.h"
#include "Projectile.h"

// move speed should modulate animation speed


class Zombie : public Actor {
	enum actions { ATTACK, DIE, HIT, IDLE, WALK };

public:
	Zombie(Vec2 loc, olc::PixelGameEngine* in_pge, vector<string>& paths) :
		Actor{ loc, in_pge, paths }
	{
		hp = 10;
		alive = true;
	}


	void randomize_stats(float speed_in);
	void look_at_vec(Vec2 pos);
	void move_towards_vec(Vec2 goal);
	bool check_collision(Projectile & bullet);
	void stay();

public:
	bool update(float fElapTm, const Vec2& cam_off) override ;

private:
	float speed;	
	int random_death_anim;
};