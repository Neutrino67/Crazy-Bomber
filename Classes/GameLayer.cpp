#include "GameLayer.h"
#include "MainPlayer.h"
#include "Bomb.h"
#include "HelloWorldScene.h"
#include "ChangeScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

GameLayer :: GameLayer()
{
	pMainPlayer = NULL;
	pSubPlayer = NULL;
	pBomb = NULL;
	is_collision = false;
	is_collision_2 = false;
	hurt_time_1 = 0;
	hurt_time_2 = 0;
	hurt_time_lable_1 = NULL;
	hurt_time_lable_2 = NULL;
	timer = NULL;
	cur_time = 59;
}



GameLayer :: ~GameLayer()
{
	pMainPlayer = NULL;
	pSubPlayer = NULL;
	pBomb = NULL;
	is_collision = false;
	is_collision_2 = false;
	hurt_time_1 = 0;
	hurt_time_2 = 0;
	hurt_time_lable_1 = NULL;
	hurt_time_lable_2 = NULL;
	timer = NULL;
	cur_time = 59;
}


bool GameLayer :: init()
{
	bool bRet = false;
	do
	{
		//super init
		if (!Layer :: init())
		{
			break;
		}
		/*auto sprite = Sprite::create("HelloWorld.png");
		this -> addChild(sprite);
		sprite -> setPosition(400.0f, 400.0f);
		*/
		Size visibleSize = Director :: getInstance() -> getVisibleSize();
	    Vec2 origin = Director :: getInstance() -> getVisibleOrigin();

		auto sprite = Sprite :: create("Resources/beiju.jpg");
		this -> addChild(sprite);
		sprite -> setAnchorPoint(Vec2(0, 1));
		sprite -> setPosition(0, origin.y + visibleSize.height);
		sprite -> setScale(0.8f);
		hurt_time_lable_1 = LabelBMFont :: create("X 00", "Resources/fonts/bitmapFontTest3.fnt", sprite -> getContentSize().height);
		hurt_time_lable_1 -> setAnchorPoint(Vec2(0, 1));
		hurt_time_lable_1 -> setPosition(sprite -> getPosition() + Vec2(sprite -> getContentSize().width, 0));
		this -> addChild(hurt_time_lable_1);


		auto sprite2 = Sprite :: create("Resources/beiju.jpg");
		this -> addChild(sprite2);
		sprite2 -> setAnchorPoint(Vec2(1, 1));
		sprite2 -> setPosition(origin.x + visibleSize.width, origin.y + visibleSize.height);
		sprite2 -> setScale(0.8f);
		hurt_time_lable_2 = LabelBMFont :: create("X 00", "Resources/fonts/bitmapFontTest3.fnt", sprite -> getContentSize().height, TextHAlignment ::RIGHT);
		hurt_time_lable_2 -> setAnchorPoint(Vec2(1, 1));
		hurt_time_lable_2 -> setPosition(sprite2 -> getPosition() - Vec2(sprite -> getContentSize().width, 0));
		this -> addChild(hurt_time_lable_2);

		timer = LabelBMFont :: create("60", "Resources/fonts/font-issue1343.fnt", 0, TextHAlignment :: CENTER);
		timer -> setAnchorPoint(Vec2(0.5, 1));
		timer -> setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height);
		this -> addChild(timer);
		timer -> setScale(2.0);
		schedule(schedule_selector(GameLayer :: TimerUpdate), 1.0f);


		pMainPlayer = MainPlayer :: create();
		pSubPlayer = SubPlayer :: create();
		pBomb = Bomb :: create();
		this -> addChild(pMainPlayer);
		this -> addChild(pSubPlayer);
		this -> addChild(pBomb);
		pMainPlayer -> setAnchorPoint(Vec2(0, 0));
		pSubPlayer -> setAnchorPoint(Vec2(0, 0));
		pBomb -> setAnchorPoint(Vec2(0, 0));
		pMainPlayer -> setPosition(0, 0);
		pSubPlayer -> setPosition(0, 0);
		pBomb -> setPosition(0, 0);

		//register the keyboard listener
		auto listener = EventListenerKeyboard :: create();
		listener -> onKeyPressed = CC_CALLBACK_2(GameLayer :: onKeyPressed, this);
		listener -> onKeyReleased = CC_CALLBACK_2(GameLayer :: onKeyReleased, this);
		_eventDispatcher -> addEventListenerWithSceneGraphPriority(listener, this);

		//open the update
		this ->scheduleUpdate();

		SimpleAudioEngine :: getInstance() -> preloadEffect("Resources/music/reva_sm_drop.mp3");
		SimpleAudioEngine :: getInstance() -> preloadEffect("Resources/music/victory_cheer.mp3");
		SimpleAudioEngine :: getInstance() -> preloadEffect("Resources/music/special_info.mp3");
		SimpleAudioEngine :: getInstance() -> preloadEffect("Resources/music/colo_hidden_fade.mp3");

		bRet = true;
	}while(0);
	return bRet;
}



