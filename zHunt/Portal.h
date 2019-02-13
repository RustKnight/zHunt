#pragma once
#include "Actor.h"


// Portal should have 2 modes : spawn points for N S E W and the blinking behaviour
// color should be changed to show behaviour


class Portal : public Actor {

	enum phase { BROWN_IDLE, RED_IDLE, BROWN_OPEN, RED_OPEN };

public:
	Portal(Vec2 loc, olc::PixelGameEngine* in_pge) :
		Actor{ loc, in_pge }
	{
		alive = true;
		isActive = false;
	}

	
	void load_assets(vector <olc::Sprite*>* vpPrt);
	void becomeSpawner(Vec2 spw_loc);
	void update(float eTime, const Vec2 & cam_off, bool start);
	bool getStatus() const;
	Vec2 getPosition() const;

	bool isSpawner = false;


private:
	void openPortal();
	bool closePortal();
	void teleAway();

	
private:
	static constexpr int openTimeMax = 4;
	float timeOpened = 0;
	int opened = false;

	bool transitionDone;	

	phase color_idle = RED_IDLE;
	phase color_open = RED_OPEN;
};

