#include "SubPlayer.h"

USING_NS_CC;

SubPlayer :: SubPlayer()
{
	pSubplayer = NULL;
	pAnimation = NULL;
	in_throw = false;
	in_run = 0;
}

SubPlayer :: ~SubPlayer()
{
	pSubplayer = NULL;
	pAnimation = NULL;
	in_throw = false;
	in_run = 0;
}

bool SubPlayer :: init()
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
		pSubplayer = Sprite :: createWithSpriteFrame(cache -> getSpriteFrameByName("R_goblin_run/0.png"));
		this -> addChild(pSubplayer);
		auto x = Director :: getInstance() -> getVisibleOrigin().x
			     +
				 Director :: getInstance() -> getVisibleSize().width - 100.0f;
		pSubplayer -> setPosition(x, 100.0f);
		//set the 2P Flip  ,different about 1P
		pSubplayer -> setFlipX(true);

		auto listener = EventListenerKeyboard :: create();
		listener -> onKeyPressed = CC_CALLBACK_2(SubPlayer :: onKeyPressed, this);
		listener -> onKeyReleased = CC_CALLBACK_2(SubPlayer :: onKeyReleased, this);
		_eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);


		bRet = true;
	}while(0);


	return bRet;
}

Animation * SubPlayer :: AnimationMaker(SAnimationtype type)
{
	auto cache = SpriteFrameCache :: getInstance();
	cocos2d :: Vector<SpriteFrame*> temp(10);
	char str[64] = {0};
	Animation * animation = NULL;

	switch (type)
	{
	case _s_run:
			for (int i = 0; i < 7; ++i)
			{
				sprintf(str, "R_goblin_run/%d.png", i);
				auto frame = cache -> getSpriteFrameByName(str);
				temp.pushBack(frame);
			}
			animation = Animation :: createWithSpriteFrames(temp, 0.08f, 1);
		break;


	case _s_throw_1:
			for (int i = 0; i < 3; ++i)
			{
				sprintf(str, "R_goblin_throw/%d.png", i);
				auto frame = cache -> getSpriteFrameByName(str);
				temp.pushBack(frame);
			}
			animation = Animation :: createWithSpriteFrames(temp, 0.02f, 1);
		break;

	case _s_throw_2:
			for (int i = 3; i < 5; ++i)
			{
				sprintf(str, "R_goblin_throw/%d.png", i);
				auto frame = cache -> getSpriteFrameByName(str);
				temp.pushBack(frame);
			}
			temp.pushBack(cache -> getSpriteFrameByName("R_goblin_throw/0.png"));
			animation = Animation :: createWithSpriteFrames(temp, 0.1f, 1);
		break;

	case _s_stoprun:
		    temp.pushBack(cache -> getSpriteFrameByName("R_goblin_run/3.png"));
			temp.pushBack(cache -> getSpriteFrameByName("R_goblin_run/2.png"));
			temp.pushBack(cache -> getSpriteFrameByName("R_goblin_run/0.png"));
			animation = Animation :: createWithSpriteFrames(temp, 0.02f, 1);
		break;

	default:
		    animation = NULL;
		break;
	} 
	//animation -> setRestoreOriginalFrame(true);
	return animation;
}


bool SubPlayer :: CheckLocationOut()
{
	Size visibleSize = Director :: getInstance() -> getVisibleSize();
	Vec2 origin = Director :: getInstance() -> getVisibleOrigin();

	auto position = pSubplayer -> getPosition();
	auto spritesize = pSubplayer -> getContentSize();

	if (position.y < origin.y + visibleSize.height / 3 + 30.0f
		&& position.y > origin.y + spritesize.height / 2 + 30.0f
		&& position.x > origin.x + visibleSize.width / 2  + spritesize.width + 50.0f
		&& position.x < origin.x + spritesize.width - 30.f)
		return true;
	else
		return false;
}

