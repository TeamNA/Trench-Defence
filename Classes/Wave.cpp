#include "Wave.h"

USING_NS_CC;

bool Wave::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

Wave* Wave::initWithCreep(Creep* creep, double SpawnRate, int TotalCreeps)
{
	// To call a wave, initWithCreep should include the type of creep, the spawnrate and the total amount to spawn
	this->creepType = creep;
	this->spawnRate = SpawnRate;
	this->totalCreeps = TotalCreeps;

	return this;
}