void GameLayer :: onKeyPressed(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* event1)
{
	auto pMainSprite = pMainPlayer -> GetSprite();
	auto pBombSprite = pBomb -> GetSprite();
	auto pSubSprite = pSubPlayer -> GetSprite();

	switch(keyCode)
	{
	case EventKeyboard :: KeyCode :: KEY_B:
		{
			if (!is_collision) break;
		
			pBomb -> SetIsHoldOne(true); 

			Point SpritePoint = pMainSprite -> getPosition();
			auto x = SpritePoint.x - (pMainSprite -> getContentSize().width / 2) + 10.0f;
			auto y = SpritePoint.y + (pMainSprite -> getContentSize().height / 2) + 10.0f;
			SpritePoint = Vec2(x, y);
			pBombSprite -> runAction(MoveTo :: create(0.1f, SpritePoint));
		}


		break;


	case EventKeyboard :: KeyCode :: KEY_P:
		{
			if (!is_collision_2) break;
		
			pBomb -> SetIsHoldTwo(true); 

			Point SpritePoint = pSubSprite -> getPosition();
			auto x = SpritePoint.x + (pSubSprite -> getContentSize().width / 2) - 10.0f;
			auto y = SpritePoint.y + (pSubSprite -> getContentSize().height / 2) + 10.0f;
			SpritePoint = Vec2(x, y);
			pBombSprite -> runAction(MoveTo :: create(0.1f, SpritePoint));
		}




		break;
	}
}





