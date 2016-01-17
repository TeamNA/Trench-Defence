#include "Creep.h"
#include "WayPoint.h"
#include "DataModel.h"

USING_NS_CC;

bool Creep::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

Creep* Creep::initWithCreep(Creep* copyFrom)
{
	return NULL;
}

Creep* FastRedCreep::creep()
{
	auto creep = Creep::create();
	creep->sprite = Sprite::create("Enemy1.png");
	creep->setScale(0.3);
	creep->addChild(creep->sprite, 0);
	creep->curHp = 10;
	creep->moveDuration = 3;
	// The curWaypoint may need to be changed depending on the tmx points
	creep->curWaypoint = 0;
	return creep;
}

Creep* StrongGreenCreep::creep()
{
	auto creep = Creep::create();
	creep->sprite = Sprite::create("Enemy2.png");
	creep->setScale(0.3);
	creep->addChild(creep->sprite, 0);
	creep->curHp = 30;
	creep->moveDuration = 8;
	// The curWaypoint may need to be changed depending on the tmx points
	creep->curWaypoint = 0;
	return creep;
}

WayPoint* Creep::getCurrentWaypoint()
{
	// Make use of the DataModel to get the next waypoint
	DataModel* m = DataModel::getModel();
	WayPoint* waypoint = (WayPoint *)m->waypoints.at(this->curWaypoint);
	return waypoint;
}

WayPoint* Creep::getNextWaypoint()
{
	DataModel* m = DataModel::getModel();

	// Increment the waypoint by 1 if it hasn't reached the last checkpoint
	if (this->curWaypoint != 11)
	{
		this->curWaypoint++;
	}
	
	else
	{
		// If we wanted to loop the waypoint movement we would uncommment this
		// this->curWaypoint = 0;
	}
	

	CCLOG("%d", this->curWaypoint); // For testing.

	WayPoint *waypoint = (WayPoint *)m->waypoints.at(curWaypoint);
	return waypoint;
}