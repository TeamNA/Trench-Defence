// #include "base/CCValue.h"
#include "Level1Scene.h"
#include "Level1Victory.h"
#include "StartMenuScene.h"
#include "Tower.h" // We will deal with it later.
#include "DataModel.h"
#include <Vector>
#include <string>
#include "SimpleAudioEngine.h"

USING_NS_CC;

int totalCreepsLeft = 100;
int totalScoreOnWin = 0;

// float machineGunProjectileDamage = MachineGunProjectile::projectile()->projectileDamage;
/*int machineGunTowerCost = MachineGunTower::tower()->towerCost;
int fastMachineGunTowerCost = FastMachineGunTower::tower()->towerCost;
int missleTowerCost = MissleGunTower::tower()->towerCost;*/
int machineGunTowerCost;
int fastMachineGunTowerCost;
int missleTowerCost;
int totalMachineGunTowersAvailable;
int totalFastMachineGunTowersAvailable;
int totalMissleTowersAvailable;

Size visibleSize = Director::getInstance()->getVisibleSize();
Vec2 origin = Director::getInstance()->getVisibleOrigin();

Size winSize = CCDirector::getInstance()->getWinSize();

UserDefault *def = UserDefault::getInstance();

Scene* Level1::createScene()
{
	// 'Level1Scene' is an autorelease object
	auto Level1Scene = Scene::create();

	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("TrenchWarLoop1.wav", true);

	CCLOG("Total creeps count = %d", totalCreepsLeft);

	// 'layer' is an autorelease object
	auto layer = Level1::create();

	// add layer as a child to scene
	// Level1Scene->addChild(layer);

	// Add the HUD to the main game
	// auto myGameHUD = GameHUD::shareHUD();
	GameHUD *hud = new GameHUD;
	hud->init();

	// add gameHUD
	// Level1Scene->addChild(myGameHUD, 3);

	// Add the HUD to the main game
	// auto myGameHUD = GameHUD::shareHUD();

	Level1Scene->addChild(layer);
	Level1Scene->addChild(hud);
	// Level1Scene->addChild(myGameHud);

	DataModel *m = DataModel::getModel();
	m->_gameLayer = layer; // add this
	layer->_hud = hud;

	// return the scene
	return Level1Scene;
}

Level1::~Level1()
{
	/*DataModel *m = DataModel::getModel();
	// turretBases->release();
	m->waypoints.clear();
	m->targets.clear();
	m->waves.clear();
	m->towers.clear();    // We will deal with it later.
	m->projectiles.clear();  // We will deal with it later.*/

}

// on "init" you need to initialize your instance
bool Level1::init()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true; };
	listener->onTouchEnded = CC_CALLBACK_2(Level1::onTouchEnded, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	machineGunTowerCost = MachineGunTower::tower()->towerCost;
	fastMachineGunTowerCost = FastMachineGunTower::tower()->towerCost;
	missleTowerCost = MissleGunTower::tower()->towerCost;

	totalMachineGunTowersAvailable = MachineGunTower::tower()->towersAvailable;
	totalFastMachineGunTowersAvailable = FastMachineGunTower::tower()->towersAvailable;
	totalMissleTowersAvailable = MissleGunTower::tower()->towersAvailable;

	// updateAvailableTowers(5, 3, 2);

	// Add the TMX map
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("md_roomy_map1.tmx");
	// set position to middle of the screen
	// _tileMap->setPosition(Point(visibleSize.width*(0.2) + origin.x, visibleSize.height*(0.2) + origin.y));
	// set size of tilemap
	// _tileMap->setScale(visibleSize.width / 220 , visibleSize.height / 220);
	// Add the background
	_background = _tileMap->layerNamed("Background");
	_Sources = _tileMap->layerNamed("Sources");
	_Quicksand = _tileMap->layerNamed("Quicksand");

	this->addChild(_tileMap, -1);


	//////////////////////////////
	// 2. Make Enemy Spawn 
	TMXObjectGroup *objects = _tileMap->getObjectGroup("Enemy");
	CCASSERT(NULL != objects, "'Enemy' enemy spawn point not found.");
	auto enemySpawnPoint = objects->getObject("EnemySpawnPoint");
	CCASSERT(!enemySpawnPoint.empty(), "EnemySpawnPoint object not found.");

	int x = enemySpawnPoint["x"].asInt();
	int y = enemySpawnPoint["y"].asInt();


	/////////////////////////////
	// 4. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Level1::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	this->addWayPoint();
	this->addWaves();
	this->scheduleUpdate();
	this->schedule(schedule_selector(Level1::gameLogic), 1.0f);
	this->currentLevel = 0;

	// setViewPointCenter(_tileMap->getPositionX);

	//bestScoreUpdate();

	return true;
}

