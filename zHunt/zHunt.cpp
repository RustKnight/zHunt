#include "zHunt.h"


// box hit detection
// bullet pixel-level-hit detection
// hit splatter animation
// pushback on hit ?
// zombie attack when near
// creatures HP
// fire animation
// cursor hide, cursor-while-moving, cursor-while-aiming
// proper ALL creature draw order

zHunt::zHunt(vector <vector<string>>& paths) :
	winWidth { 768.0f},
	winHeight{ 640.0f },
	rifleman{ Vec2 {1.0f, 1.0f}, this, paths[0] },
	zombie{ Vec2{ 5.0f, 5.0f }, this, paths[1] },
	camera {this, &map, getWinWidth(), getWinHeight()}
{
	sAppName = "RustKnight";
}



bool zHunt::OnUserCreate() 
{

	rifleman.load_spr_sheet("sprites\\rifleman\\NEW\\aim\\r_aim.png");
	rifleman.load_spr_sheet("sprites\\rifleman\\NEW\\climb\\r_climb.png");
	rifleman.load_spr_sheet("sprites\\rifleman\\NEW\\idle\\r_idle.png");
	rifleman.load_spr_sheet("sprites\\rifleman\\NEW\\pick\\r_pick.png");
	rifleman.load_spr_sheet("sprites\\rifleman\\NEW\\run\\r_run.png");
	rifleman.load_spr_sheet("sprites\\rifleman\\NEW\\walk\\r_walk.png");
	rifleman.load_spr_sheet("sprites\\rifleman\\NEW\\fire\\r_fire.png");
	rifleman.load_spr_sheet("sprites\\rifleman\\NEW\\reload\\r_reload.png");
											 
	zombie.load_spr_sheet("sprites\\zombie\\attack\\z_attack.png");
	zombie.load_spr_sheet("sprites\\zombie\\die\\z_die.png");
	zombie.load_spr_sheet("sprites\\zombie\\hit\\z_hit.png");
	zombie.load_spr_sheet("sprites\\zombie\\idle\\z_idle.png");
	zombie.load_spr_sheet("sprites\\zombie\\walk\\z_walk.png");

	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::uniform_real_distribution <float> distR(0.1f, 0.6f);


	for (int i = 0; i < 20; i++) {
		vZombies.push_back(zombie);
		vZombies[i].randomize_stats(distR(e) );
	}

	camera.load_fields("sprites\\terrain\\green.png");
	rifleman.become_player(1);
	

	vActors.push_back(&rifleman);
	for (Zombie& z : vZombies)
		vActors.push_back(&z);

	return true;
}

// 25 w, 45h -> ~ 1 character size 

bool zHunt::OnUserUpdate(float fElapsedTime) 
{
	Clear(olc::VERY_DARK_GREEN);
	SetPixelMode(olc::Pixel::ALPHA);
	
	(toggle_camera) ? camera.update(rifleman.get_location()) : camera.update(zombie.get_location());
	camera.screen_in_view();

	if (GetKey(olc::Q).bPressed)
		toggle_camera = !toggle_camera;
	if (GetKey(olc::G).bPressed)
		toggle_hunger = !toggle_hunger;


	// this code assures that we draw by height so we avoid unclear rendering
	struct by_height {
		bool operator()(Actor* const a, Actor* const b) const noexcept {
			return a->get_location().y < b->get_location().y;
		}
	};
	std::sort(vActors.begin(), vActors.end(), by_height());

	

	if (rifleman.update(fElapsedTime, camera.get_offset()))
		vBullets.push_back( Projectile{ rifleman.get_location(), rifleman.get_fire_angle() });


	for (Projectile& p : vBullets) {
		p.location = p.location + (p.direction * p.speed * fElapsedTime);
		FillCircle((p.location.x - camera.get_offset().x) * 128, (p.location.y - camera.get_offset().y) * 128, 1, olc::BLACK);
	}
	


	for (Zombie& z : vZombies) {
		z.update(fElapsedTime, camera.get_offset());
		if (toggle_hunger) z.move_towards_vec (rifleman.get_location());
	}

	for (Actor* a : vActors)
		a->draw();

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

