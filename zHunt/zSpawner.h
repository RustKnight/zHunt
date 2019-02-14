#pragma once
#include "Zombie.h"
#include "Portal.h"
#include <random>

class zSpawner {

public:
	
	void load(vector <Zombie*>* vZ, vector <Portal*>* vP, vector <Actor*>* vA, olc::PixelGameEngine* pge_in, vector <olc::Sprite*>* vZomSprites_in, vector<Rifleman*>* vR);
	void update(float eTime);
	void spawnZ();


private:
	int spawnReady = 4;
	float spawnTimer = 0.0f;

	vector <olc::Sprite*>* vZomSprites;
	vector <Zombie*>* vZom;
	vector<Rifleman*>* vRfl;
	vector <Portal*>* vPrt;
	vector <Actor*>* vAct;
	float fElapsedTime;
	olc::PixelGameEngine* pge;
};