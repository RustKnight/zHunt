#pragma once
#include "Actor.h"


class Portal : public Actor {

public:

	Portal(Vec2 loc, olc::PixelGameEngine* in_pge) :
		Actor{ loc, in_pge }
	{
		alive = true;
	}

	enum phase {OPEN_BROWN, OPEN_RED, OPEN_BLUE, OPEN_DARK_RED, IDLE_BROWN, IDLE_RED, IDLE_BLUE, IDLE_DARK_RED};
	
	void load_assets();
	void spawn();
	void update(float eTime, const Vec2 & cam_off, bool start);


private:
	static constexpr int openTimeMax = 5;
	int timeOpened = 0;
	bool active = false;
};