﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"

using namespace cocos2d;
using namespace network;

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void onGetTest(Ref* sender);
	void onPostTest(Ref* sender);
	void onPostBinaryTest(Ref* sender);

	void onHttpRequestCompleted(HttpClient* sender, HttpResponse* response);

	LabelTTF* _labelStatusCode;
};

#endif // __HELLOWORLD_SCENE_H__
