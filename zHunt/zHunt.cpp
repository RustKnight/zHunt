#include "zHunt.h"


//Constructor

zHunt::zHunt(vector<string>& paths) :
	winWidth { 768.0f},
	winHeight{ 640.0f },
	actor{ Vec2 {1.0f, 1.0f}, this, paths, 1 },
	clone{ Vec2{ 5.0f, 5.0f }, this, paths },
	camera {this, &map, getWinWidth(), getWinHeight()}
{
	sAppName = "RustKnight";
}



bool zHunt::OnUserCreate() 
{

	actor.load_spr_sheet("sprites\\rifleman\\NEW\\aim\\r_aim.png");
	actor.load_spr_sheet("sprites\\rifleman\\NEW\\climb\\r_climb.png");
	actor.load_spr_sheet("sprites\\rifleman\\NEW\\idle\\r_idle.png");
	actor.load_spr_sheet("sprites\\rifleman\\NEW\\pick\\r_pick.png");
	actor.load_spr_sheet("sprites\\rifleman\\NEW\\run\\r_run.png");
	actor.load_spr_sheet("sprites\\rifleman\\NEW\\walk\\r_walk.png");
											 
	//clone.load_spr_sheet("sprites\\rifleman\\NEW\\aim\\r_aim.png");
	//clone.load_spr_sheet("sprites\\rifleman\\NEW\\climb\\r_climb.png");
	//clone.load_spr_sheet("sprites\\rifleman\\NEW\\idle\\r_idle.png");
	//clone.load_spr_sheet("sprites\\rifleman\\NEW\\pick\\r_pick.png");
	//clone.load_spr_sheet("sprites\\rifleman\\NEW\\run\\r_run.png");
	//clone.load_spr_sheet("sprites\\rifleman\\NEW\\walk\\r_walk.png");


	camera.load_fields("sprites\\terrain\\SUEL001.png");

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
	
	//clone.update(fElapsedTime, camera.get_offset()); // why does this work opposed to giving a Vec2{0, 0} -> that keeps the clone stuck in upper left corner

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

