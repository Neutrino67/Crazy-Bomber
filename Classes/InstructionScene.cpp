#include "InstructionScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

InstructionScene :: InstructionScene()
{
}

InstructionScene :: ~InstructionScene()
{
}

bool InstructionScene :: init()
{
	bool bRet = false;
	do
	{
		//super init
		if (!Scene :: init())
		{
			break;
		}

		auto Label = LabelBMFont :: create("Back", "Resources/fonts/futura-48.fnt", 0, TextHAlignment :: RIGHT);
		auto Item = MenuItemLabel :: create(Label, CC_CALLBACK_1(InstructionScene :: InstructionCallBack, this)); 
	    Item -> setAnchorPoint(Vec2(1, 0));
		Item -> setScale(0.8);

		Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

		Item -> setPosition(origin.x + visibleSize.width, origin.y);
	
	    auto menu = Menu :: create(Item, NULL);
	    menu -> setPosition(Vec2 :: ZERO);
	    this -> addChild(menu);

		auto Label1 = LabelTTF :: create(" ", "΢���ź�", 20);
		Label1 -> setPosition(origin.x + visibleSize.width  / 2, origin.y + visibleSize.height * 2 / 3);
		Label1 -> setString(FontToUTF8("1P �� WSAD ���Ʒ��� B ��ը��\n2P �� �������� ���Ʒ��� P��ը��\n ÿ3Sû���־�ըһ�� 60S����ʱ��������ձ�ը���ж���Χ��С ��������ء���\n��겻Ҫ��̫��= ="));
		this -> addChild(Label1);

		SimpleAudioEngine :: getInstance() -> preloadEffect("Resources/music/colo_hidden_fade.mp3");
		bRet = true;
	}while(0);
	return bRet;
}

void InstructionScene :: InstructionCallBack(Ref* pSender)
{
	auto scene = HelloWorld :: createScene();
	SimpleAudioEngine :: getInstance() -> playEffect("Resources/music/colo_hidden_fade.mp3");
	Director :: getInstance() -> replaceScene(scene);
}

char* InstructionScene :: FontToUTF8(const char* font)  
{  
    int len=MultiByteToWideChar(CP_ACP,0,font,-1,NULL,0);  
    wchar_t* wstr=new wchar_t[len+1];  
    memset(wstr,0,len+1);  
    MultiByteToWideChar(CP_ACP,0,font,-1,wstr,len);  
    len=WideCharToMultiByte(CP_UTF8,0,wstr,-1,NULL,0,NULL,NULL);  
    char* str=new char[len+1];  
    memset(str,0,len+1);  
    WideCharToMultiByte(CP_UTF8,0,wstr,-1,str,len,NULL,NULL);  
    if(wstr)delete[] wstr;  
    return str;  
}  