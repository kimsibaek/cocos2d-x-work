#ifndef __SpriteExtendEx__MonsterCell__
#define __SpriteExtendEx__MonsterCell__

#include "cocos2d.h"

class MonsterCell : public cocos2d::Sprite
{
public:
	MonsterCell();

	void setPriority(int fixedPriority);
	void setPriorityWithThis(bool useNodePriotity);


	virtual void onEnter();
	virtual void onExit();

private :
	cocos2d::EventListener* _listener;

	int _fixedPriority;
	bool _useNodePriority;

};

#endif // __SpriteExtendEx__MonsterCell__
