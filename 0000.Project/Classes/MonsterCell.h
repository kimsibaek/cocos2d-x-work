#ifndef __SpriteExtendEx__MonsterCell__
#define __SpriteExtendEx__MonsterCell__

#include "cocos2d.h"

class MonsterCell : public cocos2d::Sprite
{
public:
	MonsterCell();

	void setPriority(int fixedPriority);
	void setPriority2(int fixedPriority);
	void setPriorityWithThis(bool useNodePriotity);

	bool Color;
	virtual void onEnter();
	virtual void onExit();

private :
	cocos2d::EventListener* _listener;

	int _fixedPriority;
	int _fixedPriority2;
	bool _useNodePriority;
	bool usevalue;
};

#endif // __SpriteExtendEx__MonsterCell__
