#ifndef __FireMap_H__
#define __FireMap_H__

#include "cocos2d.h"

class FireMap : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(FireMap);
};

#endif // __FireMap_SCENE_H__
