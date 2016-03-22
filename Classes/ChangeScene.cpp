#include "ChangeScene.h"
#include "Gamescene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

ChangeScene :: ChangeScene()
{
	timer = NULL;
	time = 4;

}

ChangeScene :: ~ChangeScene()
{
	timer = NULL;
	time = 4;
}

bool ChangeScene :: init()
{
	bool bRet = false;
	do
	{
		//super init
		if (!Scene :: init())
		{
			break;
		}

		Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto sprite = Sprite :: create("Resources/change.jpg");
		sprite -> setAnchorPoint(Vec2(0, 0));
		sprite -> setPosition(origin);
		this -> addChild(sprite);

		timer = LabelBMFont :: create("","Resources/fonts/font-issue1343.fnt", 0, TextHAlignment :: CENTER);
		timer -> setAnchorPoint(Vec2(0.5, 0.5));
		timer -> setScale(5.0f);
		timer -> setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
		this -> addChild(timer);

		schedule(schedule_selector(ChangeScene :: ChangeCallBack), 1.0f);

		SimpleAudioEngine :: getInstance() -> preloadEffect("Resources/music/goloop.mp3");
		SimpleAudioEngine :: getInstance() -> preloadEffect("Resources/music/bingo_set.mp3");

		bRet = true;
	}while(0);
	return bRet;
}

void ChangeScene :: ChangeCallBack(float delta)
{
	time--;
	char str[105];
	if (time >= 1)
	{
		sprintf(str, "%d!", time);
		timer -> setString(str);
		SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/goloop.mp3");
	}
	else
		if (time == 0)
		{
			timer -> setString("Begin!");
			SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/bingo_set.mp3");
		}
		else
		{
			auto scene = Gamescene :: create();
			Director :: getInstance() -> replaceScene(scene);
		}
}