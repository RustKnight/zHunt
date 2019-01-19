#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "zHunt.h"




int main()
{

	//ShowCursor(false);
	vector <string> paths;
	paths.push_back({ "sprites\\rifleman\\NEW\\aim\\r_aim.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\climb\\r_climb.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\idle\\r_idle.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\pick\\r_pick.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\run\\r_run.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\walk\\r_walk.txt" });

	zHunt game (paths);
	if (game.Construct(int (game.getWinWidth()), int (game.getWinHeight()), 1, 1))
		game.Start();

	return 0;
}