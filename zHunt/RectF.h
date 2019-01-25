#pragma once
#include "Vec2.h"


class RectF {
public:
	RectF() = default;
	RectF(float in_left, float in_right, float in_top, float in_bottom);
	RectF(Vec2 top_left, Vec2 top_right);
	RectF(Vec2 top_left, float width, float height);
	bool is_colliding(const RectF& other) const;
	static RectF fromCenter(Vec2 center, float halfWidth, float halfHeight);
	Vec2 getCenter() const;

	Vec2 location;
public:
	float left;
	float right;
	float top;
	float bottom;
};