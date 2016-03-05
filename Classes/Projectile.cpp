#include "Projectile.h"

/*Projectile* Projectile::projectile()
{
	Projectile* projectile = (Projectile*)Sprite::create();
	if (projectile != NULL)
	{
		return projectile;
	}
	else {
		return NULL;
	}
}*/

/*Projectile* MachineGunProjectile::projectile()
{
	Projectile* projectile = (Projectile*)Sprite::create("Projectile.png");
	if (projectile != NULL)
	{
		return projectile;
	}
	else {
		return NULL;
	}
}

Projectile* FastMachineGunProjectile::projectile()
{
	Projectile* projectile = (Projectile*)Sprite::create("Projectile.png");
	if (projectile != NULL)
	{
		return projectile;
	}
	else {
		return NULL;
	}
}

Projectile* MissleProjectile::projectile()
{
	Projectile* projectile = (Projectile*)Sprite::create("Projectile.png");
	if (projectile != NULL)
	{
		return projectile;
	}
	else {
		return NULL;
	}
}*/

Projectile* MachineGunProjectile::projectile()
{
	Projectile* projectile = Projectile::create();
	projectile->projectileSprite = Sprite::create("Projectile.png");
	if (projectile != NULL)
	{
		projectile->addChild(projectile->projectileSprite);
		// projectile->setScale(0.5);
		projectile->projectileDamage = 1.2;
		projectile->type = ProjectileType::MachineGunProjectile;
		return projectile;
	}
	else
	{
		return NULL;
	}
}

bool MachineGunProjectile::init()
{
	if (!Sprite::init())
		return false;
	return true;
}


Projectile* FastMachineGunProjectile::projectile()
{
	Projectile* projectile = Projectile::create();
	projectile->projectileSprite = Sprite::create("Projectile.png");
	projectile->addChild(projectile->projectileSprite);
	// projectile->setScale(0.6);
	projectile->projectileDamage = 0.8;
	projectile->type = ProjectileType::FastMachineGunProjectile;
	return projectile;
}

bool FastMachineGunProjectile::init()
{
	if (!Sprite::init())
		return false;
	return true;
}


Projectile* MissleProjectile::projectile()
{
	Projectile* projectile = Projectile::create();
	projectile->projectileSprite = Sprite::create("Projectile.png");
	projectile->addChild(projectile->projectileSprite);
	projectile->setScale(1.2);
	projectile->projectileDamage = 4;
	projectile->type = ProjectileType::MissleProjectile;
	return projectile;
}

bool MissleProjectile::init()
{
	if (!Sprite::init())
		return false;
	return true;
}


