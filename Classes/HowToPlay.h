#ifndef __HOWTO_PLAY_H__
#define __HOWTO_PLAY_H__

#include "cocos2d.h"

class HowToPlay : public cocos2d::Layer
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
	CREATE_FUNC(HowToPlay);
};

#endif // __HISTROY_SCENE_