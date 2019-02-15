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
// zombie rotate speed - move towards goal, only if facing is correct, takes time to turn around depending on their speed
// civilians could easily be added choosing the closest threat and running in opposite direction
// go to waypoints


// animation sync so that when zombie finishes hitting , player plays hurt
// get rid of silly cascading initializations ; if a zombie class will be a zombie, make asset specific stuff be part of the class

zHunt::zHunt() :
	winWidth { 768.0f},
	winHeight{ 640.0f },
	rifleman{ Vec2 {4.0f, 3.7f}, this},
	camera {this, &map, getWinWidth(), getWinHeight()},
	control {this}
{
	sAppName = "zHunt";
}



bool zHunt::OnUserCreate() 
{
	//effect.splat_effects = new olc::Sprite("sprites\\effects\\splat_darker.png");
	//effect.effect_handler.load_mapping_info_string("sprites\\effects\\splat.txt");

	olc::SOUND::InitialiseAudio(44100, 1, 8, 512);

	snd_fire1 = olc::SOUND::LoadAudioSample("sounds\\f-r.wav");
	snd_fire2 = olc::SOUND::LoadAudioSample("sounds\\fire2.wav");
	snd_reload = olc::SOUND::LoadAudioSample("sounds\\reload.wav");
	snd_zom1_hit = olc::SOUND::LoadAudioSample("sounds\\zombie_hit1.wav");
	snd_zom2_hit = olc::SOUND::LoadAudioSample("sounds\\zombie_hit2.wav");
	snd_zom3_hit = olc::SOUND::LoadAudioSample("sounds\\zombie_hit3.wav");
	
	loadResources();
	

	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::uniform_real_distribution <float> distR(0.2f, 0.4f);  // (0.1f, 0.25f);
	
	

	for (int i = 0; i < 1; i++) {
		Rifleman* rf = new Rifleman{ Vec2{ 10.0f + i, 4.0f }, this };
		rf->load_assets(&vRflSprites);
		rf->loadPortalsPointer(&vPortals);		//CAN REMOVE IF RIFLE SHOULD NOT TELEPORT
		vRifles.push_back(rf);
		vActors.push_back(rf);
		ai.loadRiflemen(rf);
	}


	for (int i = 0; i < 4; i++) {
		Portal* prt = new Portal{ Vec2{ 5,0 }, this, &vPortals };
		prt->load_assets(&vPrtSprites);
		
		//if (i < 3)
		//	prt->becomeSpawner(Vec2{ float(rand() % 16), float(rand() % 10) });
		
		prt->setIndex(i);
		vPortals.push_back(prt);
		vActors.push_back(prt);
	}

	vPortals[0]->set_location(Vec2{ 1, 3 });
	vPortals[1]->set_location(Vec2{ 4, 3 });

	vPortals[2]->set_location(Vec2{ 1, 6 });
	vPortals[3]->set_location(Vec2{ 4, 6 });
	

	rifleman.load_assets(&vRflSprites);
	rifleman.loadPortalsPointer(&vPortals);
	vRifles.push_back(&rifleman);



	for (int i = 0; i < 8; i++) {
		Zombie* zom = new Zombie(Vec2{ 0,0 }, this, &vPortals);			// we should handle proper destruction of zombie
		zom->load_assets(&vZomSprites);
		zom->randomize_stats(distR(e));	
	//	zom->randomizeStartLocation();
		vZombies.push_back(zom);
		vActors.push_back(zom);
	}

	vZombies[0]->set_location(Vec2{ 1.0f, 3.7f });


	camera.load_fields("sprites\\terrain\\green.png");
	rifleman.become_player(1);
	
	rifleman.getSounds(snd_fire1, snd_fire2, snd_reload);
	
	vActors.push_back(&rifleman);

	zSpawn.load(&vZombies, &vPortals, &vActors, this, &vZomSprites);

	return true;
}



