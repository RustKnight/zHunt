#include "Weapon.h"
#include <iostream>

bool Weapon::fire()
{
	if (clipEmpty() || fireCoolDown()) 
		return false;
	
	fireCD = fireRate;
	clipNow -= 1;
	return true;
}

int Weapon::checkRounds() const
{
	return clipNow;
}

void Weapon::doReload()
{
	reloading = true;
}


void Weapon::update(float in_eTime)
{
	if (fireCD > 0)
		fireCD -= in_eTime * 1;

	std::cout << fireCD << std::endl;

	if (reloading)
		if (reload < reloadTime)
			reload += in_eTime * 1;
		else {
			clipNow = clipMax;
			reloading = false;
			reload = 0;
		}
}

bool Weapon::getReloadState() const
{
	return reloading;
}



bool Weapon::clipEmpty()
{
	if (clipNow <= 0)
		return true;

	return false;
}

bool Weapon::fireCoolDown()
{
	if (fireCD <= 0)
		return false;

	return true;
}

bool Carabine::bolting()
{
	return getReloadState();
}
