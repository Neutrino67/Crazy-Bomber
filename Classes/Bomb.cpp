#include "Bomb.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

Bomb :: Bomb()
{
	pBomb = NULL;
	is_hold_one = false;
	is_hold_two = false;
	is_explosion = false;
	is_over = false;
	lately_location = Vec2(0, 0);
}

Bomb :: ~Bomb()
{
	pBomb = NULL;
	is_hold_one = false;
	is_hold_two = false;
	is_explosion = false;
	is_over = false;
	lately_location = Vec2(0, 0);
}

bool Bomb :: init()
{
	bool bRet = false;
	do
	{
		//super init
		if (!Node :: init())
		{
			break;
		}

		auto cache = SpriteFrameCache :: getInstance();
		pBomb = Sprite :: createWithSpriteFrame(cache -> getSpriteFrameByName("Bomb/0.png"));
		this -> addChild(pBomb);
		pBomb -> setPosition(200.0f, 200.0f);
		this -> SetLatelyLocation(Vec2(200.0f, 200.0f));

		auto animation =AnimationMaker(BAnimationtype :: _normal_animation);
		auto animate = Animate :: create(animation);
		pBomb -> runAction(RepeatForever :: create(animate));

		/*
		auto listener = EventListenerKeyboard :: create();
		listener -> onKeyPressed = CC_CALLBACK_2(Bomb :: onKeyPressed, this);
		listener -> onKeyReleased = CC_CALLBACK_2(Bomb :: onKeyReleased, this);
		_eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);
		*/
		//set the schedule 120s explosion
		this -> scheduleOnce(schedule_selector(Bomb :: Explosion120), 59.0f);
		this -> scheduleOnce(schedule_selector(Bomb :: Explosion5), 3.0f);

		SimpleAudioEngine :: getInstance() -> preloadEffect("Resources/music/bomb_01.mp3");

		bRet = true;
	}while(0);
	return bRet;
}


Animation * Bomb :: AnimationMaker(BAnimationtype type)
{
	auto cache = SpriteFrameCache :: getInstance();
	cocos2d :: Vector<SpriteFrame*> temp(10);
	char str[64] = {0};
	Animation * animation = NULL;

	switch (type)
	{
	case BAnimationtype :: _normal_animation:
		for (int i = 0; i < 3;++i)
		{
			sprintf(str, "Bomb/%d.png", i);
			auto frame = cache -> getSpriteFrameByName(str);
			temp.pushBack(frame);
		}

		animation = Animation :: createWithSpriteFrames(temp, 0.2f, 1);
	break;


	case _bomb_animation:
		for (int i = 0; i < 7;++i)
		{
			sprintf(str, "Bomb/%d.png", i);
			auto frame = cache -> getSpriteFrameByName(str);
			temp.pushBack(frame);
		}

		animation = Animation :: createWithSpriteFrames(temp, 1.0f / 6, 1);
	break;

	case _explosion_animation:
		for (int i = 0; i < 7;++i)
		{
			sprintf(str, "Explosion/%d.png", i);
			auto frame = cache -> getSpriteFrameByName(str);
			temp.pushBack(frame);
		}

		animation = Animation :: createWithSpriteFrames(temp, 0.1f, 1);
	break;

	default:
		animation = NULL;
		break;
	}
	return animation;
}


Sprite* Bomb :: GetSprite()
{
	return pBomb;
}

bool Bomb :: IsHoldOne()
{
	return is_hold_one;
}

void Bomb :: SetIsHoldOne(bool state)
{
	is_hold_one = state;
}

bool Bomb :: IsHoldTwo()
{
	return is_hold_two;
}

void Bomb :: SetIsHoldTwo(bool state)
{
	is_hold_two = state;
}

bool Bomb :: IsExplosion()
{
	return is_explosion;
}

void Bomb :: SetIsExplosion(bool state)
{
	is_explosion = state;
}