bool zHunt::OnUserUpdate(float fElapsedTime) 
{
	{
		Clear(olc::VERY_DARK_GREEN);
		SetPixelMode(olc::Pixel::ALPHA);


		camera.screen_in_view();
		ai.update(rifleman.get_location());
		ai.think();
		control.control(rifleman);
		zSpawn.update(fElapsedTime);
	}
	
	for (Portal* prt : vPortals) {
		prt->update(fElapsedTime, camera.get_offset(), 1);
	}


	for (Rifleman* rf: vRifles) {

		if (rf->update(fElapsedTime, camera.get_offset(), vZombies)) {
			olc::SOUND::PlaySample(snd_fire1);
			vBullets.push_back(Projectile{ rf->get_location(), rf->getFireAngle() });
		}

		if (rf->alive && rf->hp < 0)
			rf->die();
	}

	int zombiesFeedingOnDead = 0;

	for (Zombie* z : vZombies) {

		z->update(fElapsedTime, camera.get_offset());
		z->loadZfeed(&zombiesFeedingOnDead);


		if (z->alive && !z->hit) {

			// create vector with RFL locations for Zombie to process
			vector<Vec2> vRflLocations;
			for (Rifleman* rf : vRifles)
				vRflLocations.push_back(rf->get_location());

			// evaluate and get index
			int closestFleshIndex = z->closestFlesh(&vRflLocations, vRifles[0]->alive, vRifles[1]->alive);


			if (toggle_hunger) {

				if (!z->in_range(vRifles[closestFleshIndex]->get_location())) {
					z->moveTowardsGoal();
				}

				else if (z->attack_cooldown_over())
					z->attack_target(*vRifles[closestFleshIndex]);
			}
		}

	

		for (Projectile& p : vBullets)
			if (z->withinOwnRect(p.location)) {
				z->is_hit();

				if (z->shot == false && z->alive) {
					EffectOnActorPointer ac{ z };
					effect.vEff_struct.push_back(ac);
					z->shot = true;
					p.body_hit_times++;
					//olc::SOUND::PlaySample(rand() % 4 + 4);
				}
			}
	}


	for (int i = 0; i < vBullets.size(); ++i) {
		
		if (vBullets[i].body_hit_times > 0 || vBullets[i].location.x > map.get_width() || vBullets[i].location.y > map.get_height()) {
			vBullets.erase(vBullets.begin() + i);
			continue;
		}
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
		if (a->alive && a->isActive)
			a->draw();
	}


	// renders candidates for splat effect
	//effect.render_effect(this, fElapsedTime, camera.get_offset());


	if (GetKey(olc::Q).bPressed)
		toggle_camera = !toggle_camera;
	if (GetKey(olc::G).bPressed)
		toggle_hunger = !toggle_hunger;
	(toggle_camera) ? camera.update(rifleman.get_location()) : camera.update(vZombies[0]->get_location());

	return true;
}

void zHunt::loadResources()
{
	
	olc::Sprite* spr = new olc::Sprite{ "sprites\\zombie\\attack\\z_attack.png" };
	vZomSprites.push_back(spr);

	 spr = new olc::Sprite{ "sprites\\zombie\\die\\z_die.png" };
	vZomSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\zombie\\hit\\z_hit.png" };
	vZomSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\zombie\\idle\\z_idle.png" };
	vZomSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\zombie\\walk\\z_walk.png" };
	vZomSprites.push_back(spr);	


	 spr = new olc::Sprite{ "sprites\\rifleman\\NEW\\aim\\r_aim.png" };
	vRflSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\rifleman\\NEW\\climb\\r_climb.png" };
	vRflSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\rifleman\\NEW\\idle\\r_idle.png" };
	vRflSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\rifleman\\NEW\\pick\\r_pick.png" };
	vRflSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\rifleman\\NEW\\run\\r_run.png" };
	vRflSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\rifleman\\NEW\\walk\\r_walk.png" };
	vRflSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\rifleman\\NEW\\fire\\r_fire.png" };
	vRflSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\rifleman\\NEW\\reload\\r_reload.png" };
	vRflSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\rifleman\\NEW\\hurt\\r_hurt.png" };
	vRflSprites.push_back(spr);
	 spr = new olc::Sprite{ "sprites\\rifleman\\NEW\\die\\r_die.png" };
	vRflSprites.push_back(spr);


	spr = new olc::Sprite{ "sprites\\portals\\brown_idle\\idle.png" };
	vPrtSprites.push_back(spr);
	spr = new olc::Sprite{ "sprites\\portals\\red_idle\\idle.png" };
	vPrtSprites.push_back(spr);
	spr = new olc::Sprite{ "sprites\\portals\\blue_open\\idle.png" };
	vPrtSprites.push_back(spr);
	spr = new olc::Sprite{ "sprites\\portals\\brown_open\\open.png" };
	vPrtSprites.push_back(spr);
	spr = new olc::Sprite{ "sprites\\portals\\red_open\\open.png" };
	vPrtSprites.push_back(spr);
	spr = new olc::Sprite{ "sprites\\portals\\blue_open\\open.png" };
	vPrtSprites.push_back(spr);

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



/*
piece of code to make zombies follow mouse cursor


Vec2 screen_vec{ (float)GetMouseX(), (float)GetMouseY() };
Vec2 screen_to_tile = Vec2{ screen_vec.x / 128.0f, screen_vec.y / 128.0f };
Vec2 map_vec = camera.get_offset() + screen_to_tile;
Vec2 temp_go_to = map_vec;
temp_go_to.x = (int)temp_go_to.x;
temp_go_to.y = (int)temp_go_to.y;


*/