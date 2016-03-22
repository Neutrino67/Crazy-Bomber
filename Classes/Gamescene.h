#ifndef _CRAZY_BOMBER_GAMESCENE_H
#define _CRAZY_BOMBER_GAMESCENE_H

#include "cocos2d.h"

class Gamescene : public cocos2d :: Scene
{
public:
	Gamescene();
	virtual ~Gamescene();
	virtual bool init();
	CREATE_FUNC(Gamescene);
	void update(float delta);


private:

};








#endif // !_CRAZY_BOMBER_GAMESCENE.H
