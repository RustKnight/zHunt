#pragma once
#include "olcPixelGameEngine.h"
#include "Rifleman.h"
#include "Zombie.h"

class Controller {
public:

	Controller() = default;
	Controller(olc::PixelGameEngine* in_pge) :
		pge{ in_pge }
	{}


	void control(Rifleman& actor);


private:
	olc::PixelGameEngine* pge;
};