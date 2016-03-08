#include "ui/CocosGUI.h"
#include <iostream>
#include "StartMenuScene.h"
#include "Level1Scene.h"
#include "Level1Victory.h"
#include "SimpleAudioEngine.h"
#include "DataModel.h"

USING_NS_CC;

int finalLevel1Score;

Scene* Level1Victory::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Level1Victory::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Level1Victory::init()
{
	DataModel *m = DataModel::getModel();

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	finalLevel1Score = m->finalScore;
	//MachineGunTower::tower()->towersAvailable;


	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Level1Victory::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	/////////////////////////////
	// 3. add your codes below...

	// add "TeamNA" splash screen" with logo
	auto sprite = Sprite::create("LEVEL1VICTORY.png");
	// set the anchor point to the middle
	// Bottom Left (0,0), Top Right (1,1)
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	float scale = MIN(visibleSize.width / sprite->getContentSize().width, visibleSize.height / sprite->getContentSize().height);
	sprite->setScale(scale);

	// add the sprite as a child to this layer
	//    this->addChild(sprite, 1);


	// add the sprite as a child to this layer
	//this->addChild(sprite, 0);

	//Add a Settings Button
	ui::Button* settingsBtn = ui::Button::create("MainMenu.png");
	settingsBtn->setPosition(Vec2(visibleSize.width * 0.87 + origin.x, visibleSize.height*0.195 + origin.y));
	settingsBtn->setScale(0.8f);
	settingsBtn->setTitleText(" ");
	settingsBtn->setTitleFontSize(80);
	settingsBtn->setColor(Color3B(159, 168, 176));
	settingsBtn->addTouchEventListener(CC_CALLBACK_0(Level1Victory::startButtonPressed, this));
	this->addChild(settingsBtn, 1);
	// add the sprite as a child to this layer
	this->addChild(sprite, -2);


	// Final Score labels
	_finalScoreLabel = new CCLabelTTF();
	_finalScoreLabel->initWithString("5", "Verdana-Bold", 26.0);
	_finalScoreLabel->setColor(ccc3(0, 0, 0));
	finalScoreInit(finalLevel1Score);

	// Labels for the score name
	LabelTTF* finalScoreLabel_ttf1 = LabelTTF::create("Final Score: ", "ARMYRUST", 26,
		CCSizeMake(245, 32), kCCTextAlignmentLeft);
	finalScoreLabel_ttf1->setPosition(Vec2((visibleSize.width / 2) + origin.x + 50, visibleSize.height*(0.2) + origin.y));
	finalScoreLabel_ttf1->setColor(ccc3(0, 0, 0));

	_finalScoreLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x + 100, visibleSize.height*(0.2) + origin.y));

	this->addChild(finalScoreLabel_ttf1);

	this->addChild(_finalScoreLabel);

	return true;

}
void Level1Victory::finalScoreInit(int finalScore)
{
	// This updates the number of coins collects on the hud
	String *labelFinalScore = new String();
	labelFinalScore->initWithFormat("%d", finalScore);
	_finalScoreLabel->setString(labelFinalScore->getCString());
}
void Level1Victory::onEnter() {
	CCLayer::onEnter();
	// CCLog("onEnter");
	printf("onEnter");
	//this->scheduleOnce(schedule_selector(Level1Victory::finishSplash), 1.0f);
}
void Level1Victory::finishSplash(float dt) {
	// CCDirector::sharedDirector()->replaceScene(StartMenu::scene());
	auto Level1Victory = Level1Victory::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, Level1Victory));
}

void Level1Victory::continueLevel2ButtonPressed()
{
	// ***** NB Change to level 2 when ready
	// get level2 scene and run it 
	auto loadLevel2 = StartMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, loadLevel2));
}

void Level1Victory::startButtonPressed()
{
	// get startMenu scene and run it
	auto loadStartMenu = StartMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, loadStartMenu));
}
void Level1Victory::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}