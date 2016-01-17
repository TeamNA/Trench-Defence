#ifndef __LEVEL1_SCENE_H__
#define __LEVEL1_SCENE_H__

#include "cocos2d.h"
#include "Creep.h"
#include "WayPoint.h"
#include "Wave.h"
#include "GameHUD.h"

using namespace cocos2d;

class Level1 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	~Level1();
	virtual bool init();

	// Important Variables
	int currentLevel;
	void addWayPoint();
	void addWaves();
	void FollowPath(Node *sender);
	void gameLogic(float dt);
	void addTarget();
	virtual void update(float dt);
	Wave* getCurrentWave();
	Wave* getNextWave();


	// implement the "static create()" method manually
	CREATE_FUNC(Level1);

	void menuCloseCallback(cocos2d::Ref* pSender);
	void setViewPointCenter(cocos2d::Point position);
	// Tower
	void addTower(Point pos);
	Point tileCoordForPosition(Point position);
	bool canBuildOnTilePosition(Point pos);
	Point boundLayerPos(Point newPos);

	Point position;
	GameHUD *gameHUD;

private:
	
	CCTMXTiledMap *_tileMap;
	CCTMXLayer *_background;
	CCTMXLayer *_walls;
	CCTMXLayer *_turrets;
	CCTMXLayer *_buildable;
	CCSprite *_enemyUnit1;
};

#endif // __LEVEL1_SCENE_H__
