#ifndef _CRAZY_BOMBER_BACKGROUNDLAYER_H
#define _CRAZY_BOMBER_BACKGROUNDLAYER_H

#include "cocos2d.h"

USING_NS_CC;

class BackGroundLayer : public :: Layer
{
public:
	BackGroundLayer();
	virtual ~BackGroundLayer();
	virtual bool init();
	CREATE_FUNC(BackGroundLayer);
};




#endif