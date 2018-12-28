#include "RectF.h"

RectF::RectF(float in_left, float in_right, float in_top, float in_bottom) :
	left{in_left},
	right{in_right},
	top {in_top},
	bottom {in_bottom}
{}
	


RectF::RectF(Vec2 top_left, Vec2 in_bottom) :
	RectF(top_left.x, in_bottom.x, top_left.y, in_bottom.y)
{}



RectF::RectF(Vec2 top_left, float width, float height) :
	RectF(top_left, top_left + Vec2 {width, height})
{}



bool RectF::is_colliding(const RectF& other) const
{
	bool collision = false;

	if (right > other.left && left < other.right &&
		bottom > other.top && top < other.bottom){
		
		collision = true;
		}

	return collision;
}

RectF RectF::fromCenter(Vec2 center, float halfWidth, float halfHeight)
{
	Vec2 half{ halfWidth , halfHeight };
	return RectF{ center - half, center + half }; // super cool thinking!
}		// Center is a Vec2 and half is also a Vec2 = Vec2 Operations

Vec2 RectF::getCenter() const
{
	return Vec2{ (left + right) / 2.0f, (top + bottom) / 2.0f };
	
}
