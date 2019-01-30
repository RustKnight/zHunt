#pragma once
#include "olcPixelGameEngine.h"
#include <Vector>
#include "AnimationHandler.h"
#include "Actor.h"


struct EffectOnActorPointer {

	EffectOnActorPointer(Actor* ac) :
		actor{ ac }, frame{ 0 }
	{}

	Actor* actor;
	float frame;
};




class Effect {
public:

	void render_effect (olc::PixelGameEngine* pge, float eTime, Vec2 cam_offset) {

		for (int i = 0; i < vEff_struct.size(); ++i) {

			spr_sqn eff;
			int x = (vEff_struct[i].actor->get_location().x - cam_offset.x) * 128;
			int y = (vEff_struct[i].actor->get_location().y - cam_offset.y) * 128;

			// request anim nr. x with facing y -  with frame X
			eff = effect_handler.get_coords(0, 1, int(vEff_struct[i].frame));
			// increase frame step	
			vEff_struct[i].frame += eTime * 12.5f;
			// if frame reached end, animation done get rid of actor, set new animation hit position
			if ((int)vEff_struct[i].frame >= effect_handler.get_sqn_size(0, 0)) {
				vEff_struct[i].actor->shot = false;
				vEff_struct.erase(vEff_struct.begin() + i);

				hit_offset_x = rand() % 12;
				hit_offset_y = 14 + (rand() % 18);
			}
			else {
				// randomize hit location

			//	pge->DrawPartialSprite(x - hit_offset_x, y - hit_offset_y, splat_effects, eff.x, eff.y, eff.w, eff.h, 1);

				//cout << "x: " << x - hit_offset_x << endl;
				//cout << "y: " << y - hit_offset_y << endl;
			}
		}
	}


public:
	olc::Sprite* splat_effects;
	std::vector<EffectOnActorPointer> vEff_struct;
	AnimationHandler effect_handler;
	bool bullet_hit = false;
	int hit_offset_x;
	int hit_offset_y;
};