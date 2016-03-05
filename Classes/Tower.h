#pragma once
#include "cocos2d.h"
#include "Creep.h"
#include "Projectile.h"

enum TowerType
{
	MachineGunTurret,
	FastMachineGunTurret,
	MissleGunTurret,
};

class Tower : public Sprite
{
public:
	int range;
	int attackDamage;
	// Sprite *deck;
	Sprite* sprite;
	Creep* target;
	Sprite * selSpriteRange;
	Creep* getClosestTarget();
	Projectile* nextProjectile;

	CREATE_FUNC(Tower);
};

class MachineGunTower : public Tower
{
public:
	// int attackDamage = 1;
	static Tower* tower();
	bool virtual init();
	void towerLogic(float dt);
	// void getAttackDamage();

	void finishFiring();
	void creepMoveFinished(Node* sender);
};

class FastMachineGunTower : public Tower
{
public:
	// float attackDamage = 0.4;
	static Tower* tower();
	bool virtual init();
	void towerLogic(float dt);

	void finishFiring();
	void creepMoveFinished(Node* sender);
};

class MissleGunTower : public Tower
{
public:
	// float attackDamage = 3.5;
	static Tower* tower();
	bool virtual init();
	void towerLogic(float dt);

	void finishFiring();
	void creepMoveFinished(Node* sender);
};