void SubPlayer :: judge()
{
	Size visibleSize = Director :: getInstance() -> getVisibleSize();
	Vec2 origin = Director :: getInstance() -> getVisibleOrigin();

	auto position = pSubplayer -> getPosition();
	auto spritesize = pSubplayer -> getContentSize();

	if (!(position.y < origin.y + visibleSize.height / 3 + 30.0f)) pSubplayer -> stopActionByTag(_s_a_move_up);
	if (!(position.y > origin.y + spritesize.height / 2 + 30.0f)) pSubplayer -> stopActionByTag(_s_a_move_down);
	if (!(position.x < origin.x + visibleSize.width - spritesize.width / 2 - 30.f)) pSubplayer -> stopActionByTag(_s_a_move_right);
	if (!(position.x > origin.x + visibleSize.width / 2  + spritesize.width + 50.0f)) pSubplayer -> stopActionByTag(_s_a_move_left);
}

void SubPlayer :: onKeyPressed(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* enent1)
{
	if (in_throw) return;
	//Get the Position
	Size visibleSize = Director :: getInstance() -> getVisibleSize();
	Vec2 origin = Director :: getInstance() -> getVisibleOrigin();
	auto position = pSubplayer -> getPosition();
	auto spritesize = pSubplayer -> getContentSize();
	


	switch(keyCode)
	{
	case EventKeyboard :: KeyCode :: KEY_UP_ARROW:
		{
			//set the state
			in_run++;

			auto animation = AnimationMaker(_s_run);
			auto action_animate = RepeatForever :: create(Animate :: create(animation));
			action_animate -> setTag(_s_run);
			pSubplayer -> runAction(action_animate);
			auto action_moveby = MoveBy :: create(0.1f, ccp(0.0f, 20.0f));
			auto action_squence = Sequence :: create(action_moveby, CallFunc :: create(this, callfunc_selector(SubPlayer :: judge)), NULL);
			auto action_movebyforever = RepeatForever :: create(action_squence);
			action_movebyforever -> setTag(_s_a_move_up);
			if ((position.y < origin.y + visibleSize.height / 3 + 30.0f))
			{
				pSubplayer -> runAction(action_movebyforever);
			}
		}
		break;


	case EventKeyboard :: KeyCode :: KEY_DOWN_ARROW:
	   {
		    in_run++;
			auto animation = AnimationMaker(_s_run);
			auto action_animate = RepeatForever :: create(Animate :: create(animation));
			action_animate -> setTag(_s_run);
			pSubplayer -> runAction(action_animate);
			auto action_moveby = MoveBy :: create(0.1f, ccp(0.0f, -20.0f));
			auto action_squence = Sequence :: create(action_moveby, CallFunc :: create(this, callfunc_selector(SubPlayer :: judge)), NULL);
			auto action_movebyforever = RepeatForever :: create(action_squence);
			action_movebyforever -> setTag(_s_a_move_down);
			if ((position.y > origin.y + spritesize.height / 2 + 30.0f))
			{
				pSubplayer -> runAction(action_movebyforever);
			}
	   }

		break;


	case EventKeyboard :: KeyCode :: KEY_RIGHT_ARROW:
	   {
			in_run++;
			auto animation = AnimationMaker(_s_run);
			auto action_animate = RepeatForever :: create(Animate :: create(animation) -> reverse());
			action_animate -> setTag(_s_runback);
			pSubplayer -> runAction(action_animate);
			auto action_moveby = MoveBy :: create(0.1f, ccp(20.0f, 0.0f));
			auto action_squence = Sequence :: create(action_moveby, CallFunc :: create(this, callfunc_selector(SubPlayer :: judge)), NULL);
			auto action_movebyforever = RepeatForever :: create(action_squence);
			action_movebyforever -> setTag(_s_a_move_right);
			if ((position.x < origin.x + visibleSize.width - spritesize.width / 2 - 30.0f))
			{
				pSubplayer -> runAction(action_movebyforever);
			}
	   }

		break;

	case EventKeyboard :: KeyCode :: KEY_LEFT_ARROW:
	   {
		    in_run++;
			auto animation = AnimationMaker(_s_run);
			auto action_animate = RepeatForever :: create(Animate :: create(animation));
			action_animate -> setTag(_s_run);
			pSubplayer -> runAction(action_animate);
			auto action_moveby = MoveBy :: create(0.1f, ccp(-20.0f, 0.0f));
			auto action_squence = Sequence :: create(action_moveby, CallFunc :: create(this, callfunc_selector(SubPlayer :: judge)), NULL);
			auto action_movebyforever = RepeatForever :: create(action_squence);
			action_movebyforever -> setTag(_s_a_move_left);
			if ((position.x > origin.x + visibleSize.width / 2  + spritesize.width + 50.0f))
			{
				pSubplayer -> runAction(action_movebyforever);
			}
	   }

		break;


	case EventKeyboard :: KeyCode :: KEY_P:
	   {
		   //keep in run
		    if (in_run) break;
		    //set the state
		    in_throw = true;
			pSubplayer -> stopAllActions();
		    auto animation = AnimationMaker(_s_throw_1);
			auto action_animate = Animate :: create(animation);
			pSubplayer -> runAction(action_animate);
			
	   }

		break;
	}
}