void Bomb :: Explosion120(float delta)
{
	auto animation1 = AnimationMaker(_bomb_animation);
	auto animation2 = AnimationMaker(_explosion_animation);
	auto animate1 = Animate :: create(animation1);
	auto animate2 = Animate :: create(animation2);

	Point point1 = pBomb -> getPosition();
	Size size1 = pBomb -> getContentSize();

	auto x = point1.x;
	auto y = point1.y + 80.0f;

	auto action1 = Place :: create(ccp(x, y));
	auto action2 = Place :: create(ccp(point1.x, point1.y));
	
	auto action = Sequence :: create(CallFunc :: create(CC_CALLBACK_0(Bomb :: ExplosionCallBack, this)),
									 animate1, 
								     CallFunc :: create(CC_CALLBACK_0(Bomb :: ExplosionCallBack3, this)),
								     NULL);

	pBomb -> runAction(action);
	unschedule(schedule_selector(Bomb :: Explosion5));
}


void Bomb :: Explosion5(float delta)
{
	auto animation1 = AnimationMaker(_bomb_animation);
	auto animation2 = AnimationMaker(_explosion_animation);
	auto animate1 = Animate :: create(animation1);

	Point point1 = pBomb -> getPosition();
	Size size1 = pBomb -> getContentSize();

	auto x = point1.x;
	auto y = point1.y + 80.0f;

	auto action1 = Place :: create(ccp(x, y));
	auto action2 = Place :: create(ccp(point1.x, point1.y));

	auto animate2 = Animate :: create(animation2);
	auto action = Sequence :: create(animate1, 
									 CallFunc :: create(CC_CALLBACK_0(Bomb :: ExplosionCallBack2, this)),
									 NULL);

	action -> setTag(BActiontype :: _explosion5_action);
	pBomb -> runAction(action);
}

void Bomb :: ExplosionCallBack()
{
	SetIsExplosion(true);
	if (IsHoldOne())
	{
		SetIsHoldOne(false);
	}

	if (IsHoldTwo())
	{
		SetIsHoldTwo(false);
	}
}

void Bomb :: ExplosionCallBack2()
{
	Point point1 = pBomb -> getPosition();
	Size size1 = pBomb -> getContentSize();

	auto x = point1.x;
	auto y = point1.y + 80.0f;

	auto action1 = Place :: create(ccp(x, y));
	auto action2 = Place :: create(ccp(point1.x, point1.y));
	auto action3 = Place :: create(LatelyLocation());

	auto animation = AnimationMaker(_explosion_animation);
	auto animate2 = Animate :: create(animation);
	auto action = Sequence :: create(CallFunc :: create(CC_CALLBACK_0(Bomb :: ExplosionCallBack, this)),
										action1, animate2, action2, action3,
										CallFunc :: create(CC_CALLBACK_0(Bomb :: ResetExplosion5, this)),
										NULL);

	action -> setTag(BActiontype :: _explosion5_action);
	pBomb -> runAction(action);
	SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/bomb_01.mp3");
}

void Bomb :: ExplosionCallBack3()
{
	this -> stopAllActions();
	Point point1 = pBomb -> getPosition();

	this -> SetLatelyLocation(point1);
	Size size1 = pBomb -> getContentSize();

	auto x = point1.x;
	auto y = point1.y + 80.0f;

	auto action1 = Place :: create(ccp(x, y));
	auto action2 = Place :: create(ccp(point1.x, point1.y));
	auto action3 = Place :: create(LatelyLocation());

	auto animation = AnimationMaker(_explosion_animation);
	auto animate2 = Animate :: create(animation);
	auto action = Sequence :: create(action1, animate2, action2, action3,
									 CallFunc :: create(CC_CALLBACK_0(Bomb :: ExplosionEnd, this)),
																	NULL);

	//action -> setTag(BActiontype :: _explosion5_action);
	pBomb -> runAction(action);
	SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/bomb_01.mp3");
}



Point Bomb :: LatelyLocation()
{
	return lately_location;
}

void Bomb :: SetLatelyLocation(Point location)
{
	lately_location = location;
}

void Bomb :: ResetExplosion5()
{
	this -> scheduleOnce(schedule_selector(Bomb :: Explosion5), 3.0f);
}

void Bomb :: ExplosionEnd()
{
	pBomb ->setVisible(false);
	is_over = true;
}

bool Bomb :: IsOver()
{
	return is_over;
}