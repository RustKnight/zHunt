#include "zSpawner.h"


bool zSpawner::hasDott(string s)
{
	int dotCount = 0;

	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '.')
			dotCount++;
	}

	if (dotCount >= 1)
		return true;

	return false;
}


void zSpawner::load(vector<Zombie*>* vZ, vector<Portal*>* vP, vector <Actor*>* vA, olc::PixelGameEngine* pge_in, vector <olc::Sprite*>* vZomSprites_in)
{
	std::ifstream file{ "settings.txt" };
	if (!file.is_open()) {
		cout << "Settings not open. Default values loaded";
	}

	else {

		enum variables {MAX_ZOMBIES, SPAWN_INTERVAL};
		string candidate;
		float number = -1;
		int alocator = 0;

		for (char ch; file.get(ch);) {

			bool hasAlreadyDott = hasDott(candidate);

			if (isdigit(ch) || (ch == '.' && !candidate.empty() && !hasAlreadyDott))
				candidate += ch;

			else if (ch == ';')
				number = ::atof(candidate.c_str());


			if (number != -1) {

				if (alocator == MAX_ZOMBIES) {
					zombieMax = number;
					number = -1;
					candidate.clear();
					alocator++;
				}

				else if (alocator == SPAWN_INTERVAL)
					spawnReady = number;
			}
		}

	}


	vZomSprites = vZomSprites_in;
	vZom = vZ;
	vPrt = vP;
	vAct = vA;
	pge = pge_in;
}

void zSpawner::update(float eTime, int zombiesAlive)
{
	fElapsedTime = eTime;
	zombiesAliveTotal = zombiesAlive;
	spawnTimer += eTime * 1.0f;

	if (spawnTimer > spawnReady) {
		spawnZ();
		spawnTimer = 0;
	}
}


void zSpawner::spawnZ()
{
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::uniform_real_distribution <float> distR(0.1f, 0.30f);

	int spawnCount = 0;

	for (Portal* prt: *vPrt) {

		bool canSpawn = rand() % 2;
		if (canSpawn && prt->getStatus() && prt->isSpawner && prt->visible && prt->isActive && zombiesAliveTotal < zombieMax) {

			Zombie* zom = new Zombie(prt->get_location(), pge, vPrt);			// we should handle proper destruction of zombie
			zom->load_assets(vZomSprites);
			zom->randomize_stats(distR(e));
			vZom->push_back(zom);
			(*vAct).push_back(zom);

			spawnCount++;
		}

	}
	
	cout << "Spawned this round: " << spawnCount << endl;
}

void zSpawner::spawnZat(int portalIndex)
{
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::uniform_real_distribution <float> distR(0.1f, 0.30f);


	Zombie* zom = new Zombie((*vPrt)[portalIndex]->get_location(), pge, vPrt);			// we should handle proper destruction of zombie
	zom->load_assets(vZomSprites);
	zom->randomize_stats(distR(e));
	zom->changeSpeed(0.18f);
	vZom->push_back(zom);
	(*vAct).push_back(zom);
}

