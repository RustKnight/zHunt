#pragma once
#include "RectF.h"
#include "Vec2.h"
#include "olcPixelGameEngine.h"






class Actor {

	//tools

	enum actions {	WALK, RUN, RELOAD, AIM, RECOIL, DIE, HURT, DIE2, GRAVE,
					CLIMB, PICK_UP, TIED, SIT, TIED_DIE, CARRIED, IDLE, SMOKE, ACTIONS_SIZE};
	enum facings {N, NE, E, SE, S, SW, W, NW, FACINGS_SIZE};

	struct spr_sqn {

		spr_sqn() :
		x{ 32167 }, y{ 0 }, w{ 0 }, h{ 0 }
		{}

		spr_sqn(int16_t x_in, int16_t y_in, int16_t w_in, int16_t h_in) :
			x{ x_in }, y{ y_in }, w{ w_in }, h{ h_in }
		{}

		int16_t x;
		int16_t y;
		int16_t w;
		int16_t h;
	};



public:
	Actor() = default;
	Actor (Vec2 loc, olc::PixelGameEngine* in_pge):
		location {loc},
		pge {in_pge},
		speed {80.0f},
		action{ WALK },
		facing{N}
	{
		load_mapping_info();
	}


public:
	void draw();
	void load_spr_sheet(std::string adrs);
	void draw_centered(float x, float y, olc::Sprite* spr, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale) const;
	
	//temp
	void update (float fElapTm);

private:
	void load_mapping_info();
	void draw_curr_anim(facings facing, actions act);
	int array_size(facings facing, actions act) const;	// build a function that checks values from start to end |||for (x : arr)||| and when it 
														// meets x = 32167 it stops counting and returns the size

	// Private Data Members
private:
	Vec2 location;
	Vec2 old_location;
	Vec2 velocity;
	float speed;

	olc::Sprite* spr = nullptr;
	olc::PixelGameEngine* pge;

	static constexpr int sqn_size = 8; // this is the greatest number of sequences of any given animation
	spr_sqn a3d_mapping_data[ACTIONS_SIZE][FACINGS_SIZE][sqn_size];
	actions action;
	facings facing;
	float play_seq = 0;
	float anim_speed = 6;  // might need an animation speed according to the size of the anim_seq
	float eTime = 0;
};


