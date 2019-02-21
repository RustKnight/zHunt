#pragma once
#include "olcPixelGameEngine.h"


class CinematicEffect {

	class Side {
	public:
		Side(CinematicEffect* pCE, float startPosition, bool growDown) :
			pCE_{ pCE }, heightPosition_{ startPosition }, growDown_{ growDown }, progress_{ 0.0f }
		{}

		void grow();
		void retract();
		float getProgress() const;

	private:
		float progress_;
		float heightPosition_;
		bool growDown_;
		CinematicEffect* pCE_;
	};



public:																					
	CinematicEffect(int winWidth, int winHeight, float speed, olc::PixelGameEngine* pge) :	//0.07f
		scrWidth_{ winWidth }, scrHeight_{ winHeight }, focusSize_{ int(winHeight * 0.10f) }, speed_{ speed }, pge_{ pge },
		top{ this, 0.0f, true }, 
		bottom{ this, float(scrHeight_), false }
	{}

	void update(float eTime);
	void framing(bool active);
	bool closeView();

private:

	static constexpr float sidesLengthCinematic = 0.07f;
	static constexpr float sidesClose = 0.50f;

	float eTime_;
	float speed_;
	int scrWidth_;
	int scrHeight_;
	int focusSize_;
	bool active_;

	Side top;
	Side bottom;

	olc::PixelGameEngine* pge_;
};
