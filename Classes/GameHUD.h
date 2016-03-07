#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameHUD : public Layer
{
public:
	Sprite* background;
	Sprite* selSpriteRange;
	Sprite* selSprite;
	Vector<Sprite*> movableSprites;
	static GameHUD* _sharHUD;
	// static CCScene scene();
	virtual bool init();
	static GameHUD* shareHUD();
	CREATE_FUNC(GameHUD);

	virtual void onEnter();
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);

	void machineGunATKInit(float machineGunATK);
	void fastMachineGunATKInit(float fastMachineGunATK);
	void missleATKInit(float missleATK);
	void machineGunRNGInit(float machineGunRNG);
	void fastMachineGunRNGInit(float fastMachineGunRNG);
	void missleRNGInit(float missleRNG);
	void machineGunCOSTInit(int machineGunCOST);
	void fastMachineGunCOSTInit(int fastMachineGunCOST);
	void missleCOSTInit(int missleCOST);
	void machineGunsAVAILABLEInit(int machineGunsAVAILABLE);
	void fastMachineGunsAVAILABLEInit(int fastMachineGunsAVAILABLE);
	void misslesAVAILABLEInit(int misslesAVAILABLE);

	void numCoinsCollectedChanged(int numCoinsCollected);
	void scoreCollectedChanged(int scoreCollected);

private:
	cocos2d::Label *machineGunATKLabel;
	LabelTTF *_machineGunATKLabel;
	cocos2d::Label *fastMachineGunATKLabel;
	LabelTTF *_fastMachineGunATKLabel;
	cocos2d::Label *missleATKLabel;
	LabelTTF *_missleATKLabel;

	cocos2d::Label *machineGunRNGLabel;
	LabelTTF *_machineGunRNGLabel;
	cocos2d::Label *fastMachineGunRNGLabel;
	LabelTTF *_fastMachineGunRNGLabel;
	cocos2d::Label *missleRNGLabel;
	LabelTTF *_missleRNGLabel;

	cocos2d::Label *machineGunCOSTLabel;
	LabelTTF *_machineGunCOSTLabel;
	cocos2d::Label *fastMachineGunCOSTLabel;
	LabelTTF *_fastMachineGunCOSTLabel;
	cocos2d::Label *missleCOSTLabel;
	LabelTTF *_missleCOSTLabel;

	cocos2d::Label *machineGunsAVAILABLELabel;
	LabelTTF *_machineGunsAVAILABLELabel;
	cocos2d::Label *fastMachineGunsAVAILABLELabel;
	LabelTTF *_fastMachineGunsAVAILABLELabel;
	cocos2d::Label *misslesAVAILABLELabel;
	LabelTTF *_misslesAVAILABLELabel;

	cocos2d::Label *coinLabel;
	LabelTTF *_coinLabel;
	cocos2d::Label *scoreLabel;
	LabelTTF *_scoreLabel;
};