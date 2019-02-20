#include "Ai.h"


//mergi in spatele meu la o distanta mica, iar daca ma opresc vino in dreapta mea si uita-te la ce ma uit eu
//daca eu tintesc, tinesti la acelasi lucru, si daca incep sa trag, tragi si tu (ask to go in fire mode)
//
//cand iti spun sa stai, stai pe pozitie si tragi in cel mai apropiat zumba care intra in raza ta de actiune

/// maybe make AI rotate smoothly and also make him slightly aim before firing

void Ai::think()
{
	for (Rifleman* rf : vAllies) {
	
		// follow (x), stand ground, hunt, scavange (med/ammo)
		// for example indepedent squads can be made, by following a rifleman set in hunting mode

		// if (follow me)
		//		follow
		// else
		//		guard position
		if (noMoveToOrder) {
			if (rf->alive) {

				if (rf->withinDistance(playerLocation, 4000))
					rf->standGround(aggresive);
				else {
					rf->setGoal(playerLocation);
					rf->follow();
				}
			}
		}

		else 
			goToMoveOrder();

			

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

void Ai::toggleAggro()
{
	aggresive = !aggresive;
}

void Ai::goToMoveOrder()
{
	for (Rifleman* rf : vAllies) 
		if (rf->withinDistance(moveOrder, 300))
			noMoveToOrder = true;

		else {
			rf->setGoal(moveOrder);
			rf->follow();
		}

}

void Ai::moveTo(Vec2 loc)
{
	noMoveToOrder = false;
	moveOrder = loc;
}

bool Ai::noMoveOrders() const
{
	return noMoveToOrder;
}



//
//
//
//
//