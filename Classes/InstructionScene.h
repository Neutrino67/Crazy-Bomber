#ifndef _CRAZY_BOMBER_INSTRUCTIONSCENE_H
#define _CRAZY_BOMBER_INSTRUCTIONSCENE_H

#include "cocos2d.h"

USING_NS_CC;

class InstructionScene : public Scene
{
public:
	InstructionScene();
	virtual ~InstructionScene();
	virtual bool init();
	CREATE_FUNC(InstructionScene);
 
	void InstructionCallBack(Ref* pSender);

	//display chinese
	char* FontToUTF8(const char* font);   
private:
};



#endif // ! _CRAZY_BOMBER_INSTRUCTIONSCENE_H