void GameLayer :: onKeyReleased(cocos2d :: EventKeyboard :: KeyCode keyCode, Event* event1)
{

	Size visibleSize = Director :: getInstance() -> getVisibleSize();
	Vec2 origin = Director :: getInstance() -> getVisibleOrigin();
	auto pMainSprite = pMainPlayer -> GetSprite();
	auto pBombSprite = pBomb -> GetSprite();
	auto pSubSprite = pSubPlayer -> GetSprite();

	switch(keyCode)
	{
	case EventKeyboard :: KeyCode :: KEY_B:
		{

			if (!pBomb -> IsHoldOne()) break;

			//stop the explosion5

			pBomb -> unschedule(schedule_selector(Bomb :: Explosion5));
			pBombSprite -> stopActionByTag(_explosion5_action);


			Point SpritePoint1 = pBombSprite -> getPosition();
			Point SpritePoint2 = pSubSprite -> getPosition();
			auto spritesize = pSubSprite -> getContentSize();

			//get the random location
			auto left_boundary = origin.x + visibleSize.width / 2  + spritesize.width + 100.0f;
			auto right_boundary =  origin.x + visibleSize.width - spritesize.width / 2 - 80.0f;

			auto up_boundary = origin.y + visibleSize.height / 3 - 30.0f;
			auto down_boundary =   origin.y + spritesize.height / 2 + 60.0f;

			auto dx = left_boundary + CCRANDOM_0_1() * (right_boundary - left_boundary); 
			auto dy = down_boundary + CCRANDOM_0_1() * (up_boundary - down_boundary); 

			//cal the control piont 1
			auto control_point_1_x = SpritePoint1.x + (dx - SpritePoint1.x) * (1.0 / 3.0);
			auto control_point_1_y = SpritePoint1.y + 180.0f;

			//cal the control point 2
            auto control_point_2_x = SpritePoint1.x + (dx - SpritePoint1.x) * (2.0 / 3.0);
			auto control_point_2_y = SpritePoint1.y + 180.0f;

			ccBezierConfig bezier;
			bezier.controlPoint_1 = CCPointMake(control_point_1_x, control_point_1_y);
			bezier.controlPoint_2 = CCPointMake(control_point_2_x, control_point_2_y);
			bezier.endPosition = CCPointMake(dx, dy);
			//set the latelylocation
			pBomb -> SetLatelyLocation(Vec2(dx, dy));

			auto action1 = BezierTo :: create(1.0f, bezier);
			auto action2 = CallFunc :: create(CC_CALLBACK_0(GameLayer :: ExplosionCallBack, this));

			auto action = Sequence :: create(action1, action2, NULL);
	
			pBombSprite -> runAction(action);
			SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/reva_sm_drop.mp3");
			//auto animation = pBomb -> AnimationMaker(_explosion);
			//pBombSprite -> runAction(Animate :: create(animation));

			pBomb -> SetIsHoldOne(false);
		}
		break;




	case EventKeyboard :: KeyCode :: KEY_P:
		{

			if (!pBomb -> IsHoldTwo()) break;

			//stop the explosion5

			pBomb -> unschedule(schedule_selector(Bomb :: Explosion5));
			pBombSprite -> stopActionByTag(_explosion5_action);


			Point SpritePoint1 = pBombSprite -> getPosition();
			Point SpritePoint2 = pMainSprite -> getPosition();
			auto spritesize = pMainSprite -> getContentSize();

			//get the random location
			auto left_boundary = origin.x + spritesize.width / 2 + 80.0f;
			auto right_boundary =  origin.x + visibleSize.width / 2  - spritesize.width - 100.0f;

			auto up_boundary = origin.y + visibleSize.height / 3 - 30.0f;
			auto down_boundary =   origin.y + spritesize.height / 2 + 60.0f;

			auto dx = left_boundary + CCRANDOM_0_1() * (right_boundary - left_boundary); 
			auto dy = down_boundary + CCRANDOM_0_1() * (up_boundary - down_boundary); 

			//cal the control piont 1
			auto control_point_1_x = SpritePoint1.x + (dx - SpritePoint1.x) * (1.0 / 3.0);
			auto control_point_1_y = SpritePoint1.y + 180.0f;

			//cal the control point 2
            auto control_point_2_x = SpritePoint1.x + (dx - SpritePoint1.x) * (2.0 / 3.0);
			auto control_point_2_y = SpritePoint1.y + 180.0f;

			ccBezierConfig bezier;
			bezier.controlPoint_1 = CCPointMake(control_point_1_x, control_point_1_y);
			bezier.controlPoint_2 = CCPointMake(control_point_2_x, control_point_2_y);
			bezier.endPosition = CCPointMake(dx, dy);
			//set the latelylocation
			pBomb -> SetLatelyLocation(Vec2(dx, dy));

			auto action1 = BezierTo :: create(1.0f, bezier);
		
			auto action2 = CallFunc :: create(CC_CALLBACK_0(GameLayer :: ExplosionCallBack, this));
			auto action = Sequence :: create(action1, action2, NULL);
	
			pBombSprite -> runAction(action);
			SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/reva_sm_drop.mp3");
			//auto animation = pBomb -> AnimationMaker(_explosion);
			//pBombSprite -> runAction(Animate :: create(animation));

			pBomb -> SetIsHoldTwo(false);
		}
		break;







	}

}


