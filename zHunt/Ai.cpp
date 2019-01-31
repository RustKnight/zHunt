#include "Ai.h"

void Ai::think()
{
	for (Rifleman* rf : vAllies) {
		rf->setGoal(playerLocation);
		rf->moveTowardsGoal();		 
	}

}

void Ai::loadRiflemen(Rifleman* rf)
{
	vAllies.push_back(rf);
}

void Ai::update(Vec2 playerLoc)
{
	playerLocation = playerLoc;
}
