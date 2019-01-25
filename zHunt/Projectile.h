#pragma once
#include "Vec2.h"


struct Projectile {
	Projectile (Vec2 location_in, Vec2 direction_in) :
		location {location_in}, direction { direction_in }
	{}


	Vec2 location;
	Vec2 direction;
	float speed = 7.13f;
};