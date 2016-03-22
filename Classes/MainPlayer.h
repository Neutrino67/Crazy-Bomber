#ifndef _CRAZY_BOMBER_MAINPLAYER_H
#define _CRAZY_BOMBER_MAINPLAYER_H

#include "cocos2d.h"

USING_NS_CC;

enum Animationtype
{
	_run,
	_runback,
	_stoprun,
	_throw_1,
	_throw_2
};

enum Actiontype
{
	//action_run ..
	a_run,
	a_throw,
	a_move_up,
	a_move_down,
	a_move_right,
	a_move_left
};

class MainPlayer : public cocos2d :: Node
{
public:
	MainPlayer();
	virtual ~MainPlayer();
	virtual bool init();
	CREATE_FUNC(MainPlayer);

	Animation* AnimationMaker(Animationtype type);

	// the KeyBoard CallBack
	void onKeyPressed(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* event1);
	void onKeyReleased(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* event1);

	bool CheckLocationOut();
	void judge();
	Sprite* GetSprite();

protected:
	cocos2d :: Sprite* pMainplayer;
	cocos2d :: Animation* pAnimation;

	//state   so sorry that i don't know how to gao zhi
	bool in_throw;
	//there are 4 type of run ,once on of the key press this value++,and released value--;
	int in_run;
};





#endif //! _CRAZY_BOMBER_MAINPALYER_H