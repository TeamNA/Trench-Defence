#ifndef __HISTORY_THIRD_H__
#define __HISTORY_THIRD_H__

#include "cocos2d.h"

class HistoryThird : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onEnter();
	void finishSplash(float dt);
	void settingsButtonPressed();
	void startButtonPressed();
	void rankButtonPressed();
	void NextButtonPressed();
	void BackButtonPressed();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HistoryThird);
};

#endif // __HISTORY_SCENE_