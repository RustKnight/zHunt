#include "Portal.h"

void Portal::setIndex(int i)
{
	index = i;
}

void Portal::load_assets(vector <olc::Sprite*>* vpPrt)
{
	vSpriteSheetPointers = vpPrt;

		vector <string> mappingData;
		mappingData.push_back({ "sprites\\portals\\brown_idle\\idle.txt" });
		mappingData.push_back({ "sprites\\portals\\red_idle\\idle.txt" });	
		mappingData.push_back({ "sprites\\portals\\blue_idle\\idle.txt" });

		mappingData.push_back({ "sprites\\portals\\brown_open\\open.txt" });
		mappingData.push_back({ "sprites\\portals\\red_open\\open.txt" });
		mappingData.push_back({ "sprites\\portals\\blue_open\\open.txt" });
		
		Actor::load_assets(mappingData);
}



//bool interruptable, bool reversed_in, bool loop_in, bool back_and_forth, bool end_lock_in, float speed

void Portal::update(float eTime_in, const Vec2 & cam_off, bool triggered)
{
	eTime = eTime_in;
	camera_offset = cam_off;
	renderer.update_offset(camera_offset);

	if (actorsTeleported > 4)
		readyTimer += eTime * 1.0f;

	if (index == 0) {
		cout << actorsTeleported << endl;
		cout << "Timer: " << readyTimer << endl;
	}

	if (!isSpawner) {

		if (timeOpened > openTimeMax && opened) {
			//teleAway();

		}
		else
			openPortal();
	
		timeOpened += eTime * 1.0f;
	}

	else
		openPortal();
}


void Portal::teleAway()
{
	if (closePortal()) {

		location.x = 1 + rand() % 14;
		location.y = 1 + rand() % 8;
		timeOpened = 0;
	}

}




void Portal::openPortal()
{
	if (!opened) {

		isActive = true;				//flag that it's safe to draw portal

		transitionDone = renderer.animationCount;

		if (!transitionDone && !opened)
			renderer.request_animation(color_open, (*vSpriteSheetPointers)[color_open], 0, 0, 0, 0, 1, speed * 15.0f);

		else {
			renderer.override(color_idle, (*vSpriteSheetPointers)[color_idle], 1, 0, 1, 1, 0, speed * 15.0f);
			opened = true;
		}

	}

	else
		renderer.animationCount = 0;
}


bool Portal::closePortal()
{
	if (opened) {
		
		renderer.request_animation(color_open, (*vSpriteSheetPointers)[color_open], 1, 1, 0, 0, 1, speed * 15.0f);

		transitionDone = renderer.animationCount;


		if (transitionDone) {
			isActive = false;
			opened = false;
			renderer.animationCount = 0;
			return true;
		}
		
	}

}

bool Portal::getStatus() const
{
	return opened;
}

bool Portal::isReady()
{
	static constexpr int resetReady = 5;

	// if we teleported more than five start counting
	
	if (readyTimer > resetReady) {
		actorsTeleported = 0;
		readyTimer = 0.0f;
		return true;
	}

	if (actorsTeleported < 5)
		return true;

	return false;
}


void Portal::becomeSpawner(Vec2 spw_loc)
{
	color_idle = BROWN_IDLE;
	color_open = BROWN_OPEN;

	location = spw_loc;
	isSpawner = true;
}

void Portal::tryTeleport(Actor& act)
{
							// in range						//waited enough since last
	if (withinDistance(act.get_location(), 2000) && (act.timeSinceLastTele > teleCooldown) && opened && act.alive && !isSpawner && act.desiredPrtIndex != -1) {
		
		if (isReady()) {
			act.timeSinceLastTele = 0;
			actorsTeleported++;
			teleport(act);
		}
	}
}

void Portal::teleport(Actor& act)
{
	if (pairing) {
		int i;

		if (index % 2 == 0)
			i = index + 1;
		else
			i = index - 1;

		act.set_location((*vpPrt)[i]->get_location());
	}

	else 		
		act.set_location((*vpPrt)[act.desiredPrtIndex]->get_location());
	
}



