#include "zHunt.h"


//Constructor

zHunt::zHunt() :
	winWidth { 768.0f},
	winHeight{ 640.0f },
	actor	{ placeInCenter(), this }
{
	sAppName = "RustKnight";
}



bool zHunt::OnUserCreate() 
{
	actor.load_spr_sheet("survivor_expanded.png");
	fields = new olc::Sprite{ "SUEL001.png" };
	
	karte += L"..o.............";
	karte += L"..o..o..........";
	karte += L".....o..........";
	karte += L".....o..........";
	karte += L"................";
	karte += L"................";
	karte += L"................";
	karte += L"................";
	karte += L"................";
	karte += L"................";

	return true;
}

// 25 w, 45h -> ~ 1 character size 

bool zHunt::OnUserUpdate(float fElapsedTime) 
{
	Clear(olc::VERY_DARK_GREEN);
	SetPixelMode(olc::Pixel::ALPHA);

	auto GetTile = [&](int x, int y)
	{
		if (x >= 0 && x < map_width && y >= 0 && y < map_height)
			return karte[y * map_width + x];
		else
			return L' ';
	};

	auto SetTile = [&](int x, int y, wchar_t c)
	{
		if (x >= 0 && x < map_width && y >= 0 && y < map_height)
			karte[y * map_width + x] = c;
	};


	if (GetKey(olc::UP).bHeld)
		location.y -= fElapsedTime * speed;
	if (GetKey(olc::DOWN).bHeld)
		location.y += fElapsedTime * speed;
	if (GetKey(olc::LEFT).bHeld)
		location.x -= fElapsedTime * speed;
	if (GetKey(olc::RIGHT).bHeld)
		location.x += fElapsedTime * speed;


	cameraPos_x = location.x ;
	cameraPos_y = location.y ;

	offset_x = cameraPos_x - float(tiles_visible_x / 2.0f) * tile_width;
	offset_y = cameraPos_y - float(tiles_visible_y / 2.0f) * tile_height;

	if (offset_x < 0) offset_x = 0;
	if (offset_y < 0) offset_y = 0;
	if (offset_x > map_width - tiles_visible_x) offset_x = map_width - tiles_visible_x;
	if (offset_y > map_height - tiles_visible_y) offset_y = map_height - tiles_visible_y;

	float fTileOffsetX = (offset_x - (int)offset_x) * tile_width;
	float fTileOffsetY = (offset_y - (int)offset_y) * tile_height;


	for (int x = 0; x < tiles_visible_x; ++x)
		for (int y = 0; y < tiles_visible_y; ++y) {

			wchar_t tileID = GetTile(x + offset_x, y + offset_y);
			
			switch (tileID) {
			case L'.':
				DrawSprite(x * tile_width - fTileOffsetX, y * tile_height - fTileOffsetY, fields, 1);
				break;
			case L'o':
				break;
			}
		}
		

	FillRect((location.x - offset_x) * tile_width, (location.y - offset_y)  * tile_height, 20, 40, olc::DARK_RED);
	

	actor.update(fElapsedTime);


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

