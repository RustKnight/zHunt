#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "zHunt.h"




int main()
{

	//ShowCursor(false);
	vector < vector<string>> actors_mapping;
	vector <string> paths;
	
	paths.push_back({ "sprites\\rifleman\\NEW\\aim\\aim_temp.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\climb\\r_climb.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\idle\\r_idle.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\pick\\r_pick.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\run\\r_run.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\walk\\r_walk.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\fire\\r_fire.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\reload\\r_reload.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\fire\\fire_slow.txt" });
	paths.push_back({ "sprites\\rifleman\\NEW\\fire\\fire_faster.txt" });

	actors_mapping.push_back(paths);
	paths.clear();

	paths.push_back({ "sprites\\zombie\\attack\\z_attack.txt" });
	paths.push_back({ "sprites\\zombie\\die\\z_die.txt" });
	paths.push_back({ "sprites\\zombie\\hit\\z_hit.txt" });
	paths.push_back({ "sprites\\zombie\\idle\\z_idle.txt" });
	paths.push_back({ "sprites\\zombie\\walk\\z_walk.txt" });

	actors_mapping.push_back(paths);
	paths.clear();

	

	zHunt game (actors_mapping);
	if (game.Construct(int (game.getWinWidth()), int (game.getWinHeight()), 1, 1))
		game.Start();

	return 0;
}