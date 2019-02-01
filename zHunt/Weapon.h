#pragma once


class Weapon {

public:
	Weapon (int in_clipMax, int in_clipNow, int in_damage, float in_fireRate, float in_fireCD, int in_reloadTime, float in_reload, bool in_reloading)
		: clipMax { in_clipMax }, clipNow { in_clipNow }, damage { in_damage }, fireRate { in_fireRate }, fireCD { in_fireCD }, reloadTime { in_reloadTime }, reload { in_reload }, reloading { in_reloading }
	{}

	bool fire ();
	int checkRounds() const;
	void doReload();
	void update(float eTime);
	bool getReloadState() const;

private:
	bool clipEmpty();
	bool fireCoolDown();


private:
	int clipMax;
	int clipNow;

	int damage;

	float fireRate;
	float fireCD;

	int reloadTime;
	float reload;

	bool reloading;
};



class Carabine : public Weapon {
public:
	Carabine(int in_clipMax, int in_clipNow, int in_damage, float in_fireRate, float in_fireCD, int in_reloadTime, float in_reload, bool in_reloading) :
		Weapon (in_clipMax, in_clipNow, in_damage, in_fireRate, in_fireCD, in_reloadTime, in_reload, in_reloading)
	{}

	bool bolting();
};