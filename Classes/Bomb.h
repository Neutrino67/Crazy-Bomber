#ifndef _CRAZY_BOMBER_BOMB_H
#define _CRAZY_BOMBER_BOMB_H

#include "cocos2d.h"

USING_NS_CC;

enum BAnimationtype
{
	_normal_animation,
	_bomb_animation,
	_explosion_animation
};

enum BActiontype
{
	_explosion5_action,
	_normal_action,
};



class Bomb : public :: Node
{
public:
	Bomb();
	virtual ~Bomb();
	virtual bool init();
	CREATE_FUNC(Bomb);
	Sprite* GetSprite();
	bool IsHoldOne();
	void SetIsHoldOne(bool state);

	bool IsHoldTwo();
	void SetIsHoldTwo(bool state);

	bool IsExplosion();
	void SetIsExplosion(bool state);

	bool IsOver();

	Point LatelyLocation();
	void SetLatelyLocation(Point location);

	Animation* AnimationMaker(BAnimationtype type);
	void Explosion120(float delta);
	void Explosion5(float delta);

	void ExplosionCallBack();
	void ExplosionCallBack2();
	void ExplosionCallBack3();
	void ExplosionEnd();

	void ResetExplosion5();
	//KeyBoard Callback
	//void onKeyPressed(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* event1);
	//void onKeyReleased(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* event1);


protected:

	Sprite* pBomb;
	bool is_hold_one;
	bool is_hold_two;
	bool is_explosion;
	bool is_over;
	Point lately_location;
};














#endif //! _CRAZY_BOMBER_BOMB_H