/*void Level1::updateAvailableTowers(int totalMachineGunTowers, int totalFastMachineGunTowers, int totalMissleTowers) {
totalMachineGunTowersAvailable = totalMachineGunTowers;
totalFastMachineGunTowersAvailable = totalFastMachineGunTowers;
totalMissleTowersAvailable = totalMissleTowers;
}*/

void Level1::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Level1::setViewPointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	auto actualPosition = Point(x, y);

	auto centerOfView = Point(winSize.width*0.6, winSize.height*0.75);
	auto viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}

// Here we read the value from the class ‘creep’. 
// And we make the enemy move. 
void Level1::FollowPath(Node *sender)
{
	Creep *creep = (Creep *)sender;

	WayPoint *waypoint = creep->getNextWaypoint();

	int moveDuration = creep->moveDuration;
	auto actionMove = MoveTo::create(moveDuration, waypoint->getPosition());
	auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(Level1::FollowPath));
	creep->stopAllActions();
	creep->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}


// Here, we set the parameters for the class ‘Wave’ 
// about the creep type, spawn rate and the number of the creep.
void Level1::addWaves()
{
	DataModel *m = DataModel::getModel();

	Wave *wave = NULL;

	// Create a wave of 75 Fast red creeps with a spawn rate of 0.7 seconds
	wave = Wave::create()->initWithCreep(FastRedCreep::creep(), 0.7, 1000000);
	m->waves.pushBack(wave);
	wave = NULL;

	// Create a wave of 10 Strong GreenCreeps and spawn them every 2 seconds
	wave = Wave::create()->initWithCreep(StrongGreenCreep::creep(), 2.0, 30);
	m->waves.pushBack(wave);
	wave = NULL;
}



void Level1::addWayPoint()
{
	DataModel *m = DataModel::getModel();
	auto *objects = this->_tileMap->objectGroupNamed("WayPointList");
	WayPoint *wp = NULL;

	std::string stringWithFormat = "Waypoint";
	int wayPointCounter = 0;
	ValueMap wayPoint;
	wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));

	while (wayPoint.begin() != wayPoint.end())
	{
		int x = wayPoint.at("x").asInt();
		int y = wayPoint.at("y").asInt();
		wp = WayPoint::create();
		wp->setPosition(Vec2(x, y));
		m->waypoints.pushBack(wp);
		wayPointCounter++;
		wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));
	}
	wp = NULL;
}

void Level1::addTarget()
{
	DataModel *m = DataModel::getModel();
	Wave *wave = this->getCurrentWave();

	if (wave->totalCreeps < 0)
	{
		return;
	}
	wave->totalCreeps--;

	Creep *target = NULL;
	int random = CCRANDOM_0_1() * 2;
	if (random == 0)
	{
		target = FastRedCreep::creep();
	}
	else
	{
		target = StrongGreenCreep::creep();
	}

	WayPoint *waypoint = target->getCurrentWaypoint();
	target->setPosition(waypoint->getPosition());
	waypoint = target->getNextWaypoint();
	this->addChild(target, 1);

	int moveDuration = target->moveDuration;
	auto actionMove = CCMoveTo::create(moveDuration, waypoint->getPosition());
	auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(Level1::FollowPath));

	target->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	target->tag = 1;
	m->targets.pushBack(target);
}

