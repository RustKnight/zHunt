#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "zHunt.h"




int main()
{

	//ShowCursor(false);


	zHunt game;
	if (game.Construct(int (game.getWinWidth()), int (game.getWinHeight()), 1, 1))
		game.Start();

	return 0;
}