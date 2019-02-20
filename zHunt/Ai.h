#pragma once

#include "Actor.h"
#include "Rifleman.h"
#include "Vec2.h"
#include <vector>

class Ai {

public:
	Ai() = default;

	void think();
	void loadRiflemen(Rifleman* rf);
	void update(Vec2 playerLoc);
	void toggleAggro();
	void goToMoveOrder();
	void moveTo(Vec2 loc);
	bool noMoveOrders() const;

private:
	std::vector <Rifleman*> vAllies;
	Vec2 playerLocation;
	Vec2 moveOrder;
	bool aggresive = false;
	bool noMoveToOrder = true;

};