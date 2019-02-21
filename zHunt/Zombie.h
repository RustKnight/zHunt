#pragma once
#include "Actor.h"
#include "Projectile.h"
#include "Portal.h"



class Rifleman;

class Zombie : public Actor {
	enum actions { ATTACK, DIE, HIT, IDLE, WALK };

public:
	Zombie(Vec2 loc, olc::PixelGameEngine* in_pge, vector<Portal*>* vpP) :
		Actor{ loc, in_pge }, vpPrt {vpP}
	{
		hp = 10;
		alive = true;
		finishedDieing = false;
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
	void loadZfeed(int* x);
	int closestFlesh(vector<Vec2>* locs, bool rfA, bool rfB);
	float calculatePath(const Vec2& PathRifle, bool& teleporting, int& InIndexPortal, int& OutIndexPortal) const;
	float closestToActor(const Vec2& Actor, int& portalIndex) const;
	void changeSpeed(float speed_in);

	
	void load_assets(vector <olc::Sprite*>* vpZomSpr);
private:
	float speed;	
	int random_death_anim;
	float att_cooldown = 100.0f;
	vector<Portal*>* vpPrt;
	int* ZomFeedOnDead;
	
};