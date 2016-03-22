#ifndef _CRAZY_BOMBER_CHANGESCENE_H
#define _CRAZY_BOMBER_CHANGESCENE_H

#include "cocos2d.h"

USING_NS_CC;

class ChangeScene : public Scene
{
public:
	ChangeScene();
	virtual ~ChangeScene();
	virtual bool init();
	CREATE_FUNC(ChangeScene);
 
	void ChangeCallBack(float delta);
	LabelBMFont * timer;
	int time;
};



#endif // ! _CRAZY_BOMBER_CHANGESCENE_H