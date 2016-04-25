#ifndef __EarthMap_H__
#define __EarthMap_H__

#include "cocos2d.h"

class EarthMap : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(EarthMap);
};

#endif // __EarthMap_SCENE_H__
