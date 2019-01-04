#include "zHunt.h"


//Constructor

zHunt::zHunt() :
	winWidth { 800.0f},
	winHeight{ 600.0f },
	actor	{ placeInCenter(), this }
{
	sAppName = "RustKnight";
}



bool zHunt::OnUserCreate() 
{
	actor.load_spr_sheet("survivor_expanded.png");

	return true;
}


bool zHunt::OnUserUpdate(float fElapsedTime) 
{
	Clear(olc::BLACK);
	SetPixelMode(olc::Pixel::ALPHA);

	//DrawLine(400, 0, 400, 600, olc::RED);
	//DrawLine(0, 300, 800, 300, olc::RED);
	//DrawLine(100, 0, 700, 600, olc::RED);
	//DrawLine(100, 600, 700, 0, olc::RED);

	//std::string pos = std::to_string (actor.lookAtMouse());
	//DrawString(40, 40, pos, olc::YELLOW);

	actor.update(fElapsedTime);
	//actor.draw();

	return true;
}




Vec2 zHunt::placeInCenter() const
{
	return  Vec2{ winWidth / 2, winHeight / 2 };
}



float zHunt::getWinWidth() const
{
	return winWidth;
}

float zHunt::getWinHeight() const
{
	return winHeight;
}

