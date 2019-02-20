#include "Camera.h"



void Camera::update(Vec2 actor_loc)
{

	cameraPos_x = actor_loc.x;
	cameraPos_y = actor_loc.y;

	offset_x = cameraPos_x - float(tiles_visible_x / 2.0f);
	offset_y = cameraPos_y - float(tiles_visible_y / 2.0f);

	if (offset_x < 0) offset_x = 0;
	if (offset_y < 0) offset_y = 0;
	if (offset_x > map->get_width() - tiles_visible_x) offset_x = map->get_width() - tiles_visible_x;
	if (offset_y > map->get_height() - tiles_visible_y) offset_y = map->get_height() - tiles_visible_y;

	fTileOffsetX = (offset_x - (int)offset_x) * tile_width;
	fTileOffsetY = (offset_y - (int)offset_y) * tile_height;

}


void Camera::screen_in_view()
{

	for (int x = -1; x < tiles_visible_x + 1; ++x)
		for (int y = -1; y < tiles_visible_y + 1; ++y) {

			wchar_t tileID = map->get_tile(x + offset_x, y + offset_y);

			switch (tileID) {
			case L'.':
				pge->DrawSprite(x * tile_width - fTileOffsetX, y * tile_height - fTileOffsetY, fields, 1);
				break;
			case L'o':
				break;
			}
		}

}

Vec2 Camera::get_offset()
{
	return Vec2{ offset_x, offset_y };
}




void Camera::load_fields(std::string adrs)
{
//	fields = new olc::Sprite{ adrs };
}