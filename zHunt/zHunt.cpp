#include "zHunt.h"


//DONE Proper draw order of sprites
//DONE box hit detection
//DONE bullet pixel-level-hit detection
//DONE hit splatter animation ///!!! maybe darker blood color and less animation sequences ; also, alternate splat animations
//DONE creatures HP/Death/stay static
//DONE fire animation
// pushback on hit// animation of zombie being hit
// zombie attack when near // pass for zombies to follow location and rectangle struct for them to check if near
// cursor hide, cursor-while-moving, cursor-while-aiming
// new terrain might be added via GRID edit in asprite, facilitates 8 direction grid creation
// stamina + deplete when running OR
// when pushing back
// minimap ?

zHunt::zHunt(vector <vector<string>>& paths) :
	winWidth { 768.0f},
	winHeight{ 640.0f },
	rifleman{ Vec2 {7.0f, 5.0f}, this, paths[0] },
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
	effect.splat_effects = new olc::Sprite("sprites\\effects\\splat.png");


	effect.effect_handler.load_mapping_info_string("sprites\\effects\\splat.txt");

	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::uniform_real_distribution <float> distR(0.1f, 0.4f);


	for (int i = 0; i < 25; i++) {
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
	

	if (rifleman.update(fElapsedTime, camera.get_offset()))
		vBullets.push_back( Projectile{ rifleman.get_location(), rifleman.get_fire_angle() });


	for (Zombie& z : vZombies) {
		z.update(fElapsedTime, camera.get_offset());
		z.move_towards_vec (rifleman.get_location());
		if (toggle_hunger) z.stay();

		for (Projectile& p : vBullets)
			if (z.check_collision(p)) {

				if (z.shot == false && z.alive) {
					EffectOnActorPointer ac{ &z };
					effect.vEff_struct.push_back(ac);
					z.shot = true;
					p.body_hit_times++;
				}
			}
	}


	for (int i = 0; i < vBullets.size(); ++i) {
		if (vBullets[i].body_hit_times > 0 || vBullets[i].location.x > map.get_width() || vBullets[i].location.y > map.get_height()) {
			vBullets.erase(vBullets.begin() + i);
			continue;
		}
		// if (p.hit_body) {vBullets.erase(vec.begin() + indice); continue;}
		vBullets[i].location = vBullets[i].location + (vBullets[i].direction * vBullets[i].speed * fElapsedTime);
		FillCircle((vBullets[i].location.x - camera.get_offset().x) * 128, (vBullets[i].location.y - camera.get_offset().y) * 128, 1, olc::BLACK);
	}


	// draw dead actors first
	for (Actor* a : vActors)
		if (!a->alive)
			a->draw();

	// draw alive actors by height
	sort_actors_by_height(); 
	for (Actor* a : vActors) {
		if (a->alive)
			a->draw();

		//FillCircle( (a->get_location().x - camera.get_offset().x)  * 128, (a->get_location().y - camera.get_offset().y) * 128, 3, olc::RED);
	}

	// renders candidates for splat effect
	effect.render_effect(this, fElapsedTime, camera.get_offset());



	return true;
}



//std::string pos = std::to_string (actor.location.y);
//DrawString(40, 40, pos, olc::YELLOW);


Vec2 zHunt::placeInCenter() const
{
	return  Vec2{ winWidth / 2, winHeight / 2 };
}

void zHunt::sort_actors_by_height()
{
	struct by_height {
		bool operator()(Actor* const a, Actor* const b) const noexcept {
			return a->get_location().y < b->get_location().y;
		}
	};
	std::sort(vActors.begin(), vActors.end(), by_height());
}

void zHunt::draw_effect_on_actor(Actor& actor)
{
}



float zHunt::getWinWidth() const
{
	return winWidth;
}

float zHunt::getWinHeight() const
{
	return winHeight;
}

