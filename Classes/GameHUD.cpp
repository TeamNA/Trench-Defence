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

	_label = new CCLabelTTF();
	_label->initWithString("5", "Verdana-Bold", 18.0);
	_label->setColor(ccc3(0, 0, 0));

	_label2 = new CCLabelTTF();
	_label2->initWithString("0", "Verdana-Bold", 18.0);
	_label2->setColor(ccc3(0, 0, 0));

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
	images.pushBack(StringMake("MachineGun.png"));
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
		sprite->setPosition(Vec2(winSize.width*(offsetFraction / 2), visibleSize.height*(0.11) + origin.y));
		sprite->setContentSize(Size(50, 50));
		sprite->setName(image->getCString());
		this->addChild(sprite);
		movableSprites.pushBack(sprite);
	}

	// Add the coins label to the hud and set its posiion
	LabelTTF* ttf1 = LabelTTF::create("COINS = ", "ARMYRUST", 18,
		CCSizeMake(245, 32), kCCTextAlignmentCenter);
	LabelTTF* ttf2 = LabelTTF::create("SCORE = ", "ARMYRUST", 18,
		CCSizeMake(245, 32), kCCTextAlignmentCenter);


	//scoreLabel = Label::create(tempscore->getCString(), "Helvetica", 12,
	//CCSizeMake(245, 32), kCCTextAlignmentCenter);

	ttf1->setPosition(Vec2(winSize.width - 90, visibleSize.height*(0.08) + origin.y));
	ttf1->setColor(ccc3(0, 0, 0));
	_label->setPosition(Vec2(winSize.width - 50, visibleSize.height*(0.10) + origin.y));

	ttf2->setPosition(Vec2(winSize.width - 185, visibleSize.height*(0.08) + origin.y));
	ttf2->setColor(ccc3(0, 0, 0));
	_label2->setPosition(Vec2(winSize.width - 140, visibleSize.height*(0.10) + origin.y));
	//scoreLabel->setColor(ccc3(0, 0, 0));

	this->addChild(ttf1);
	this->addChild(ttf2);
	this->addChild(_label);
	this->addChild(_label2);

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

void GameHUD::numCollectedChanged(int numCollected)
{
	// This updates the number of coins collects on the hud
	String *labelCollected = new String();
	labelCollected->initWithFormat("%d", numCollected);
	_label->setString(labelCollected->getCString());
}

void GameHUD::scCollectedChanged(int scCollected)
{
	// This updates the score on the hud
	String *scoreCollected = new String();
	scoreCollected->initWithFormat("%d", scCollected);
	_label2->setString(scoreCollected->getCString());
}