#pragma once
#include "Zombie.h"
#include "Portal.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>

class zSpawner {

public:
	
	void load(vector <Zombie*>* vZ, vector <Portal*>* vP, vector <Actor*>* vA, olc::PixelGameEngine* pge_in, vector <olc::Sprite*>* vZomSprites_in);
	void update(float eTime, int zombiesAlive);
	void spawnZ();
	void spawnZat(int portalIndex);

	bool hasDott(string s);
	bool intro;

private:
	int zombieMax = 170;
	float spawnReady = 1;
	int zombiesAliveTotal;
	float spawnTimer = 0.0f;
	

	vector <olc::Sprite*>* vZomSprites;
	vector <Zombie*>* vZom;
	vector <Portal*>* vPrt;
	vector <Actor*>* vAct;
	float fElapsedTime;
	olc::PixelGameEngine* pge;
};