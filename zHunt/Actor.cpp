#include "Actor.h"

void Actor::draw() const
{
	pge->FillCircle((int)location.x, (int)location.y, 2, olc::RED);
}
