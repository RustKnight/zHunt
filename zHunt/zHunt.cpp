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
	Clear(olc::VERY_DARK_CYAN);
	SetPixelMode(olc::Pixel::ALPHA);

	actor.update(fElapsedTime);
	actor.draw();

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

