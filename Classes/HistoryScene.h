#ifndef __HISTORY_SCENE_H__
#define __HISTORY_SCENE_H__

#include "cocos2d.h"

class HistoryScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onEnter();
	void finishSplash(float dt);
	void NextButtonPressed();
	void BackButtonPressed();
	void MenuButtonPressed();
	void startButtonPressed();
	void settingsButtonPressed();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HistoryScene);
};

#endif // __HISTORY_SCENE_H__