void SubPlayer :: onKeyReleased(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* enent1)
{
	switch(keyCode)
	{
	case EventKeyboard :: KeyCode :: KEY_UP_ARROW:
		{
			//keep in throw
			if (in_throw) break;

			pSubplayer -> stopActionByTag(_s_a_move_up);
			Director :: getInstance() -> getActionManager() ->removeActionByTag(_s_run, pSubplayer);
			auto animation = AnimationMaker(_s_stoprun);
			auto action_animate = Animate :: create(animation);
			pSubplayer -> runAction(action_animate);
			if (in_run) in_run--;
		}
		break;
		
	case EventKeyboard :: KeyCode :: KEY_DOWN_ARROW:
		{
			if (in_throw) break;

			pSubplayer -> stopActionByTag(_s_a_move_down);
			Director :: getInstance() -> getActionManager() ->removeActionByTag(_s_run, pSubplayer);
			auto animation = AnimationMaker(_s_stoprun);
			auto action_animate = Animate :: create(animation);
			pSubplayer -> runAction(action_animate);
			if (in_run) in_run--;
		}
		break;

	case EventKeyboard :: KeyCode :: KEY_RIGHT_ARROW:
		{
			if (in_throw) break;
			pSubplayer -> stopActionByTag(_s_a_move_right);
			Director :: getInstance() -> getActionManager() ->removeActionByTag(_s_runback, pSubplayer);
			auto animation = AnimationMaker(_s_stoprun);
			auto action_animate = Animate :: create(animation);
			pSubplayer -> runAction(action_animate);
			if (in_run) in_run--;
		}
		break;


	case EventKeyboard :: KeyCode :: KEY_LEFT_ARROW:
		{
			if (in_throw) break;
			pSubplayer -> stopActionByTag(_s_a_move_left);
			Director :: getInstance() -> getActionManager() ->removeActionByTag(_s_run, pSubplayer);
			auto animation = AnimationMaker(_s_stoprun);
			auto action_animate = Animate :: create(animation);
			pSubplayer -> runAction(action_animate);
			if (in_run) in_run--;
		}
		break;

	case EventKeyboard :: KeyCode :: KEY_P:
		{
			if (in_run) break;
		    auto animation = AnimationMaker(_s_throw_2);
			auto action_animate = Animate :: create(animation);
		
			pSubplayer -> runAction(action_animate);
			in_throw = false;
		}
		break;
	}
}


Sprite* SubPlayer :: GetSprite()
{
	return pSubplayer;
}