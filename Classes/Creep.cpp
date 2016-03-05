#include "Creep.h"
#include "WayPoint.h"
#include "DataModel.h"
#include "StartMenuScene.h"

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
	creep->sprite = Sprite::create("invisible.png");

	// Create a Vector of Sprite frames to make an animation
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(8);
	animFrames.pushBack(SpriteFrame::create("EnSoldier03.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("EnSoldier02.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("EnSoldier01.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("EnSoldier02.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("EnSoldier03.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("EnSoldier04.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("EnSoldier03.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("EnSoldier02.png", Rect(0, 0, 65, 81)));

	// create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);

	// run it and repeat it forever
	creep->runAction(RepeatForever::create(animate));
	//rotate
	auto rotateTo = RotateTo::create(4.0f, 80.0f);

	creep->runAction(rotateTo);

	// Rotates a Node clockwise by 40 degree over 2 seconds
	auto rotateBy = RotateBy::create(2.0f, 40.0f);
	creep->runAction(rotateBy);

	//fade in
	auto fadeIn = FadeIn::create(5.0f);

	// Tints a node to the specified RGB values
	auto tintTo = TintTo::create(2.0f, 120.0f, 232.0f, 254.0f);
	creep->runAction(tintTo);

	// Tints a node BY the delta of the specified RGB values.
	auto tintBy = TintBy::create(2.0f, 122.0f, 121.0f, 101.0f);
	creep->runAction(tintBy);
	creep->runAction(fadeIn);

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
	creep->sprite = Sprite::create("invisible2.png");

	// Create a vector of sprite frames to make an animation from
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(12);
	animFrames.reserve(8);
	animFrames.pushBack(SpriteFrame::create("Dog1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Dog2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Dog3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Dog4.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Dog5.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Dog4.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Dog3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Dog2.png", Rect(0, 0, 65, 81)));
	// create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	// run it and repeat it forever
	creep->runAction(RepeatForever::create(animate));

	//rotate
	auto rotateTo = RotateTo::create(3.0f, 80.0f);
	creep->runAction(rotateTo);
	// Rotates a Node clockwise by 40 degree over 2 seconds
	auto rotateBy = RotateBy::create(2.0f, 40.0f);
	creep->runAction(rotateBy);

	//fade in
	auto fadeIn = FadeIn::create(5.0f);

	// Tints a node to the specified RGB values
	auto tintTo = TintTo::create(2.0f, 120.0f, 232.0f, 254.0f);
	creep->runAction(tintTo);

	// Tints a node BY the delta of the specified RGB values.
	auto tintBy = TintBy::create(2.0f, 122.0f, 121.0f, 101.0f);
	creep->runAction(tintBy);
	creep->runAction(fadeIn);
	creep->setScale(0.3);
	creep->addChild(creep->sprite, 0);
	creep->curHp = 30;
	creep->moveDuration = 3;
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
	// ** NB change the number here depending on the number of waypoints on the TMX map
	if (this->curWaypoint != 24)
	{
		this->curWaypoint++;
	}

	else
	{
		// If we wanted to loop the waypoint movement we would uncommment this
		// this->curWaypoint = 0;
	}

	// If enemy hits base... you LOSE
	if (this->curWaypoint == 24)
	{
		/*auto loseLabel = Label::createWithTTF("label test", "fonts/Marker Felt.ttf", 32);
		loseLabel->setPosition(Point(size.width / 2, size.height*0.6));
		this->addChild(loseLabel);*/
		auto loadMenu = StartMenu::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(2, loadMenu));
	}


	CCLOG("%d", this->curWaypoint); // For testing.

	WayPoint *waypoint = (WayPoint *)m->waypoints.at(curWaypoint);
	return waypoint;
}