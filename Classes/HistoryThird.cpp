#include "ui/CocosGUI.h"
#include <iostream>
#include "StartMenuScene.h"
#include "Level1Scene.h"
#include "HistoryThird.h"
#include "HistorySecond.h"
#include "HistoryThird.h"
#include "SimpleAudioEngine.h"
#include "DataModel.h"

USING_NS_CC;

Scene* HistoryThird::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HistoryThird::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HistoryThird::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HistoryThird::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	/////////////////////////////
	// 3. add your codes below...

	// add "TeamNA" splash screen" with logo
	auto sprite = Sprite::create("History3.png");
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

	// Add a button to start
	// Add a button to start
	ui::Button* startBtn = ui::Button::create("Next.png");
	startBtn->setPosition(Vec2(visibleSize.width / 1.37 + origin.x, visibleSize.height*0.325 + origin.y));
	startBtn->setScale(0.3f);
	startBtn->setTitleText(" ");
	startBtn->setTitleFontSize(80);
	startBtn->setColor(Color3B(159, 168, 176));
	startBtn->addTouchEventListener(CC_CALLBACK_0(HistoryThird::NextButtonPressed, this));
	this->addChild(startBtn, 1);

	//Add a Rankings Button
	ui::Button* rankBtn = ui::Button::create("Back.png");
	rankBtn->setPosition(Vec2(visibleSize.width / 1.37 + origin.x, visibleSize.height*0.265 + origin.y));
	rankBtn->setScale(0.3f);
	rankBtn->setTitleText(" ");
	rankBtn->setTitleFontSize(80);
	rankBtn->setColor(Color3B(159, 168, 176));
	rankBtn->addTouchEventListener(CC_CALLBACK_0(HistoryThird::BackButtonPressed, this));
	this->addChild(rankBtn, 1);

	//Add a Settings Button
	ui::Button* settingsBtn = ui::Button::create("MainMenu.png");
	settingsBtn->setPosition(Vec2(visibleSize.width / 1.37 + origin.x, visibleSize.height*0.195 + origin.y));
	settingsBtn->setScale(0.3f);
	settingsBtn->setTitleText(" ");
	settingsBtn->setTitleFontSize(80);
	settingsBtn->setColor(Color3B(159, 168, 176));
	settingsBtn->addTouchEventListener(CC_CALLBACK_0(HistoryThird::startButtonPressed, this));
	this->addChild(settingsBtn, 1);

	// add the sprite as a child to this layer
	this->addChild(sprite, -2);

	return true;

	DataModel *m = DataModel::getModel();


}
void HistoryThird::onEnter() {
	CCLayer::onEnter();
	// CCLog("onEnter");
	printf("onEnter");
	//this->scheduleOnce(schedule_selector(HistoryThird::finishSplash), 1.0f);
}
void HistoryThird::NextButtonPressed()
{
	// get startMenu scene and run it
	auto loadHistoryThird = HistoryThird::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, loadHistoryThird));
}
void HistoryThird::BackButtonPressed()
{
	// get startMenu scene and run it
	auto loadHistorySecond = HistorySecond::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, loadHistorySecond));
}
void HistoryThird::startButtonPressed()
{
	// get startMenu scene and run it
	auto loadStartMenu = StartMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, loadStartMenu));
}
void HistoryThird::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}