#include "BackGroundLayer.h"

USING_NS_CC;

BackGroundLayer :: BackGroundLayer()
{
}

BackGroundLayer :: ~BackGroundLayer()
{
}

bool BackGroundLayer :: init()
{
    bool bRet = false;
	do
	{
		//super init
		if (!Layer :: init())
		{
			break;
		}

		Size visibleSize = Director :: getInstance() -> getVisibleSize();
	    Vec2 origin = Director :: getInstance() -> getVisibleOrigin();

		auto layer = LayerColor :: create(Color4B(255, 255, 255, 255));
		this -> addChild(layer);
		auto sprite = Sprite :: create("Resources/light.png");
		sprite -> setAnchorPoint(Vec2(0.5, 1));
		sprite -> setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height);
		sprite -> setScaleY((visibleSize.height * 2 / 3) / sprite -> getContentSize().height);
		sprite -> setScaleX((visibleSize.width) / sprite -> getContentSize().width);
		this -> addChild(sprite);

		auto sprite1 = Sprite :: create("Resources/background.png");
		sprite1 -> setAnchorPoint(Vec2(0.5, 1));
		sprite1 -> setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height);
		sprite1 -> setScaleY((visibleSize.height * 2 / 3) / sprite1 -> getContentSize().height);
		sprite1 -> setScaleX((visibleSize.width) / sprite1 -> getContentSize().width);
		this -> addChild(sprite1);

		for (int i = 0; i < 5; ++i)
		{
			char str[103] = {0};
			sprintf(str, "Resources/g%d.png", i);
			auto sprite2 = Sprite :: create(str);
			sprite2 -> setAnchorPoint(Vec2(0, 0));
			sprite2 -> setPosition(origin.x + sprite2 ->getContentSize().width * i, origin.y);
			//sprite1 -> setScaleY((visibleSize.height * 2 / 3 - 30.0f) / sprite1 -> getContentSize().height);
			//sprite1 -> setScaleX((visibleSize.width) / sprite1 -> getContentSize().width);
			this -> addChild(sprite2);
		}

		for (int i = 0; i <= 2; ++i)
		{
			auto sprite3 = Sprite :: create("Resources/bar.png");
			sprite3 -> setAnchorPoint(Vec2(0, 0));
			sprite3 -> setPosition(origin.x + visibleSize.width / 2 - 50.0f, origin.y + sprite3 -> getContentSize().height * i);
		
			this -> addChild(sprite3);
		}

		bRet = true;
	}while(0);
	return bRet;
}


