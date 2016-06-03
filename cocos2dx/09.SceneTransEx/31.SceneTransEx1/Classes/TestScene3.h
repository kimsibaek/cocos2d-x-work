#ifndef __TestScene3_SCENE_H__
#define __TestScene3_SCENE_H__

#include "cocos2d.h"

class TestScene3 : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(TestScene3);
	void doClose(Ref* pSender);
};

#endif // __TestScene3_SCENE_H__
