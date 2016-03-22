#include "MainPlayer.h"

USING_NS_CC;

MainPlayer :: MainPlayer()
{
	pMainplayer = NULL;
	pAnimation = NULL;
	in_throw = false;
	in_run = 0;
}

MainPlayer :: ~MainPlayer()
{
	pMainplayer = NULL;
	pAnimation = NULL;
	in_throw = false;
	in_run = 0;
}

bool MainPlayer :: init()
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
		pMainplayer = Sprite :: createWithSpriteFrame(cache -> getSpriteFrameByName("B_goblin_run/0.png"));
		this -> addChild(pMainplayer);
		pMainplayer -> setPosition(100.0f, 100.0f);

		auto listener = EventListenerKeyboard :: create();
		listener -> onKeyPressed = CC_CALLBACK_2(MainPlayer :: onKeyPressed, this);
		listener -> onKeyReleased = CC_CALLBACK_2(MainPlayer :: onKeyReleased, this);
		_eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);


		bRet = true;
	}while(0);


	return bRet;
}

Animation * MainPlayer :: AnimationMaker(Animationtype type)
{
	auto cache = SpriteFrameCache :: getInstance();
	cocos2d :: Vector<SpriteFrame*> temp(10);
	char str[64] = {0};
	Animation * animation = NULL;

	switch (type)
	{
	case _run:
			for (int i = 0; i < 7; ++i)
			{
				sprintf(str, "B_goblin_run/%d.png", i);
				auto frame = cache -> getSpriteFrameByName(str);
				temp.pushBack(frame);
			}
			animation = Animation :: createWithSpriteFrames(temp, 0.08f, 1);
		break;


	case _throw_1:
			for (int i = 0; i < 3; ++i)
			{
				sprintf(str, "B_goblin_throw/%d.png", i);
				auto frame = cache -> getSpriteFrameByName(str);
				temp.pushBack(frame);
			}
			animation = Animation :: createWithSpriteFrames(temp, 0.02f, 1);
		break;

	case _throw_2:
			for (int i = 3; i < 5; ++i)
			{
				sprintf(str, "B_goblin_throw/%d.png", i);
				auto frame = cache -> getSpriteFrameByName(str);
				temp.pushBack(frame);
			}
			temp.pushBack(cache -> getSpriteFrameByName("B_goblin_throw/0.png"));
			animation = Animation :: createWithSpriteFrames(temp, 0.1f, 1);
		break;

	case _stoprun:
		    temp.pushBack(cache -> getSpriteFrameByName("B_goblin_run/3.png"));
			temp.pushBack(cache -> getSpriteFrameByName("B_goblin_run/2.png"));
			temp.pushBack(cache -> getSpriteFrameByName("B_goblin_run/0.png"));
			animation = Animation :: createWithSpriteFrames(temp, 0.02f, 1);
		break;

	default:
		    animation = NULL;
		break;
	} 
	//animation -> setRestoreOriginalFrame(true);
	return animation;
}


bool MainPlayer :: CheckLocationOut()
{
	Size visibleSize = Director :: getInstance() -> getVisibleSize();
	Vec2 origin = Director :: getInstance() -> getVisibleOrigin();
	auto position = pMainplayer -> getPosition();
	auto spritesize = pMainplayer -> getContentSize();
	if (position.y < origin.y + visibleSize.height / 3 + 30.0f
		&& position.y > origin.y + spritesize.height / 2 + 30.0f
		&& position.x < origin.x + visibleSize.width / 2  - spritesize.width - 50.0f
		&& position.x > origin.x + spritesize.width / 2 + 30.f)
		return true;
	else
		return false;
}

void MainPlayer :: judge()
{
	Size visibleSize = Director :: getInstance() -> getVisibleSize();
	Vec2 origin = Director :: getInstance() -> getVisibleOrigin();
	auto position = pMainplayer -> getPosition();
	auto spritesize = pMainplayer -> getContentSize();
	if (!(position.y < origin.y + visibleSize.height / 3 + 30.0f)) pMainplayer -> stopActionByTag(a_move_up);
	if (!(position.y > origin.y + spritesize.height / 2 + 30.0f)) pMainplayer -> stopActionByTag(a_move_down);
	if (!(position.x > origin.x + spritesize.width / 2 + 30.f)) pMainplayer -> stopActionByTag(a_move_left);
	if (!(position.x < origin.x + visibleSize.width / 2  - spritesize.width - 50.0f)) pMainplayer -> stopActionByTag(a_move_right);
}

