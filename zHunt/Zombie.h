#pragma once
#include "Actor.h"
#include "Projectile.h"
#include "Portal.h"

// move speed should modulate animation speed

class Rifleman;

class Zombie : public Actor {
	enum actions { ATTACK, DIE, HIT, IDLE, WALK };

public:
	Zombie(Vec2 loc, olc::PixelGameEngine* in_pge, vector<Rifleman*>* vpR, vector<Portal*>* vpP) :
		Actor{ loc, in_pge }, vpRfl {vpR}, vpPrt {vpP}
	{
		hp = 10;
		alive = true;
	}

public:
	void randomize_stats(float speed_in);
	void randomizeStartLocation();
	void stay();
	bool update(float fElapTm, const Vec2& cam_off) override;
	void is_hit();
	bool in_range(Vec2 location);
	void attack_target(Actor& target);
	bool attack_cooldown_over();
	void moveTowardsGoal();

	void load_assets(vector <olc::Sprite*>* vpZomSpr);
private:
	vector<Portal*>* vpPrt;
	float speed;	
	int random_death_anim;
	float att_cooldown = 100.0f;
	vector<Rifleman*>* vpRfl;
};