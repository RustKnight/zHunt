#include "zSpawner.h"

void zSpawner::load(vector<Zombie*>* vZ, vector<Portal*>* vP, vector <Actor*>* vA, olc::PixelGameEngine* pge_in)
{
	vZom = vZ;
	vPrt = vP;
	vAct = vA;
	pge = pge_in;
}

void zSpawner::update(float eTime)
{
	fElapsedTime = eTime;
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
	std::uniform_real_distribution <float> distR(0.1f, 0.25f);

	int spawnCount = 0;

	for (Portal* prt: *vPrt) {

		bool canSpawn = rand() % 2;
		if (canSpawn) {

			Zombie* zom = new Zombie(prt->get_location(), pge);			// we should handle proper destruction of zombie
			zom->load_assets();
			zom->randomize_stats(distR(e));
			vZom->push_back(zom);
			(*vAct).push_back(zom);
			spawnCount++;
		}

	}
	
	cout << spawnCount << endl;
}
