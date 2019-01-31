#include "Zombie.h"




void Zombie::randomize_stats(float speed_in)
{
	speed = speed_in;
	location.x = rand() % 16;
	location.y = rand() % 10;
	random_death_anim = rand() % 8;
}



void Zombie::is_hit()
{	
	hit = true;
	hp -= 5 + rand() % 5;

	if (hp < 0)
		alive = false;

	if (alive)
		renderer.request_animation(HIT, vSpriteSheetPointers[HIT], 0, 0, 0, 0, 0, 5.5f);
}

void Zombie::attack_target(Actor& target)
{
	renderer.request_animation(ATTACK, vSpriteSheetPointers[ATTACK], 0, 0, 0, 0, 0, 8.0f);
	
	target.take_damage(rand() % 5);
}

bool Zombie::attack_cooldown_over()
{
	// if speed of cooldown matches speed of animation - we get synced constant attacks
	// if a brake between attacks is wanted, then another float that grows slower than att_anim_cd_over should be implemented
	// if (att_anim_cd_over && att_cd_over) -> attack;

	if ((int)att_cooldown >= renderer.get_animation_seqences_count(ATTACK, facing)) {
		att_cooldown = 0;
		return true;
	}

	return false;
}

void Zombie::load_assets()
{

	load_spr_sheet("sprites\\zombie\\attack\\z_attack.png");
	load_spr_sheet("sprites\\zombie\\die\\z_die.png");
	load_spr_sheet("sprites\\zombie\\hit\\z_hit.png");
	load_spr_sheet("sprites\\zombie\\idle\\z_idle.png");
	load_spr_sheet("sprites\\zombie\\walk\\z_walk.png");


	vector <string> map;

	map.push_back({ "sprites\\zombie\\attack\\z_attack.txt" });
	map.push_back({ "sprites\\zombie\\die\\z_die.txt" });
	map.push_back({ "sprites\\zombie\\hit\\z_hit.txt" });
	map.push_back({ "sprites\\zombie\\idle\\z_idle.txt" });
	map.push_back({ "sprites\\zombie\\walk\\z_walk.txt" });

	Actor::load_assets(map);
}

bool Zombie::in_range(Vec2 target) const
{
	if (check_collision(target))
		return true;

	return false;
}

bool Zombie::check_collision(Vec2 location) const
{

	int x = (location.x - camera_offset.x) * 128;
	int y = (location.y - camera_offset.y) * 128;

	RenderRect r_rect = renderer.get_render_rect();

	if ((y > r_rect.top && y < r_rect.bottom) && (x > r_rect.left && x < r_rect.right)) 
		return true;
	else
		return false;
}

void Zombie::stay()
{
	location = old_location;
	renderer.request_animation(IDLE, vSpriteSheetPointers[IDLE], 1, 0, 1, 1, 0, speed * 5.0f);
}



bool Zombie::update(float fElapTm, const Vec2 & cam_off)
{
	eTime = fElapTm;
	camera_offset = cam_off;
	renderer.update_offset(camera_offset);
	old_location = location;


	if (renderer.get_current_anim() != HIT)
		hit = false;


	if (alive && !hit) {

		location += goal.GetNormalized() * eTime * speed;

		if (old_location != location)
			renderer.request_animation(WALK, vSpriteSheetPointers[WALK], 1, 0, 0, 0, 0, speed * 30.0f);

		look_at_vec(goal);

		if (att_cooldown < 200.0f)
			att_cooldown += eTime * 4.0f;

		if (isPlayer) {

			if (pge->GetKey(olc::W).bHeld)
				location.y -= eTime * speed;
			if (pge->GetKey(olc::S).bHeld)
				location.y += eTime * speed;
			if (pge->GetKey(olc::A).bHeld)
				location.x -= eTime * speed;
			if (pge->GetKey(olc::D).bHeld)
				location.x += eTime * speed;


			if (pge->GetKey(olc::I).bPressed)
				renderer.request_animation(DIE, vSpriteSheetPointers[DIE], 0, 0, 0, 0, 0, 13.5f);
		}
	}


	else if (alive)
		renderer.request_animation(IDLE, vSpriteSheetPointers[IDLE], 1, 0, 1, 1, 0, speed * 5.0f);

	if (!alive) {
		facing = facings(random_death_anim);
		renderer.override (DIE, vSpriteSheetPointers[DIE], 0, 0, 0, 0, 1, 13.5f);
	}

	return 0;
}

