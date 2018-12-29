#include "Actor.h"

void Actor::draw() const
{
	draw_centered (location.x, location.y, spr, 231, 295, 31, 25, 2);
}

void Actor::load_spr_sheet(std::string adrs)
{
	spr = new olc::Sprite{ adrs };
}

void Actor::draw_centered(float x, float y, olc::Sprite * spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale) const
{
	float center_x = x - (w*scale) / 2.0f;
	float center_y = y - (h*scale) / 2.0f;

	pge->DrawPartialSprite(int32_t (center_x), int32_t (center_y), spr, ox, oy, w, h, scale);
	
	//pge->FillCircle(400, 300, 2, olc::RED);
	//pge->DrawRect(center_x, center_y, (w*scale), (h*scale));
}
