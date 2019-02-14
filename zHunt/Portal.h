#pragma once
#include "Actor.h"


// Portal should have 2 modes : spawn points for N S E W and the blinking behaviour
// color should be changed to show behaviour


class Portal : public Actor {

	enum phase { BROWN_IDLE, RED_IDLE, BROWN_OPEN, RED_OPEN };

public:
	Portal(Vec2 loc, olc::PixelGameEngine* in_pge, vector <Portal*>* vpP) :
		Actor{ loc, in_pge }, vpPrt {vpP}
	{
		alive = true;
		isActive = false;
	}

	void becomeSpawner(Vec2 spw_loc);
	void tryTeleport(Actor& act);

	void setIndex(int i);
	void load_assets(vector <olc::Sprite*>* vpPrt);
	void update(float eTime, const Vec2 & cam_off, bool start);
	bool getStatus() const;
	Vec2 getPosition() const;
	

	bool isSpawner = false;


private:
	void openPortal();
	bool closePortal();
	void teleAway();
	void teleport(Actor& act);

	
private:
	static constexpr int openTimeMax = 4;
	static constexpr int teleCooldown = 3;
	float timeOpened = 0;
	int opened = false;
	int index = 0;

	bool transitionDone;	

	phase color_idle = RED_IDLE;
	phase color_open = RED_OPEN;

	vector<Portal*>* vpPrt;
};

