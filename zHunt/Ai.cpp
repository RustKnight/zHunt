#include "Ai.h"

void Ai::think()
{
	for (Rifleman* rf : vAllies)
		1;
}

void Ai::loadRiflemen(Rifleman* rf)
{
	vAllies.push_back(rf);
}

void Ai::update(float playerLoc)
{
	playerLocation = playerLoc;
}