void Level1::gameLogic(float dt)
{
	DataModel *m = DataModel::getModel();
	Wave *wave = this->getCurrentWave();
	static double lastTimeTargetAdded = 0;

	double now = 0;
	if (lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= wave->spawnRate)
	{
		this->addTarget();
		lastTimeTargetAdded = now;
	}
}

Wave *Level1::getCurrentWave()
{
	DataModel *m = DataModel::getModel();
	Wave *wave = (Wave *)m->waves.at(this->currentLevel);

	return wave;
}

Wave *Level1::getNextWave()
{
	DataModel *m = DataModel::getModel();

	this->currentLevel++;
	// why does this revert to level 0?
	if (this->currentLevel > 1)
	{
		this->currentLevel = 0;
	}

	Wave *wave = (Wave *)m->waves.at(this->currentLevel);

	return wave;
}

Point Level1::tileCoordForPosition(Point position)
{
	int x = position.x / this->_tileMap->getTileSize().width;
	int y = ((this->_tileMap->getMapSize().height * this->_tileMap->getTileSize().height) - position.y) / this->_tileMap->getTileSize().height;
	return Point(x, y);
}

bool Level1::canBuildOnTilePosition(Point pos)
{
	Point towerLoc = this->tileCoordForPosition(pos);
	int tileGid = this->_background->getTileGIDAt(towerLoc);
	Value props = this->_tileMap->getPropertiesForGID(tileGid);

	// MD
	if (props.isNull())   // NULL check
	{
		return true;
	}
	ValueMap map = props.asValueMap();
	bool buildable = true;
	if (map.size() != 0)
	{

		buildable = map.at("buildable").asBool();
	}

	return buildable;
}

void Level1::addTower(Point pos, std::string towerType)
{
	DataModel *m = DataModel::getModel();

	//_numCollected = 5;
	Tower *target = NULL;
	Point towerLoc = this->tileCoordForPosition(pos);
	bool buildable = canBuildOnTilePosition(pos);
	// If the terrain is buildable, AND you have more coins than the cost of the machine gun(5 coins)...
	if ((buildable && _numCollected >= machineGunTowerCost)) {
		// Point towerLoc = this->tileCoordForPosition(pos);
		towerType = towerType.substr(0, 2);
		CCLOG("TowerType is: %s", towerType.c_str());
		// If the tower that's been selected returns the machine gun string...
		if (towerType == "MachineGunTower" || towerType == "Ma") {
			// And if the number of available towers isn't 0 then add the tower and decrement the total number
			if (totalMachineGunTowersAvailable > 0) {
				// Decrement the total number of missle towers available
				totalMachineGunTowersAvailable--;
				// Update the available missle towers on the hud
				_hud->machineGunsAVAILABLEInit(totalMachineGunTowersAvailable);
				// Take away the cost from the total coins and update the hud
				_numCollected = _numCollected - machineGunTowerCost;
				_hud->numCoinsCollectedChanged(_numCollected);
				_hud->scoreCollectedChanged(_scCollected);
				target = MachineGunTower::tower();
				target->setPosition(Vec2((towerLoc.x * 20) + 10, this->_tileMap->getContentSize().height - (towerLoc.y * 20) + 150));
				this->addChild(target, 1);
				target->setTag(1);
				m->towers.pushBack(target);
			}
		}
		// If the terrain is buildable, AND you have more coins than the cost of the fast machine gun(8 coins)...
		if ((buildable && _numCollected >= fastMachineGunTowerCost)) {
			// If the tower that's been selected returns the fast machine gun string...
			if (towerType == "FastMachineGunTower" || towerType == "Fa") {
				// And if the number of available towers isn't 0 then add the tower and decrement the total number
				if (totalFastMachineGunTowersAvailable > 0) {
					// Decrement the total number of missle towers available
					totalFastMachineGunTowersAvailable--;
					// Update the available missle towers on the hud
					_hud->fastMachineGunsAVAILABLEInit(totalFastMachineGunTowersAvailable);
					// Take away the cost from the total coins and update the hud
					_numCollected = _numCollected - fastMachineGunTowerCost;
					_hud->numCoinsCollectedChanged(_numCollected);
					_hud->scoreCollectedChanged(_scCollected);
					target = FastMachineGunTower::tower();
					target->setPosition(Vec2((towerLoc.x * 20) + 10, this->_tileMap->getContentSize().height - (towerLoc.y * 20) + 150));
					this->addChild(target, 1);
					target->setTag(1);
					m->towers.pushBack(target);
				}
			}
		}
		// If the terrain is buildable, AND you have more coins than the cost of the missle tower(10 coins)...
		if ((buildable && _numCollected >= missleTowerCost)) {
			// If the tower that's been selected returns the missle tower string...
			if (towerType == "MissleGunTower" || towerType == "Mi") {
				// And if the number of available towers isn't 0 then add the tower
				if (totalMissleTowersAvailable > 0) {
					// Decrement the total number of missle towers available
					totalMissleTowersAvailable--;
					// Update the available missle towers on the hud
					_hud->misslesAVAILABLEInit(totalMissleTowersAvailable);
					// Take away the cost from the total coins and update the hud
					_numCollected = _numCollected - missleTowerCost;
					_hud->numCoinsCollectedChanged(_numCollected);
					_hud->scoreCollectedChanged(_scCollected);
					target = MissleGunTower::tower();
					target->setPosition(Vec2((towerLoc.x * 20) + 10, this->_tileMap->getContentSize().height - (towerLoc.y * 20) + 150));
					this->addChild(target, 1);
					target->setTag(1);
					m->towers.pushBack(target);
				}
			}
		}

		else {
			return;
		}
	}
	else
	{
		log("Tile Not Buildable");
	}

}

