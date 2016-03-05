#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum ProjectileType {
	MachineGunProjectile,
	FastMachineGunProjectile,
	MissleProjectile
};

class Projectile : public Sprite
{
public:
	// Projectile* projectile();
	Sprite* projectileSprite;
	float projectileDamage;
	ProjectileType type;

	CREATE_FUNC(Projectile);
};

class MachineGunProjectile : public Projectile
{
public:
	static Projectile* projectile();
	bool virtual init();
};

class FastMachineGunProjectile : public Projectile
{
public:
	static Projectile* projectile();
	bool virtual init();
};

class MissleProjectile : public Projectile
{
public:
	static Projectile* projectile();
	bool virtual init();
};



