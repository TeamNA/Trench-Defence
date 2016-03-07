#include "GameHUD.h"
#include "DataModel.h"
#include "Level1Scene.h"
// #include <vector>
// #include <string>

GameHUD* GameHUD::_sharHUD;

bool GameHUD::init()
{
	DataModel *m = DataModel::getModel();
	GameHUD* score;

	//__String *tempscore = __String::createWithFormat("%i", b);
	//	scoreLabel = Label::createWithTTF(tempscore->getCString(), "Helvetica", 12);

	if (!Layer::init())
	{
		return false;
	}

	// Get the size of the game window
	Size winSize = CCDirector::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float machineGunProjectileDamage = MachineGunProjectile::projectile()->projectileDamage;
	float fastMachineGunProjectileDamage = FastMachineGunProjectile::projectile()->projectileDamage;
	float missleProjectileDamage = MissleProjectile::projectile()->projectileDamage;

	float machineGunTowerRange = MachineGunTower::tower()->range;
	float fastMachineGunTowerRange = FastMachineGunTower::tower()->range;
	float missleTowerRange = MissleGunTower::tower()->range;

	int machineGunTowerCost = MachineGunTower::tower()->towerCost;
	int fastMachineGunTowerCost = FastMachineGunTower::tower()->towerCost;
	int missleTowerCost = MissleGunTower::tower()->towerCost;

	int totalMachineGunTowersAvailable = MachineGunTower::tower()->towersAvailable;
	int totalFastMachineGunTowersAvailable = FastMachineGunTower::tower()->towersAvailable;
	int totalMissleTowersAvailable = MissleGunTower::tower()->towersAvailable;

	CCLOG("Machine Gun Cost: %d ", machineGunTowerCost);

	// Tower Attack Labels
	_machineGunATKLabel = new CCLabelTTF();
	_machineGunATKLabel->initWithString("2", "Verdana-Bold", 6.0);
	_machineGunATKLabel->setColor(ccc3(0, 0, 0));
	machineGunATKInit(machineGunProjectileDamage);

	_fastMachineGunATKLabel = new CCLabelTTF();
	_fastMachineGunATKLabel->initWithString("5", "Verdana-Bold", 6.0);
	_fastMachineGunATKLabel->setColor(ccc3(0, 0, 0));
	fastMachineGunATKInit(fastMachineGunProjectileDamage);

	_missleATKLabel = new CCLabelTTF();
	_missleATKLabel->initWithString("5", "Verdana-Bold", 6.0);
	_missleATKLabel->setColor(ccc3(0, 0, 0));
	missleATKInit(missleProjectileDamage);

	// Tower Range Labels
	_machineGunRNGLabel = new CCLabelTTF();
	_machineGunRNGLabel->initWithString("5", "Verdana-Bold", 6.0);
	_machineGunRNGLabel->setColor(ccc3(0, 0, 0));
	machineGunRNGInit(machineGunTowerRange);

	_fastMachineGunRNGLabel = new CCLabelTTF();
	_fastMachineGunRNGLabel->initWithString("5", "Verdana-Bold", 6.0);
	_fastMachineGunRNGLabel->setColor(ccc3(0, 0, 0));
	fastMachineGunRNGInit(fastMachineGunTowerRange);

	_missleRNGLabel = new CCLabelTTF();
	_missleRNGLabel->initWithString("5", "Verdana-Bold", 6.0);
	_missleRNGLabel->setColor(ccc3(0, 0, 0));
	missleRNGInit(missleTowerRange);

	// Tower Cost Labels
	_machineGunCOSTLabel = new CCLabelTTF();
	_machineGunCOSTLabel->initWithString("5", "Verdana-Bold", 6.0);
	_machineGunCOSTLabel->setColor(ccc3(0, 0, 0));
	machineGunCOSTInit(machineGunTowerCost);

	_fastMachineGunCOSTLabel = new CCLabelTTF();
	_fastMachineGunCOSTLabel->initWithString("5", "Verdana-Bold", 6.0);
	_fastMachineGunCOSTLabel->setColor(ccc3(0, 0, 0));
	fastMachineGunCOSTInit(fastMachineGunTowerCost);

	_missleCOSTLabel = new CCLabelTTF();
	_missleCOSTLabel->initWithString("5", "Verdana-Bold", 6.0);
	_missleCOSTLabel->setColor(ccc3(0, 0, 0));
	missleCOSTInit(missleTowerCost);

	// Towers Available labels
	_machineGunsAVAILABLELabel = new CCLabelTTF();
	_machineGunsAVAILABLELabel->initWithString("5", "Verdana-Bold", 6.0);
	_machineGunsAVAILABLELabel->setColor(ccc3(0, 0, 0));
	machineGunsAVAILABLEInit(totalMachineGunTowersAvailable);

	_fastMachineGunsAVAILABLELabel = new CCLabelTTF();
	_fastMachineGunsAVAILABLELabel->initWithString("5", "Verdana-Bold", 6.0);
	_fastMachineGunsAVAILABLELabel->setColor(ccc3(0, 0, 0));
	fastMachineGunsAVAILABLEInit(totalFastMachineGunTowersAvailable);

	_misslesAVAILABLELabel = new CCLabelTTF();
	_misslesAVAILABLELabel->initWithString("5", "Verdana-Bold", 6.0);
	_misslesAVAILABLELabel->setColor(ccc3(0, 0, 0));
	misslesAVAILABLEInit(totalMissleTowersAvailable);

	// Coin label
	_coinLabel = new CCLabelTTF();
	_coinLabel->initWithString("5", "Verdana-Bold", 18.0);
	_coinLabel->setColor(ccc3(0, 0, 0));

	// Score label
	_scoreLabel = new CCLabelTTF();
	_scoreLabel->initWithString("0", "Verdana-Bold", 18.0);
	_scoreLabel->setColor(ccc3(0, 0, 0));

	// Draw the background of the game HUD
	Texture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
	background = Sprite::create("hud.png");
	background->setScaleX(2.3);
	background->setScaleY(1.95);

	// Create an anchor point at the bottom of the screen to put the hud box
	// ignoreAnchorPointForPosition(false);
	// background->setAnchorPoint(Vec2(0.5, 0.5));
	// background->setPosition(Vec2(0.5, 1));
	background->setPosition(Point(visibleSize.width*(0.28) + origin.x, visibleSize.height*(0.1) + origin.y));
	this->addChild(background);
	//CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default);


	// Create a vector of strings to take in the names of the turrets for the HUD
	Vector<String*> images;
	images.pushBack(StringMake("MachineGunTurret.png"));
	images.pushBack(StringMake("FastMachineGunTurret.png"));
	images.pushBack(StringMake("MissleGunTurret.png"));

	// For each string in the images vector, add the image to the
	// hud, increment the offset and repeat
	for (int i = 0; i < images.size(); ++i) {
		String* image = images.at(i);
		CCLOG("Placing %s turret", image->getCString());
		Sprite* sprite = Sprite::create(image->getCString());

		float offsetFraction = ((float)(i + 1)) / (images.size() + 1);
		sprite->setScale(0.6);
		sprite->setPosition(Vec2(winSize.width*(offsetFraction / 1.78), visibleSize.height*(0.105) + origin.y));
		sprite->setContentSize(Size(50, 50));
		sprite->setName(image->getCString());
		this->addChild(sprite);
		movableSprites.pushBack(sprite);
	}

	// Labels for the names of the turrets
	LabelTTF* machineGunLabel_ttf1 = LabelTTF::create("Machine Gun", "ARMYRUST", 6,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	machineGunLabel_ttf1->setPosition(Vec2(130, visibleSize.height*(0.105) + origin.y));
	machineGunLabel_ttf1->setColor(ccc3(0, 0, 0));
	LabelTTF* fastMachineGunLabel_ttf1 = LabelTTF::create("Fast Machine Gun", "ARMYRUST", 6,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	fastMachineGunLabel_ttf1->setPosition(Vec2(200, visibleSize.height*(0.105) + origin.y));
	fastMachineGunLabel_ttf1->setColor(ccc3(0, 0, 0));
	LabelTTF* missleLabel_ttf1 = LabelTTF::create("Missle Tower", "ARMYRUST", 6,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	missleLabel_ttf1->setPosition(Vec2(265, visibleSize.height*(0.105) + origin.y));
	missleLabel_ttf1->setColor(ccc3(0, 0, 0));

	// Labels for the attack stats of the turrets
	LabelTTF* machineGunATKLabel_ttf1 = LabelTTF::create("ATK: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	machineGunATKLabel_ttf1->setPosition(Vec2(130, visibleSize.height*(0.080) + origin.y));
	machineGunATKLabel_ttf1->setColor(ccc3(0, 0, 0));
	LabelTTF* fastMachineGunATKLabel_ttf1 = LabelTTF::create("ATK: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	fastMachineGunATKLabel_ttf1->setPosition(Vec2(200, visibleSize.height*(0.080) + origin.y));
	fastMachineGunATKLabel_ttf1->setColor(ccc3(0, 0, 0));
	LabelTTF* missleATKLabel_ttf1 = LabelTTF::create("ATK: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	missleATKLabel_ttf1->setPosition(Vec2(265, visibleSize.height*(0.080) + origin.y));
	missleATKLabel_ttf1->setColor(ccc3(0, 0, 0));

	// These labels contain the actual number of the ATK and change the label to show changes
	_machineGunATKLabel->setPosition(Vec2(43, visibleSize.height*(0.12) + origin.y));
	_fastMachineGunATKLabel->setPosition(Vec2(112, visibleSize.height*(0.12) + origin.y));
	_missleATKLabel->setPosition(Vec2(180, visibleSize.height*(0.12) + origin.y));

	// Labels for the range stats of the turrets
	LabelTTF* machineGunRNGLabel_ttf1 = LabelTTF::create("RANGE: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	machineGunRNGLabel_ttf1->setPosition(Vec2(130, visibleSize.height*(0.060) + origin.y));
	machineGunRNGLabel_ttf1->setColor(ccc3(0, 0, 0));
	LabelTTF* fastMachineGunRNGLabel_ttf1 = LabelTTF::create("RANGE: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	fastMachineGunRNGLabel_ttf1->setPosition(Vec2(200, visibleSize.height*(0.060) + origin.y));
	fastMachineGunRNGLabel_ttf1->setColor(ccc3(0, 0, 0));
	LabelTTF* missleRNGLabel_ttf1 = LabelTTF::create("RANGE: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	missleRNGLabel_ttf1->setPosition(Vec2(265, visibleSize.height*(0.060) + origin.y));
	missleRNGLabel_ttf1->setColor(ccc3(0, 0, 0));

	// These labels contain the actual number of the RNG and change the label to show changes
	_machineGunRNGLabel->setPosition(Vec2(40, visibleSize.height*(0.10) + origin.y));
	_fastMachineGunRNGLabel->setPosition(Vec2(110, visibleSize.height*(0.10) + origin.y));
	_missleRNGLabel->setPosition(Vec2(176, visibleSize.height*(0.10) + origin.y));

	// Labels for the cost stats of the turrets
	LabelTTF* machineGunCOSTLabel_ttf1 = LabelTTF::create("COST: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	machineGunCOSTLabel_ttf1->setPosition(Vec2(130, visibleSize.height*(0.040) + origin.y));
	machineGunCOSTLabel_ttf1->setColor(ccc3(0, 0, 0));
	LabelTTF* fastMachineGunCOSTLabel_ttf1 = LabelTTF::create("COST: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	fastMachineGunCOSTLabel_ttf1->setPosition(Vec2(200, visibleSize.height*(0.040) + origin.y));
	fastMachineGunCOSTLabel_ttf1->setColor(ccc3(0, 0, 0));
	LabelTTF* missleCOSTLabel_ttf1 = LabelTTF::create("COST: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	missleCOSTLabel_ttf1->setPosition(Vec2(265, visibleSize.height*(0.040) + origin.y));
	missleCOSTLabel_ttf1->setColor(ccc3(0, 0, 0));

	// These labels contain the actual number of the COST and change the label to show changes
	_machineGunCOSTLabel->setPosition(Vec2(45, visibleSize.height*(0.08) + origin.y));
	_fastMachineGunCOSTLabel->setPosition(Vec2(115, visibleSize.height*(0.08) + origin.y));
	_missleCOSTLabel->setPosition(Vec2(180, visibleSize.height*(0.08) + origin.y));

	// Labels for the AVAILABLE stats of the turrets
	LabelTTF* machineGunsAVAILABLELabel_ttf1 = LabelTTF::create("AVAILABLE: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	machineGunsAVAILABLELabel_ttf1->setPosition(Vec2(130, visibleSize.height*(0.020) + origin.y));
	machineGunsAVAILABLELabel_ttf1->setColor(ccc3(0, 0, 0));
	LabelTTF* fastMachineGunsAVAILABLELabel_ttf1 = LabelTTF::create("AVAILABLE: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	fastMachineGunsAVAILABLELabel_ttf1->setPosition(Vec2(200, visibleSize.height*(0.020) + origin.y));
	fastMachineGunsAVAILABLELabel_ttf1->setColor(ccc3(0, 0, 0));
	LabelTTF* misslesAVAILABLELabel_ttf1 = LabelTTF::create("AVAILABLE: ", "ARMYRUST", 5,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	misslesAVAILABLELabel_ttf1->setPosition(Vec2(265, visibleSize.height*(0.020) + origin.y));
	misslesAVAILABLELabel_ttf1->setColor(ccc3(0, 0, 0));

	// These labels contain the actual number of the AVAILABLE towers and change the label to show changes
	_machineGunsAVAILABLELabel->setPosition(Vec2(45, visibleSize.height*(0.06) + origin.y));
	_fastMachineGunsAVAILABLELabel->setPosition(Vec2(115, visibleSize.height*(0.06) + origin.y));
	_misslesAVAILABLELabel->setPosition(Vec2(180, visibleSize.height*(0.06) + origin.y));

	// Add the coins label to the hud and set its posiion
	LabelTTF* coins_ttf1 = LabelTTF::create("COINS = ", "ARMYRUST", 18,
		CCSizeMake(245, 32), kCCTextAlignmentCenter);
	coins_ttf1->setPosition(Vec2(winSize.width - 80, visibleSize.height*(0.08) + origin.y));
	coins_ttf1->setColor(ccc3(0, 0, 0));
	// Add the coins label which represents the amount of coins currently owned
	_coinLabel->setPosition(Vec2(winSize.width - 30, visibleSize.height*(0.10) + origin.y));

	// Add the score label to the hud and set its position
	LabelTTF* score_ttf2 = LabelTTF::create("SCORE = ", "ARMYRUST", 18,
		CCSizeMake(245, 32), kCCTextAlignmentCenter);
	score_ttf2->setPosition(Vec2(winSize.width - 205, visibleSize.height*(0.08) + origin.y));
	score_ttf2->setColor(ccc3(0, 0, 0));
	// Add the score label which represents the amount of score currently earned
	_scoreLabel->setPosition(Vec2(winSize.width - 140, visibleSize.height*(0.10) + origin.y));
	//scoreLabel->setColor(ccc3(0, 0, 0));
	

	this->addChild(machineGunLabel_ttf1);
	this->addChild(fastMachineGunLabel_ttf1);
	this->addChild(missleLabel_ttf1);
	this->addChild(machineGunATKLabel_ttf1);
	this->addChild(fastMachineGunATKLabel_ttf1);
	this->addChild(missleATKLabel_ttf1);
	this->addChild(machineGunRNGLabel_ttf1);
	this->addChild(fastMachineGunRNGLabel_ttf1);
	this->addChild(missleRNGLabel_ttf1);
	this->addChild(machineGunCOSTLabel_ttf1);
	this->addChild(fastMachineGunCOSTLabel_ttf1);
	this->addChild(missleCOSTLabel_ttf1);
	this->addChild(machineGunsAVAILABLELabel_ttf1);
	this->addChild(fastMachineGunsAVAILABLELabel_ttf1);
	this->addChild(misslesAVAILABLELabel_ttf1);

	this->addChild(_machineGunATKLabel);
	this->addChild(_fastMachineGunATKLabel);
	this->addChild(_missleATKLabel);
	this->addChild(_machineGunRNGLabel);
	this->addChild(_fastMachineGunRNGLabel);
	this->addChild(_missleRNGLabel);
	this->addChild(_machineGunCOSTLabel);
	this->addChild(_fastMachineGunCOSTLabel);
	this->addChild(_missleCOSTLabel);
	this->addChild(_machineGunsAVAILABLELabel);
	this->addChild(_fastMachineGunsAVAILABLELabel);
	this->addChild(_misslesAVAILABLELabel);

	this->addChild(coins_ttf1);
	this->addChild(score_ttf2);
	this->addChild(_coinLabel);
	this->addChild(_scoreLabel);

	return true;
}

GameHUD* GameHUD::shareHUD()
{
	// If there isn't a _sharHUD make one
	if (_sharHUD == NULL)
	{
		_sharHUD = GameHUD::create();
	}

	return _sharHUD;
}

void GameHUD::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameHUD::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameHUD::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameHUD::onTouchEnded, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//dispatcher->addEventListenerWithFixedPriority(listener, 0);

}

bool GameHUD::onTouchBegan(Touch *touch, Event *event)
{
	Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));
	Sprite *newSprite = NULL;
	// for each(Sprite* sprite in this->movableSprites) // MD 
	for (Sprite *sprite : this->movableSprites)
		//for (int i = 0; i < movableSprites.size(); i++)  // Use this if your VC doesn’t support C++11
	{
		// Sprite* sprite = (Sprite*)(movableSprites.at(i));  // Use this if your VC doesn’t support C++11

		Rect pos_rect = Rect((sprite->getPositionX() - sprite->getContentSize().width / 2), (sprite->getPositionY() - sprite->getContentSize().height / 2), sprite->getContentSize().width, sprite->getContentSize().height);
		// This determines the area which you can drag our ‘tower’
		float xMin = pos_rect.getMinX();
		float xMax = pos_rect.getMaxX();
		float yMIn = pos_rect.getMinY();
		float yMax = pos_rect.getMaxY();
		if (pos_rect.containsPoint(touchLocation))
		{
			DataModel *m = DataModel::getModel();
			//m.gestureRecognizer.enabled = NO;
			selSpriteRange = Sprite::create("Range.png");
			selSpriteRange->setScale(0.6);
			this->addChild(selSpriteRange, -1);
			selSpriteRange->setPosition(sprite->getPosition());

			newSprite = Sprite::createWithTexture(sprite->getTexture()); //sprite;
																		 // newSprite = Sprite::createWithSpriteFrameName(sprite->getName());
			newSprite->setPosition(sprite->getPosition());
			newSprite->setScale(0.6);
			newSprite->setName(sprite->getName());
			CCLOG("Setting down %s", sprite->getName());
			selSprite = newSprite;
			this->addChild(newSprite);
		}
	}

	return true;
}

void GameHUD::onTouchMoved(Touch* touch, Event* event)
{
	Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));

	Point oldTouchLocation = touch->getPreviousLocationInView();
	oldTouchLocation = Director::getInstance()->convertToGL(oldTouchLocation);
	oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);

	Point translation = ccpSub(touchLocation, oldTouchLocation);

	if (selSprite != NULL)
	{
		Point newPos = selSprite->getPosition() + translation;
		selSprite->setPosition(newPos);
		selSpriteRange->setPosition(newPos);

		DataModel *m = DataModel::getModel();
		// Error here
		Point touchLocationInGameLayer = m->_gameLayer->convertTouchToNodeSpace(touch);

		// small bool here?
		BOOL isBuildable = m->_gameLayer->canBuildOnTilePosition(touchLocationInGameLayer);
		if (isBuildable)
		{
			selSprite->setOpacity(200);
		}
		else
		{
			selSprite->setOpacity(50);
		}
	}

	CCLOG("%s", "Reaching end of onTouchMoved");
}

void GameHUD::onTouchEnded(Touch* touch, Event* event)
{
	Point touchLocation = this->convertTouchToNodeSpace(touch);
	DataModel *m = DataModel::getModel();

	if (selSprite != NULL)
	{
		Rect backgroundRect = Rect(background->getPositionX(),
			background->getPositionY(),
			background->getContentSize().width,
			background->getContentSize().height);

		if (!backgroundRect.containsPoint(touchLocation) && m->_gameLayer->canBuildOnTilePosition(touchLocation))
		{
			Point touchLocationInGameLayer = m->_gameLayer->convertTouchToNodeSpace(touch);
			m->_gameLayer->addTower(touchLocationInGameLayer, this->selSprite->getName());
			CCLOG("Placed %s Turret.", this->selSprite->getName());
		}

		this->removeChild(this->selSprite, true);
		selSprite = NULL;
		this->removeChild(this->selSpriteRange, true);
		selSpriteRange = NULL;
	}

}

void GameHUD::machineGunATKInit(float machineGunATK)
{
	// This updates the number of coins collects on the hud
	String *labelMachineATK = new String();
	labelMachineATK->initWithFormat("%.1f", machineGunATK);
	_machineGunATKLabel->setString(labelMachineATK->getCString());
}

void GameHUD::fastMachineGunATKInit(float fastMachineGunATK)
{
	// This updates the number of coins collects on the hud
	String *labelFastMachineATK = new String();
	labelFastMachineATK->initWithFormat("%.1f", fastMachineGunATK);
	_fastMachineGunATKLabel->setString(labelFastMachineATK->getCString());
}

void GameHUD::missleATKInit(float missleATK)
{
	// This updates the number of coins collects on the hud
	String *labelMissleATK = new String();
	labelMissleATK->initWithFormat("%.1f", missleATK);
	_missleATKLabel->setString(labelMissleATK->getCString());
}

void GameHUD::machineGunRNGInit(float machineGunRNG)
{
	// This updates the number of coins collects on the hud
	String *labelMachineRNG = new String();
	labelMachineRNG->initWithFormat("%.1f", machineGunRNG);
	_machineGunRNGLabel->setString(labelMachineRNG->getCString());
}

void GameHUD::fastMachineGunRNGInit(float fastMachineGunRNG)
{
	// This updates the number of coins collects on the hud
	String *labelFastMachineRNG = new String();
	labelFastMachineRNG->initWithFormat("%.1f", fastMachineGunRNG);
	_fastMachineGunRNGLabel->setString(labelFastMachineRNG->getCString());
}

void GameHUD::missleRNGInit(float missleRNG)
{
	// This updates the number of coins collects on the hud
	String *labelMissleRNG = new String();
	labelMissleRNG->initWithFormat("%.1f", missleRNG);
	_missleRNGLabel->setString(labelMissleRNG->getCString());
}

void GameHUD::machineGunCOSTInit(int machineGunCOST)
{
	// This updates the number of coins collects on the hud
	String *labelMachineCOST = new String();
	labelMachineCOST->initWithFormat("%d", machineGunCOST);
	_machineGunCOSTLabel->setString(labelMachineCOST->getCString());
}

void GameHUD::fastMachineGunCOSTInit(int fastMachineGunCOST)
{
	// This updates the number of coins collects on the hud
	String *labelFastMachineCOST = new String();
	labelFastMachineCOST->initWithFormat("%d", fastMachineGunCOST);
	_fastMachineGunCOSTLabel->setString(labelFastMachineCOST->getCString());
}

void GameHUD::missleCOSTInit(int missleCOST)
{
	// This updates the number of coins collects on the hud
	String *labelMissleCOST = new String();
	labelMissleCOST->initWithFormat("%d", missleCOST);
	_missleCOSTLabel->setString(labelMissleCOST->getCString());
}
// AVAILABLE TOWERS UPDATES
void GameHUD::machineGunsAVAILABLEInit(int machineGunsAVAILABLE)
{
	// This updates the number of coins collects on the hud
	String *labelMachinesAVAILABLE = new String();
	labelMachinesAVAILABLE->initWithFormat("%d", machineGunsAVAILABLE);
	_machineGunsAVAILABLELabel->setString(labelMachinesAVAILABLE->getCString());
}

void GameHUD::fastMachineGunsAVAILABLEInit(int fastMachineGunsAVAILABLE)
{
	// This updates the number of coins collects on the hud
	String *labelFastMachinesAVAILABLE = new String();
	labelFastMachinesAVAILABLE->initWithFormat("%d", fastMachineGunsAVAILABLE);
	_fastMachineGunsAVAILABLELabel->setString(labelFastMachinesAVAILABLE->getCString());
}

void GameHUD::misslesAVAILABLEInit(int misslesAVAILABLE)
{
	// This updates the number of coins collects on the hud
	String *labelMisslesAVAILABLE = new String();
	labelMisslesAVAILABLE->initWithFormat("%d", misslesAVAILABLE);
	_misslesAVAILABLELabel->setString(labelMisslesAVAILABLE->getCString());
}

void GameHUD::numCoinsCollectedChanged(int numCoinsCollected)
{
	// This updates the number of coins collects on the hud
	String *labelCollected = new String();
	labelCollected->initWithFormat("%d", numCoinsCollected);
	_coinLabel->setString(labelCollected->getCString());
}

void GameHUD::scoreCollectedChanged(int scoreCollected)
{
	// This updates the score on the hud
	String *_scoreCollected = new String();
	_scoreCollected->initWithFormat("%d", scoreCollected);
	_scoreLabel->setString(_scoreCollected->getCString());
}
