#include "HelloWorldScene.h"
#include "Gamescene.h"
#include "InstructionScene.h"
#include "ChangeScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

HelloWorld :: HelloWorld()
{
	reloadNums = 0;
	curReloadNum = 0;
	loading = true;
}

HelloWorld :: ~HelloWorld()
{
	//SimpleAudioEngine :: end();
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//add the background layer
	auto back = Sprite :: create("Resources/back1.png");
	back -> setFlippedY(true);
	back -> setFlippedX(true);
	back -> setAnchorPoint(Vec2(0, 0));
	back -> setScaleX(back -> getContentSize().width / visibleSize.width);
	back -> setScaleY(back -> getContentSize().height / visibleSize.height);
	back -> setPosition(origin);
	this -> addChild(back);

	auto Title = LabelBMFont :: create("C", "Resources/fonts/font-issue1343-hd.fnt");
	Title -> setScale(2);
	Title -> setAnchorPoint(Vec2(0, 0));
	Title -> setPosition(origin.x + visibleSize.width / 5, origin.y + visibleSize.height * 7 / 10);
	this -> addChild(Title);

	auto Title1 = LabelBMFont :: create("razy", "Resources/fonts/font-issue1343-hd.fnt");
	Title1 -> setScale(1);
	Title1 -> setAnchorPoint(Vec2(0, 0));
	Title1 -> setPosition(origin.x + visibleSize.width / 5 + 100.0f, origin.y + visibleSize.height * 7 / 10);
	this -> addChild(Title1);

	auto Title2 = LabelBMFont :: create("bomber", "Resources/fonts/font-issue1343-hd.fnt");
	Title2 -> setScale(1);
	Title2 -> setAnchorPoint(Vec2(0, 0));
	Title2 -> setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 6 / 10);
	this -> addChild(Title2);




    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "Resources/CloseNormal.png",
                                           "Resources/CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	auto label1 = LabelBMFont :: create("Play", "Resources/fonts/futura-48.fnt", 0, TextHAlignment :: CENTER);
    label1 -> setAnchorPoint(Vec2(0.5, 0.5));
	auto selectItem = MenuItemLabel :: create(label1, CC_CALLBACK_1(HelloWorld :: selectItemCallback, this)); 
	selectItem -> setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 - 60.0f));

	auto label2 = LabelBMFont :: create("Instructuon", "Resources/fonts/futura-48.fnt", 0, TextHAlignment :: CENTER);
	label2 -> setAnchorPoint(Vec2(0.5, 0.5));
	auto instructionItem = MenuItemLabel :: create(label2, CC_CALLBACK_1(HelloWorld :: instructionItemCallback, this));
	instructionItem -> setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3));

	auto label3 = LabelBMFont :: create("About", "Resources/fonts/futura-48.fnt", 0, TextHAlignment :: CENTER);
	label3 -> setAnchorPoint(Vec2(0.5, 0.5));
	auto aboutItem = MenuItemLabel :: create(label3, CC_CALLBACK_1(HelloWorld :: aboutItemCallback, this));
	aboutItem -> setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 - 120.0f));



    // create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, selectItem, instructionItem, aboutItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //auto label = LabelTTF::create("Crazy Bomber", "Arial", 24);
    
    // position the label on the center of the screen
   // label->setPosition(Vec2(origin.x + visibleSize.width/2,
                        //    origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
   // this->addChild(label, 1);

    // add "HelloWorld" splash screen"
   // auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
   // sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
  // this->addChild(sprite, 0);
    
	//add resources
	reloadResources.push_back("Resources/R_goblin_run.plist");
	reloadResources.push_back("Resources/R_goblin_throw.plist");
	reloadResources.push_back("Resources/B_goblin_run.plist");
	reloadResources.push_back("Resources/B_goblin_throw.plist");
	reloadResources.push_back("Resources/Bomb.plist");
	reloadResources.push_back("Resources/Explosion.plist");
	reloadNums = reloadResources.size();

	//open the scheduleUpdate
	this -> scheduleUpdate();
    
	SimpleAudioEngine :: getInstance() ->  preloadEffect("Resources/music/special_info.mp3");
	

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();
	SimpleAudioEngine :: end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld :: selectItemCallback(Ref * psender)
{
	auto scene = ChangeScene :: create();
	SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/special_info.mp3");
	Director :: getInstance() -> replaceScene(scene);
}

void HelloWorld :: instructionItemCallback(cocos2d :: Ref* pSender)
{
	auto scene = InstructionScene :: create();
	SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/special_info.mp3");
	Director :: getInstance() -> replaceScene(scene);
}

void HelloWorld :: aboutItemCallback(cocos2d :: Ref* pSender)
{
	//change the scene
	SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/special_info.mp3");
}
void HelloWorld :: update(float delta)
{
	if (loading)
	{
		loading = false;
		if (curReloadNum >= reloadNums)
		{
			this -> unscheduleUpdate();
			//replace the Scene

			/*auto cache = SpriteFrameCache :: getInstance();
			auto ll = Sprite :: createWithSpriteFrame(cache -> getSpriteFrameByName("B_goblin_run/0.png"));
			ll -> setPosition(300.0f, 300.0f);
			this -> addChild(ll);*/
			//just for test

			return;
		}
		else
		{
			//add the SpriteFram into cache

			auto cache = SpriteFrameCache :: getInstance();
			cache -> addSpriteFramesWithFile(reloadResources[curReloadNum]);
			curReloadNum++;
			loading = true;
		}
	}
}