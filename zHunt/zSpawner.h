#pragma once
#include "Zombie.h"
#include "Portal.h"
#include <random>

class zSpawner {

public:
	
	void load(vector <Zombie*>* vZ, vector <Portal*>* vP, vector <Actor*>* vA, olc::PixelGameEngine* pge_in, vector <olc::Sprite*>* vZomSprites_in);
	void update(float eTime, int zombiesAlive);
	void spawnZ();
	void spawnZat(int portalIndex);


private:
	static constexpr int zombieMax = 170;
	int spawnReady = 1;
	int zombiesAliveTotal;
	float spawnTimer = 0.0f;

	vector <olc::Sprite*>* vZomSprites;
	vector <Zombie*>* vZom;
	vector <Portal*>* vPrt;
	vector <Actor*>* vAct;
	float fElapsedTime;
	olc::PixelGameEngine* pge;
};