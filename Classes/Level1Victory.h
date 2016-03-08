#ifndef __VICTORY_SCENE_H__
#define __VICTORY_SCENE_H__

#include "cocos2d.h"

class Level1Victory : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onEnter();
	void finishSplash(float dt);
	void continueLevel2ButtonPressed();
	void MenuButtonPressed();
	void startButtonPressed();
	void settingsButtonPressed();
	void finalScoreInit(int finalScore);
	void highScoreInit(int highScore);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Level1Victory);

private:
	cocos2d::Label *finalScoreLabel;
	LabelTTF *_finalScoreLabel;
	LabelTTF *_highScoreLabel;

};

#endif // __VICTORY_SCENE_H__

