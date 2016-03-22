#ifndef _CRAZY_BOMBER_SUBPLAYER_H
#define _CRAZY_BOMBER_SUBPLAYER_H

#include "cocos2d.h"

USING_NS_CC;

enum SAnimationtype
{
	_s_run,
	_s_runback,
	_s_stoprun,
	_s_throw_1,
	_s_throw_2
};

enum SActiontype
{
	//subplayer_action_run ..
	_s_a_run,
	_s_a_throw,
	_s_a_move_up,
	_s_a_move_down,
	_s_a_move_right,
	_s_a_move_left
};

class SubPlayer : public cocos2d :: Node
{
public:
	SubPlayer();
	virtual ~SubPlayer();
	virtual bool init();
	CREATE_FUNC(SubPlayer);

	Animation* AnimationMaker(SAnimationtype type);

	// the KeyBoard CallBack
	void onKeyPressed(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* event1);
	void onKeyReleased(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* event1);

	bool CheckLocationOut();
	void judge();
	Sprite* GetSprite();

protected:
	cocos2d :: Sprite* pSubplayer;
	cocos2d :: Animation* pAnimation;

	//state   so sorry that i don't know how to gao zhi
	bool in_throw;
	//there are 4 type of run ,once on of the key press this value++,and released value--;
	int in_run;
};








#endif // !_CRAZY_BOMBER_SUBPLAYER_H