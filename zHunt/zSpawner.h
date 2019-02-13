#pragma once
#include "Zombie.h"
#include "Portal.h"
#include <random>

class zSpawner {

public:
	
	void load(vector <Zombie*>* vZ, vector <Portal*>* vP, vector <Actor*>* vA, olc::PixelGameEngine* pge_in);
	void update(float eTime);
	void spawnZ();


private:
	int spawnReady = 2;
	float spawnTimer = 0.0f;

	vector <Zombie*>* vZom;
	vector <Portal*>* vPrt;
	vector <Actor*>* vAct;
	float fElapsedTime;
	olc::PixelGameEngine* pge;
};