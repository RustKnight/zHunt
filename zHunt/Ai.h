#pragma once

#include "Actor.h"
#include "Rifleman.h"
#include <vector>

class Ai {

	Ai() = default;

	void think();
	void loadRiflemen(Rifleman* rf);
	void update(float playerLoc);

private:
	std::vector <Rifleman*> vAllies;
	float playerLocation = 0;
};