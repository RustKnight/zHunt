#include "zHunt.h"


//Constructor

zHunt::zHunt() :
	winWidth { 768.0f},
	winHeight{ 640.0f },
	actor{ Vec2 {1.0f, 1.0f}, this },
	clone{ Vec2{ 7.0f, 10.0f }, this },
	camera {this, &map, getWinWidth(), getWinHeight()}
{
	sAppName = "RustKnight";
}



bool zHunt::OnUserCreate() 
{
	actor.load_spr_sheet("survivor_expanded.png");
	clone.load_spr_sheet("survivor_expanded.png");
	camera.load_fields("SUEL001.png");

	return true;
}

// 25 w, 45h -> ~ 1 character size 

bool zHunt::OnUserUpdate(float fElapsedTime) 
{
	Clear(olc::VERY_DARK_GREEN);
	SetPixelMode(olc::Pixel::ALPHA);
	

	camera.update(actor.get_location());
	camera.screen_in_view();

	actor.update(fElapsedTime, camera.get_offset());
	//actor.controlls();

	clone.update(fElapsedTime, camera.get_offset()); // why does this work opposed to giving a Vec2{0, 0} -> that keeps the clone stuck in upper left corner

	return true;
}

//std::string pos = std::to_string (actor.location.y);
//DrawString(40, 40, pos, olc::YELLOW);


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

