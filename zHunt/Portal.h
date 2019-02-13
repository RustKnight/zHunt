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

	
	
	void load_assets();
	void update(float eTime, const Vec2 & cam_off, bool start);
	
	void openPortal();
	void closePortal();
	
	void becomeSpawner(Vec2 spw_loc);
	Vec2 getPosition() const;



private:
	static constexpr int openTimeMax = 5;
	int timeOpened = 0;
	int opened = false;

	bool transitionDone;
	bool isSpawner = false;
	bool isTeleporter = true;

	phase color_idle = RED_IDLE;
	phase color_open = RED_OPEN;
};

