#include "zHunt.h"


//Constructor

zHunt::zHunt() :
	winWidth { 768.0f},
	winHeight{ 640.0f },
	actor{ Vec2 {1.0f, 1.0f}, this }

{
	sAppName = "RustKnight";
}



bool zHunt::OnUserCreate() 
{
	actor.load_spr_sheet("survivor_expanded.png");
	fields = new olc::Sprite ("SUEL001.png");


	return true;
}

// 25 w, 45h -> ~ 1 character size 

bool zHunt::OnUserUpdate(float fElapsedTime) 
{
	Clear(olc::VERY_DARK_GREEN);
	SetPixelMode(olc::Pixel::ALPHA);



	if (GetKey(olc::UP).bHeld)
		location.y -= fElapsedTime * speed;
	if (GetKey(olc::DOWN).bHeld)
		location.y += fElapsedTime * speed;
	if (GetKey(olc::LEFT).bHeld && (int)location.x > 0)
		location.x -= fElapsedTime * speed;
	if (GetKey(olc::RIGHT).bHeld)
		location.x += fElapsedTime * speed;

	//  karte += L"..o.............";
	//  karte += L".o...o..........";
	//  karte += L".....o..........";
	//  karte += L".....o..........";
	//  karte += L"................";
	//  karte += L"................";

	cameraPos_x = actor.get_location().x;
	cameraPos_y = actor.get_location().y;

	offset_x = cameraPos_x - float(tiles_visible_x / 2.0f);
	offset_y = cameraPos_y - float(tiles_visible_y / 2.0f);

	if (offset_x < 0) offset_x = 0;
	if (offset_y < 0) offset_y = 0;
	if (offset_x > map.get_width() - tiles_visible_x) offset_x = map.get_width() - tiles_visible_x;
	if (offset_y > map.get_height() - tiles_visible_y) offset_y = map.get_height() - tiles_visible_y;

	float fTileOffsetX = (offset_x - (int)offset_x) * tile_width;
	float fTileOffsetY = (offset_y - (int)offset_y) * tile_height;


	for (int x = -1; x < tiles_visible_x + 1; ++x)
		for (int y = -1; y < tiles_visible_y + 1; ++y) {

			wchar_t tileID = map.get_tile(x + offset_x, y + offset_y);
			
			switch (tileID) {
			case L'.':
				DrawSprite(x * tile_width - fTileOffsetX, y * tile_height - fTileOffsetY, fields, 1);
				break;
			case L'o':
				break;
			}
		}
		

	FillRect((location.x - offset_x) * tile_width, (location.y - offset_y)  * tile_height, 20, 40, olc::DARK_RED);
	Vec2 offset{ offset_x , offset_y };


	actor.renderer.update_offset(offset);
	actor.update(fElapsedTime);

	//if (VC.value_changed((int)cameraPos_x)) {
	//
	//	cout << "CamPos_X: " << cameraPos_x << endl;
	//	cout << "CamPos_Y: " << cameraPos_y;
	//	cout << endl;
	//	cout << endl;
	//}

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

