#include "CinematicEffect.h"



void CinematicEffect::update(float eTime) {

	eTime_ = eTime;

	if (active_) {
		top.grow();
		bottom.grow();
	}

	else {
		top.retract();
		bottom.retract();
	}
}



void CinematicEffect::framing(bool start) {
	active_ = start;
}

