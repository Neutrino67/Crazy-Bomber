#include "Gamescene.h"

USING_NS_CC;

Gamescene :: Gamescene()
{
}


Gamescene :: ~Gamescene()
{
}

bool Gamescene :: init()
{
	bool bRet = false;
	do
	{
		//super init
		if (!Scene :: init())
		{
			break;
		}


		auto cache = SpriteFrameCache :: getInstance();
		auto Sprite1 = Sprite :: createWithSpriteFrame(cache -> getSpriteFrameByName("Bomb/0.png"));
		Sprite1 -> setPosition(300.0f, 300.0f);
		this -> addChild(Sprite1);


		bRet = true;
	}while(0);
	return bRet;
}


