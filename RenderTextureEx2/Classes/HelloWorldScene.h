#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "CustomTableViewCell.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class HelloWorld
	: public cocos2d::LayerColor,
	public cocos2d::extension::TableViewDataSource,
	public cocos2d::extension::TableViewDelegate
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	cocos2d::EventListenerTouchAllAtOnce* listener;
	cocos2d::Size winSize;
	cocos2d::RenderTexture* m_pTarget;
	cocos2d::Vector<cocos2d::Sprite*> m_pBrush;
	cocos2d::Sprite* sprite_brush;
	cocos2d::Sprite* sprite_1;
	cocos2d::Sprite* sprite_2;
	cocos2d::Sprite* sprite_3;
	cocos2d::Sprite* sprite_4;
	cocos2d::Sprite* sprite_5;
	cocos2d::Sprite* sprite_6;
	cocos2d::Sprite* sprite_7;
	cocos2d::Sprite* sprite_8;
	cocos2d::Sprite* sprite_9;
	cocos2d::Sprite* sprite_10;
	cocos2d::Sprite* sprite_11;
	cocos2d::Sprite* sprite_12;
	cocos2d::Sprite* sprite_13;
	int num;
	~HelloWorld();
	virtual void onEnter();
	virtual void onExit();
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void saveImage(Ref* sender);
	void clearImage(Ref* sender);
	void SelectColor(int number);
	void SelectPosition(int number);
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
	cocos2d::Vector<cocos2d::Sprite*> sprite_vector;
	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {};
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);


};

#endif // __HELLOWORLD_SCENE_H__
