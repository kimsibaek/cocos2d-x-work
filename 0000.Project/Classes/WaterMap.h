#ifndef __WaterMap_H__
#define __WaterMap_H__

#include "cocos2d.h"

class WaterMap : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(WaterMap);
};

#endif // __WaterMap_SCENE_H__
