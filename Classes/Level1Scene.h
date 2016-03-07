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
	// void updateAvailableTowers(int totalMachineGunTowers, int totalFastMachineGunTowers, int totalMissleTowers);
	virtual void update(float dt);
	Wave* getCurrentWave();
	Wave* getNextWave();
	int count = 0;

	// implement the "static create()" method manually
	CREATE_FUNC(Level1);

	void menuCloseCallback(cocos2d::Ref* pSender);
	void setViewPointCenter(cocos2d::Point position);
	// Tower
	void addTower(Point pos, std::string towerType);
	Point tileCoordForPosition(Point position);
	bool canBuildOnTilePosition(Point pos);
	Point boundLayerPos(Point newPos);
	int getCount() { return count; };
	void setCount(int c) { count = c; };
	int getSCount() { return count; };
	void setSCount(int s) { count = s; };

	void youWon(int finalScore, int finalCoins);

	Point position;
	GameHUD *gameHUD;

	// void onEnter();
	// void onExit();

private:

	TMXTiledMap *_tileMap;
	TMXLayer *_background;
	TMXLayer *_Sources;
	TMXLayer *_Quicksand;
	TMXLayer *_walls;
	TMXLayer *_turrets;
	TMXLayer *_buildable;
	Sprite *_enemyUnit1;
	cocos2d::Label *scoreLabel;
	GameHUD *_hud;
	int _numCollected = 5;
	int _scCollected = 0;
};

#endif