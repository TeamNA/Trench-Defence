#ifndef  _CREEP_H_
#define  _CREEP_H_

#include "cocos2d.h"
#include "WayPoint.h"

USING_NS_CC;

class Creep : public Sprite
{
public:
	int curHp;
	int moveDuration;
	int curWaypoint;
	int tag;
	Sprite* sprite;
	virtual bool init();
	Creep* initWithCreep(Creep* copyFrom);
	WayPoint* getNextWaypoint();
	WayPoint* getCurrentWaypoint();
	CREATE_FUNC(Creep);
};

class FastRedCreep : public Creep
{
public:
	static Creep* creep();
};

class StrongGreenCreep : public Creep
{
public:
	static Creep* creep();
};
class LightEffect;

class EffectSprite : public cocos2d::Sprite
{
public:
	static EffectSprite *create(const std::string &filename);
	static EffectSprite *createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);

	void setEffect(LightEffect *effect, const std::string &normalMapFilename);

protected:
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

	~EffectSprite();

	LightEffect *_effect = nullptr;
	cocos2d::Texture2D *_normalmap = nullptr;
};

#endif // _CREEP_H_