void GameLayer :: update(float delta)
{
	// get the data

	Size visibleSize = Director :: getInstance() -> getVisibleSize();
	Vec2 origin = Director :: getInstance() -> getVisibleOrigin();

	auto pMainSprite = pMainPlayer -> GetSprite();
	auto pSubSprite = pSubPlayer -> GetSprite();
	auto pBombSprite = pBomb -> GetSprite();

	Point playerlocation1 = pMainSprite -> getPosition();
	Point playerlocation2 = pSubSprite -> getPosition();
	Point bomblocation = pBombSprite -> getPosition();

	Size playersize1 = pMainSprite -> getContentSize();
	Size playersize2 = pSubSprite -> getContentSize();
	Size bombsize = pBombSprite -> getContentSize();

	//fix the z order
	{
		auto bomby = bomblocation.y - bombsize.height / 2;
		auto bombx = bomblocation.x;
		auto player1y = playerlocation1.y - playersize1.height / 2;
		auto player2y = playerlocation2.y - playersize2.height / 2;

		if(!pBomb -> IsHoldOne() && !pBomb -> IsHoldTwo())
		{
			if (bombx <= origin.x + visibleSize.width / 2)
			{
				if (player1y <= bomby)
				{
					pMainPlayer -> setZOrder(500);
					pBomb -> setZOrder(0);
				}
				else
				{
					pMainPlayer -> setZOrder(0);
					pBomb -> setZOrder(500);
				}
			}
			else
			{
				if (player2y <= bomby)
				{
					pSubPlayer -> setZOrder(500);
					pBomb -> setZOrder(0);
				}
				else
				{
					pMainPlayer -> setZOrder(0);
					pBomb -> setZOrder(500);
				}
			}
		}
		else
		{
			pBomb -> setZOrder(500);
			pMainPlayer -> setZOrder(0);
			pSubPlayer -> setZOrder(0);
		}
	}

	{
	/***********************************
	 *      MAIN       PLAYER          *
	 ***********************************/

	//judge if is collision
	auto x0 = playerlocation1.x + playersize1.width / 2;
	auto y0 = playerlocation1.y - playersize1.height / 2;

	auto x1 = bomblocation.x;
	auto y1 = bomblocation.y - bombsize.height / 2;

	float eps = 1e-4;
	if ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - 100.0f <= eps)
	{
		is_collision = true;
	}
	else
		is_collision = false;
	}
	{
   /***********************************
	*      SUB       PLAYER           *
	***********************************/


	//judge if is collision
	auto x0 = playerlocation2.x - playersize2.width / 2;
	auto y0 = playerlocation2.y - playersize2.height / 2;

	auto x1 = bomblocation.x;
	auto y1 = bomblocation.y - bombsize.height / 2;

	float eps = 1e-4;
	if ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - 100.0f <= eps)
	{
		is_collision_2 = true;
	}
	else
		is_collision_2 = false;
	}

   /***********************************
	*              BOMB               *
	***********************************/

	if (!pBomb -> IsOver())
	{
		//deal with the explosion
		if (pBomb -> IsExplosion())
		{
			//do somethings -HP , set the sprite
			//auto x0 = playerlocation.x + playersize.width / 2  + 10.0f;
			//auto y0 = playerlocation.y - playersize.height / 2;

			//auto action = Place :: create(pBomb -> LatelyLocation());
			//pBombSprite -> runAction(action); 
			auto location = pBomb -> LatelyLocation().x;
			if (location <= origin.x + visibleSize.width / 2)
				hurt_time_1++;
			else
				hurt_time_2++;

			pBomb -> SetIsExplosion(false);
		}
	}
	else
	{
		//change the scence
		scheduleOnce(schedule_selector(GameLayer :: GameOverCallBack),3.0f);

	}

	//update the hurt time
	{
		char str1[105] = {0};
		sprintf(str1, "X 0%d", hurt_time_1);
		hurt_time_lable_1 -> setString(str1);

		char str2[105] = {0};
		sprintf(str2, "X 0%d", hurt_time_2);
		hurt_time_lable_2 -> setString(str2);	
	
	}




}


