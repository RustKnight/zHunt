#include "Controller.h"

void Controller::control(Rifleman& rifle)
{

	if (rifle.alive && rifle.isActive) {


		if (pge->GetKey(olc::W).bHeld)
			rifle.moveUp();

		if (pge->GetKey(olc::S).bHeld)
			rifle.moveDown();

		if (pge->GetKey(olc::D).bHeld)
			rifle.moveRight();

		if (pge->GetKey(olc::A).bHeld)
			rifle.moveLeft();



		if (pge->GetKey(olc::SHIFT).bHeld)
			rifle.running();

		if (pge->GetKey(olc::R).bPressed)
			rifle.reload();

		if (pge->GetKey(olc::Y).bPressed)
			rifle.smoke();


		if (pge->GetMouse(1).bHeld) {
			rifle.aim();

			Vec2 fireAngle{ (float)pge->GetMouseX(), (float)pge->GetMouseY() };

			rifle.fire(pge->GetMouse(0).bPressed, fireAngle);
		}

	}

}


