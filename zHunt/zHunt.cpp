#include "zHunt.h"


//Constructor

zHunt::zHunt(vector <vector<string>>& paths) :
	winWidth { 768.0f},
	winHeight{ 640.0f },
	actor{ Vec2 {1.0f, 1.0f}, this, paths[0], 1 },
	zombie{ Vec2{ 5.0f, 5.0f }, this, paths[1] },
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
											 
	zombie.load_spr_sheet("sprites\\zombie\\attack\\z_attack.png");
	zombie.load_spr_sheet("sprites\\zombie\\die\\z_die.png");
	zombie.load_spr_sheet("sprites\\zombie\\hit\\z_hit.png");
	zombie.load_spr_sheet("sprites\\zombie\\idle\\z_idle.png");
	zombie.load_spr_sheet("sprites\\zombie\\walk\\z_walk.png");


	camera.load_fields("sprites\\terrain\\green2.png");

	return true;
}

// 25 w, 45h -> ~ 1 character size 

bool zHunt::OnUserUpdate(float fElapsedTime) 
{
	Clear(olc::VERY_DARK_GREEN);
	SetPixelMode(olc::Pixel::ALPHA);
	
	(toggle_camera) ? camera.update(actor.get_location()) : camera.update(zombie.get_location());

	if (GetKey(olc::Q).bPressed)
		toggle_camera = !toggle_camera;

	camera.screen_in_view();

	actor.update(fElapsedTime, camera.get_offset());
	zombie.update(fElapsedTime, camera.get_offset()); // why does this work opposed to giving a Vec2{0, 0} -> that keeps the zombie stuck in upper left corner

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