void GameLayer :: ExplosionCallBack()
{
	pBomb -> scheduleOnce(schedule_selector(Bomb :: Explosion5), 3.0f);
}


void GameLayer :: TimerUpdate(float delta)
{
	if (cur_time <= 0)
	{
		unschedule(schedule_selector(GameLayer :: TimerUpdate));
	}
	char str[103] = {0};
	sprintf(str, "%d", cur_time);
	timer -> setString(str);
	cur_time--;
}

void GameLayer :: GameOverCallBack(float delta)
{
	this -> unscheduleUpdate();
	Size visibleSize = Director :: getInstance() -> getVisibleSize();
	Vec2 origin = Director :: getInstance() -> getVisibleOrigin();

	auto sprite = Sprite :: create("Resources/green.jpg", Rect(0, 0, 450, 300));
	sprite -> setAnchorPoint(Vec2(0.5, 0.5));
	sprite -> setOpacity(200);
	sprite -> setZOrder(10000);
	sprite -> setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this -> addChild(sprite);

	SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/victory_cheer.mp3");
	
	char str[104] = {0};
	if (hurt_time_1 != hurt_time_2)
	{
		int winner = hurt_time_1 > hurt_time_2 ? 2 : 1;  
		sprintf(str, "%dP WIN!", winner);
	}
	else
	{
		sprintf(str, "DRAW!");
	}

	auto Label = LabelBMFont :: create(str, "Resources/fonts/boundsTestFont.fnt", 0, TextHAlignment :: CENTER);
	Label -> setAnchorPoint(Vec2(0.5, 0.5));
	Label -> setScale(2.0);
	sprite -> addChild(Label);


	auto Label2 = LabelBMFont :: create("Play again?", "Resources/fonts/boundsTestFont.fnt", 0, TextHAlignment :: CENTER);
	Label2 -> setAnchorPoint(Vec2(0.5, 0.5));
	sprite -> addChild(Label2);


	auto Label3 = LabelBMFont :: create("Yes", "Resources/fonts/boundsTestFont.fnt", 0, TextHAlignment :: CENTER);
	auto Item3 = MenuItemLabel :: create(Label3, CC_CALLBACK_1(GameLayer :: GameOverItemYesCallBack, this)); 
	Item3 -> setAnchorPoint(Vec2(0.5, 0.5));
	


	auto Label4 = LabelBMFont :: create("No", "Resources/fonts/boundsTestFont.fnt", 0, TextHAlignment :: CENTER);
	auto Item4 = MenuItemLabel :: create(Label4, CC_CALLBACK_1(GameLayer :: GameOverItemNoCallBack, this)); 
	Item4 -> setAnchorPoint(Vec2(0.5, 0.5));
	


	auto x = sprite -> getContentSize().width;
	auto y = sprite -> getContentSize().height;

	Label -> setPosition(x / 2, y);
	Label2 -> setPosition(x / 2, y / 2 + 20);
	Item3 -> setPosition(x / 2, y / 2 - 30);
	Item4 -> setPosition(x / 2, y / 2  - 70);
	auto menu = Menu :: create(Item3, Item4, NULL);
	menu -> setPosition(Vec2 :: ZERO);
	sprite -> addChild(menu);


	pBomb -> unschedule(schedule_selector(Bomb :: Explosion5));

}

void GameLayer :: GameOverItemNoCallBack(Ref* pSender)
{
	auto scene = HelloWorld :: createScene();

	SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/colo_hidden_fade.mp3");

	Director :: getInstance() -> replaceScene(scene);
}

void GameLayer :: GameOverItemYesCallBack(Ref* pSender)
{
	auto scene = ChangeScene :: create();

	SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/special_info.mp3");

	Director :: getInstance() -> replaceScene(scene);
}