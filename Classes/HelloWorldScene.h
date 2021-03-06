#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	virtual ~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void selectItemCallback(cocos2d :: Ref* pSender);
	void instructionItemCallback(cocos2d :: Ref* pSender);
	void aboutItemCallback(cocos2d :: Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private :
	void update(float delta);
	int reloadNums;
	int curReloadNum;
	bool loading;
	std :: vector<std :: string> reloadResources;
};

#endif // __HELLOWORLD_SCENE_H__
