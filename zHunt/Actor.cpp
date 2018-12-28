#include "Actor.h"

void Actor::draw() const
{
	pge->DrawPartialSprite(location.x, location.y, spr, 231, 295, 31, 25, 1);
}

void Actor::load_spr_sheet(std::string adrs)
{
	spr = new olc::Sprite{ adrs };
}