void MainPlayer :: onKeyPressed(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* enent1)
{
	if (in_throw) return;
	//Get the Position
	Size visibleSize = Director :: getInstance() -> getVisibleSize();
	Vec2 origin = Director :: getInstance() -> getVisibleOrigin();
	auto position = pMainplayer -> getPosition();
	auto spritesize = pMainplayer -> getContentSize();
	


	switch(keyCode)
	{
	case EventKeyboard :: KeyCode :: KEY_W:
		{
			//set the state
			in_run++;

			auto animation = AnimationMaker(_run);
			auto action_animate = RepeatForever :: create(Animate :: create(animation));
			action_animate -> setTag(_run);
			pMainplayer -> runAction(action_animate);
			auto action_moveby = MoveBy :: create(0.1f, ccp(0.0f, 20.0f));
			auto action_squence = Sequence :: create(action_moveby, CallFunc :: create(this, callfunc_selector(MainPlayer :: judge)), NULL);
			auto action_movebyforever = RepeatForever :: create(action_squence);
			action_movebyforever -> setTag(a_move_up);
			if ((position.y < origin.y + visibleSize.height / 3 + 30.0f))
			{
				pMainplayer -> runAction(action_movebyforever);
			}
		}
		break;


   case EventKeyboard :: KeyCode :: KEY_S:
	   {
		    in_run++;
			auto animation = AnimationMaker(_run);
			auto action_animate = RepeatForever :: create(Animate :: create(animation));
			action_animate -> setTag(_run);
			pMainplayer -> runAction(action_animate);
			auto action_moveby = MoveBy :: create(0.1f, ccp(0.0f, -20.0f));
			auto action_squence = Sequence :: create(action_moveby, CallFunc :: create(this, callfunc_selector(MainPlayer :: judge)), NULL);
			auto action_movebyforever = RepeatForever :: create(action_squence);
			action_movebyforever -> setTag(a_move_down);
			if ((position.y > origin.y + spritesize.height / 2 + 30.0f))
			{
				pMainplayer -> runAction(action_movebyforever);
			}
	   }

		break;


	case EventKeyboard :: KeyCode :: KEY_A:
	   {
			in_run++;
			auto animation = AnimationMaker(_run);
			auto action_animate = RepeatForever :: create(Animate :: create(animation) -> reverse());
			action_animate -> setTag(_runback);
			pMainplayer -> runAction(action_animate);
			auto action_moveby = MoveBy :: create(0.1f, ccp(-20.0f, 0.0f));
			auto action_squence = Sequence :: create(action_moveby, CallFunc :: create(this, callfunc_selector(MainPlayer :: judge)), NULL);
			auto action_movebyforever = RepeatForever :: create(action_squence);
			action_movebyforever -> setTag(a_move_left);
			if ((position.x > origin.x + spritesize.width / 2 + 30.0f))
			{
				pMainplayer -> runAction(action_movebyforever);
			}
	   }

		break;

	case EventKeyboard :: KeyCode :: KEY_D:
	   {
		    in_run++;
			auto animation = AnimationMaker(_run);
			auto action_animate = RepeatForever :: create(Animate :: create(animation));
			action_animate -> setTag(_run);
			pMainplayer -> runAction(action_animate);
			auto action_moveby = MoveBy :: create(0.1f, ccp(20.0f, 0.0f));
			auto action_squence = Sequence :: create(action_moveby, CallFunc :: create(this, callfunc_selector(MainPlayer :: judge)), NULL);
			auto action_movebyforever = RepeatForever :: create(action_squence);
			action_movebyforever -> setTag(a_move_right);
			if ((position.x < origin.x + visibleSize.width / 2  - spritesize.width - 50.0f))
			{
				pMainplayer -> runAction(action_movebyforever);
			}
	   }

		break;


    case EventKeyboard :: KeyCode :: KEY_B:
	   {
		   //keep in run
		    if (in_run) break;
		    //set the state
		    in_throw = true;
			pMainplayer -> stopAllActions();
		    auto animation = AnimationMaker(_throw_1);
			auto action_animate = Animate :: create(animation);
			pMainplayer -> runAction(action_animate);
			
	   }

		break;
	}
}

void MainPlayer :: onKeyReleased(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* enent1)
{
	switch(keyCode)
	{
	case EventKeyboard :: KeyCode :: KEY_W:
		{
			//keep in throw
			if (in_throw) break;

			pMainplayer -> stopActionByTag(a_move_up);
			Director :: getInstance() -> getActionManager() ->removeActionByTag(_run, pMainplayer);
			auto animation = AnimationMaker(_stoprun);
			auto action_animate = Animate :: create(animation);
			pMainplayer -> runAction(action_animate);
			if (in_run) in_run--;
		}
		break;
		
	case EventKeyboard :: KeyCode :: KEY_S:
		{
			if (in_throw) break;

			pMainplayer -> stopActionByTag(a_move_down);
			Director :: getInstance() -> getActionManager() ->removeActionByTag(_run, pMainplayer);
			auto animation = AnimationMaker(_stoprun);
			auto action_animate = Animate :: create(animation);
			pMainplayer -> runAction(action_animate);
			if (in_run) in_run--;
		}
		break;

	case EventKeyboard :: KeyCode :: KEY_A:
		{
			if (in_throw) break;
			pMainplayer -> stopActionByTag(a_move_left);
			Director :: getInstance() -> getActionManager() ->removeActionByTag(_runback, pMainplayer);
			auto animation = AnimationMaker(_stoprun);
			auto action_animate = Animate :: create(animation);
			pMainplayer -> runAction(action_animate);
			if (in_run) in_run--;
		}
		break;


	case EventKeyboard :: KeyCode :: KEY_D:
		{
			if (in_throw) break;
			pMainplayer -> stopActionByTag(a_move_right);
			Director :: getInstance() -> getActionManager() ->removeActionByTag(_run, pMainplayer);
			auto animation = AnimationMaker(_stoprun);
			auto action_animate = Animate :: create(animation);
			pMainplayer -> runAction(action_animate);
			if (in_run) in_run--;
		}
		break;

	case EventKeyboard :: KeyCode :: KEY_B:
		{
			if (in_run) break;
		    auto animation = AnimationMaker(_throw_2);
			auto action_animate = Animate :: create(animation);
		
			pMainplayer -> runAction(action_animate);
			in_throw = false;
		}
		break;
	}
}


Sprite* MainPlayer :: GetSprite()
{
	return pMainplayer;
}