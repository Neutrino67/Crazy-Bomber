#ifndef _CRAZY_BOMBER_GAMELAYER
#define _CRAZY_BOMBER_GAMELAYER

#include "Bomb.h"
#include "MainPlayer.h"
#include "SubPlayer.h"
#include "cocos2d.h"

USING_NS_CC;

class GameLayer : public cocos2d :: Layer
{
public:
	GameLayer();
	virtual ~GameLayer();
	virtual bool init();
	CREATE_FUNC(GameLayer);

	// the KeyBoard CallBack
	void onKeyPressed(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* event1);
	void onKeyReleased(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* event1);


	void ExplosionCallBack();
	void TimerUpdate(float delta);

	virtual void update(float delta);

	void GameOverCallBack(float delta);
	void GameOverItemNoCallBack(Ref* pSender);
	void GameOverItemYesCallBack(Ref* pSender);

protected:
	MainPlayer * pMainPlayer;
	SubPlayer * pSubPlayer;
	Bomb * pBomb;
	bool is_collision;
	bool is_collision_2;
	int hurt_time_1;
	int hurt_time_2;
	LabelBMFont * hurt_time_lable_1;
	LabelBMFont * hurt_time_lable_2;
	LabelBMFont * timer;
	int cur_time;
};

#endif // !_CRAZY_BOMBER_GAMELAYER