Point Level1::boundLayerPos(Point newPos)
{
	Size winSize = CCDirector::getInstance()->getWinSize();
	Point retval = newPos;
	retval.x = MIN(retval.x, 0);
	retval.x = MAX(retval.x, _tileMap->getContentSize().width + winSize.width);
	retval.y = MIN(0, retval.y);
	retval.y = MAX(_tileMap->getContentSize().height + winSize.height, retval.y);
	return retval;
}

void Level1::update(float dt) {

	// Vector<MachineGunProjectile*> machineGunProjectilesToDelete;
	// Vector<FastMachineGunProjectile*> fastMachineGunProjectilesToDelete;
	// Vector<MissleProjectile*> missleProjectilesToDelete;
	//Level1 *l = ;

	int c = 0;
	int s = 0;

	DataModel *m = DataModel::getModel();
	// _hud->machineGunATKInit(machineGunProjectileDamage);
	Vector<Projectile*> projectileToDelete;
	for (int i = 0; i < m->projectiles.size(); ++i)
	{
		auto projectile = m->projectiles.at(i);
		auto projectileSprite = projectile->projectileSprite;
		Rect projectileRect = Rect(projectile->getPositionX() - (projectile->getContentSize().width),
			projectile->getPositionY() - (projectile->getContentSize().height),
			projectile->getContentSize().width,
			projectile->getContentSize().height);
		Vector<Creep *> targetsToDelete;
		for each (Creep* target in m->targets)
		{
			Rect targetRect = Rect(target->getPositionX() - (target->getContentSize().width),
				target->getPositionY() - (target->getContentSize().height),
				target->getContentSize().width,
				target->getContentSize().height);
			if (projectileRect.intersectsRect(targetRect))
			{
				// CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(("sound/" + target->hurtSound).c_str());
				// projectile->runHitAnimation(target);
				projectileToDelete.pushBack(projectile);
				Creep *creep = target;

				// Take projectile damage from the creeps health
				CCLOG("Creeps current health is: %f", creep->curHp);
				creep->curHp -= projectile->projectileDamage;
				CCLOG("Creeps health after projectile damage of %f is: %f", projectile->projectileDamage, creep->curHp);

				if (creep->curHp <= 0)
				{
					creep->curHp = 0;
					targetsToDelete.pushBack(creep);
				}
				break;
			}
		}
		// for (auto target : targetsToDelete)
		for (int i = 0; i < targetsToDelete.size(); ++i)
		{
			Creep* target = (Creep*)(targetsToDelete.at(i));

			totalCreepsLeft--;

			m->targets.eraseObject(target);
			this->removeChild(target, true);

			//count++;
			_scCollected += 10;
			_hud->scoreCollectedChanged(_scCollected);
			_numCollected++;
			_hud->numCoinsCollectedChanged(_numCollected);
			_hud->coinsForGamehud(_numCollected);

			// If you've killed all the creeps, change scene
			if (totalCreepsLeft <= 0)
			{
				
				totalCreepsLeft = 100;
				//addWaves();
				log("HIGHSCORE = %d", def->getIntegerForKey("BOOM"));

				
				youWon(_scCollected, _numCollected);
;
				
			}

			//CCLOG("COIN = %i", count);
		}

	}
	for (auto projectile : projectileToDelete)
	{
		m->projectiles.eraseObject(projectile);
		this->removeChild(projectile, true);

	}


}

