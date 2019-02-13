#include "Rifleman.h"

void Rifleman::follow()
{
		moveTowardsGoal();
}


void Rifleman::moveTowardsGoal()
{
		Vec2 coord = goal - location;
		location += coord.GetNormalized() * eTime * speed;
		moving = true;
}


void Rifleman::standGround()
{
	vector <Zombie*> vTargetsOnScreen;
	vTargetsOnScreen = actorsOnScreen(vpZom);

	if (!vTargetsOnScreen.empty()) {
		Zombie* z = closestTarget(vTargetsOnScreen);
		goal = z->get_location();

		if (turn.complete())
			turn.setCurrent(get_facing(goal));
		shootAtTarget(z);
	}
}


void Rifleman::shootAtTarget(Zombie* target_in)
{
	if (turn.complete() ) {
		if (renderer.get_current_anim() != FIRE || renderer.get_current_anim() != RELOAD) 
			fire(true, target_in->get_location() * 128);
	}
	else
		fired = false;
}


Vec2 Rifleman::getFireAngle()
{
	return fireAngle;
}

void Rifleman::getSounds(int f1, int f2, int r)
{
	snd_fire1 = f1;
	snd_fire2 = f2;
	snd_reload = r;

}

void Rifleman::die()
{
	alive = false;
}


Zombie* Rifleman::closestTarget(vector<Zombie*> vec)
{
	float smallest = 9999999.0f;
	int closeset_index;

	for (int i = 0; i < vec.size(); ++i) {
		Vec2 distance = location - vec[i]->get_location();

		if (distance.GetLengthSq() < smallest) {
			smallest = distance.GetLengthSq();
			closeset_index = i;
		}
	}


	return vec[closeset_index];
}



bool Rifleman::update(float fElapTm, const Vec2 & cam_off, vector<Zombie*> vpZom_in)
{
	eTime = fElapTm;
	camera_offset = cam_off;
	renderer.update_offset(camera_offset);
	

	if (!isPlayer) {
		int a = renderer.get_current_anim() != FIRE; // compress after check
		turn.update(fElapTm, a);
		if (turn.complete())
			turn.setCurrent(get_facing(goal));
		facing = facings(turn.getFacing());
	}
	else
		look_at_vec(goal);

	vpZom = vpZom_in;
	kar.update(fElapTm);

	if (moving) {

		if (walking_backwards() && isPlayer) {
			renderer.request_animation(WALK, vSpriteSheetPointers[WALK], INTERRUPTABLE, REVERSED, NOT_LOOPED, NOT_BACK_FORTH, 0, 4.0f);
			speed = 0.32f;
		}

		else {
			if (!Actor::running) {
				renderer.request_animation(WALK, vSpriteSheetPointers[WALK], 1, 0, 0, 0, 0, 6.5f);
				speed = 0.8f;
			}

			else {
				renderer.request_animation(RUN, vSpriteSheetPointers[RUN], 1, 0, 0, 0, 0, 9.5f);
				speed = 1.300f;
			}
		}
	}

	else if (fired) 
		renderer.request_animation(FIRE, vSpriteSheetPointers[FIRE], 0, 0, 0, 0, 0, 15.5f);
	
	else if (kar.bolting() || kar.getReloadState()) {
		renderer.request_animation(RELOAD, vSpriteSheetPointers[RELOAD], 1, 0, 0, 0, 0, 1.0f);
	}

	else if (aiming) 
		renderer.request_animation(AIM, vSpriteSheetPointers[AIM], 1, 0, 0, 0, 0, 3.0f);

	else if (!alive)
		renderer.request_animation(9, vSpriteSheetPointers[9], 0, 0, 0, 0, 1, 7.5f);

	else 
		renderer.request_animation(IDLE, vSpriteSheetPointers[IDLE], 1, 0, 1, 1, 0, 1.5f);
		
	
	

	old_location = location;			// needed for facing
	moving = false;
	Actor::running = false;
	aiming = false;

	

	return fired;
}

void Rifleman::updateFireAngle(Vec2 fireAt)
{
	float dx;
	float dy;

	if (isPlayer) {
		dx = fireAt.x - ( (location.x - camera_offset.x) * 128);
		dy = fireAt.y - ( (location.y - camera_offset.y) * 128);
	}

	else {
		dx = fireAt.x - (location.x * 128);
		dy = fireAt.y - (location.y * 128);
	}

	Vec2 vec{ dx, dy };
	fireAngle = vec.GetNormalized();
}

void Rifleman::reload()
{
	renderer.request_animation(RELOAD, vSpriteSheetPointers[RELOAD], 0, 0, 0, 0, 0, 2.0f);
}

void Rifleman::running()
{
	Actor::running = true;
}

void Rifleman::aim()
{
	aiming = true;
}

void Rifleman::fire(bool b, Vec2 fireAt)
{
	fired = b;

	if (fired){
		if (kar.fire()) 
			updateFireAngle(fireAt);
		
		else {
			fired = false;
			if (kar.checkRounds() <= 0)
				kar.doReload();
		}
	}
}



void Rifleman::moveUp()
{
	moving = true;
	location.y -= eTime * speed;
}

void Rifleman::moveDown()
{
	moving = true;
	location.y += eTime * speed;
}

void Rifleman::moveLeft()
{
	moving = true;
	location.x -= eTime * speed;
}

void Rifleman::moveRight()
{
	moving = true;
	location.x += eTime * speed;
}

vector<Zombie*> Rifleman::actorsOnScreen(vector<Zombie*> vec)
{
	vector<Zombie*> vOnScreen;

	float x = location.x * 128;
	float y = location.y * 128;

	int halfScreenX = 768 / 2;
	int halfScreenY = 640 / 2;

	for (Zombie* ac : vec) {
		float ZlocX = ac->get_location().x * 128;
		float ZlocY = ac->get_location().y * 128;

		if ((ZlocX > x - halfScreenX && ZlocX < x + halfScreenX) && (ZlocY > y - halfScreenY && ZlocY < y + halfScreenY))
			if (ac->alive)
				vOnScreen.push_back(ac);
	}


	return vOnScreen;
}




void Rifleman::load_assets()
{

	load_spr_sheet("sprites\\rifleman\\NEW\\aim\\r_aim.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\climb\\r_climb.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\idle\\r_idle.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\pick\\r_pick.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\run\\r_run.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\walk\\r_walk.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\fire\\r_fire.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\reload\\r_reload.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\hurt\\r_hurt.png");
	load_spr_sheet("sprites\\rifleman\\NEW\\die\\r_die.png");


	vector <string> mappingData;

	mappingData.push_back({ "sprites\\rifleman\\NEW\\aim\\r_aim.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\climb\\r_climb.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\idle\\r_idle.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\pick\\r_pick.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\run\\r_run.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\walk\\r_walk.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\fire\\r_fire.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\reload\\r_reload.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\hurt\\r_hurt.txt" });
	mappingData.push_back({ "sprites\\rifleman\\NEW\\die\\r_die.txt" });

	Actor::load_assets(mappingData);

}

