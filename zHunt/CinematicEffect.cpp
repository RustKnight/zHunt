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

	active_ = false;
}



void CinematicEffect::framing(bool start) {
	active_ = start;
}

bool CinematicEffect::closeView()
{
	active_ = true;
	focusSize_ = scrHeight_ * sidesClose;
	speed_ = 70.0f;

	if (top.getProgress() > focusSize_ - 1.0f)
		return true;

	return false;
}

void CinematicEffect::Side::grow()
{

	if (progress_ < pCE_->focusSize_)
		progress_ += pCE_->eTime_ * pCE_->speed_;

	if (growDown_)
		pCE_->pge_->FillRect(0, 0, pCE_->scrWidth_, progress_, olc::BLACK);

	else
		pCE_->pge_->FillRect(0, pCE_->scrHeight_ - progress_, pCE_->scrWidth_, pCE_->scrHeight_, olc::BLACK);
}

void CinematicEffect::Side::retract()
{


	if (progress_ > 0)
		progress_ -= pCE_->eTime_ * pCE_->speed_;

	if (growDown_)
		pCE_->pge_->FillRect(0, 0, pCE_->scrWidth_, progress_, olc::BLACK);


	else
		pCE_->pge_->FillRect(0, pCE_->scrHeight_ - progress_, pCE_->scrWidth_, pCE_->scrHeight_, olc::BLACK);

}

float CinematicEffect::Side::getProgress() const
{
	return progress_;
}