void Level1::youWon(int finalScore, int finalCoins)
{

	DataModel *m = DataModel::getModel();

	totalScoreOnWin = finalScore + (finalCoins * 10);
	m->finalScore = totalScoreOnWin;

	CCLabelTTF* youWon_ttf1 = CCLabelTTF::create("YOU HAVE WON", "Helvetica", 32,
	CCSizeMake(245, 32), kCCTextAlignmentCenter);
	youWon_ttf1->setPosition(Vec2(265, visibleSize.height*(0.6) + origin.y));

	//def->setIntegerForKey("BOOM", 0);

	if (def->getIntegerForKey("BOOM") < totalScoreOnWin)
	{

		def->setIntegerForKey("BOOM", totalScoreOnWin);

		def->flush();

	}

	//m->_gameLayer->addChild(youWon_ttf1);
	/**
	int best = UserDefault::getInstance()->getIntegerForKey("Best_Score");
	

	if (best < _scCollected)
	{
		best = _scCollected;

		char score[256];
		sprintf(score, "%i", best);
		UserDefault::getInstance()->setIntegerForKey("Best_Score", best);
		bestScore = LabelTTF::create(score, "Helvetica", 32,
		CCSizeMake(245, 32), kCCTextAlignmentCenter);
		bestScore->setPosition(Vec2(265, visibleSize.height*(0.6) + origin.y));
		UserDefault::getInstance()->flush();
	}
	else
	{
		char buffer[10];
		sprintf(buffer, "%i", best);
		bestScore = LabelTTF::create(buffer, "Helvetica", 32,
		CCSizeMake(245, 32), kCCTextAlignmentCenter);
		bestScore->setPosition(Vec2(265, visibleSize.height*(0.6) + origin.y));
	}*/

	//bestScore->addChild(bestScore);

	auto loadVictory = Level1Victory::createScene();
	auto loadMenu = StartMenu::createScene();

	Director::getInstance()->sharedDirector()->replaceScene(TransitionFade::create(3, loadVictory));
	//Director::getInstance()->sharedDirector()->popScene();
}


void delayProjectileDelete(float dt)
{

}


	


/*void Level1::onEnter()
{
}*/
/*void Level1::onExit()
{
/*DataModel *m = DataModel::getModel();
m->waypoints.clear();
m->targets.clear();
m->waves.clear();
m->towers.clear();    // We will deal with it later.
m->projectiles.clear();  // We will deal with it later.
//this->unscheduleAllSelectors();
// this->release();
// CCTextureCache sharedTextureCache[removeAllTextures];
}*/

//  #endif