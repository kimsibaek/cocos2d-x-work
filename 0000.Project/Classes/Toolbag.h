#ifndef __Toolbag_H__
#define __Toolbag_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "CustomTableViewCell.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class Toolbag :
	public cocos2d::LayerColor,
	public cocos2d::extension::TableViewDataSource,
	public cocos2d::extension::TableViewDelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(Toolbag);
	std::string dbfileName;
	void selectData(Ref* pSender);
	void doContinue(Ref* pSender);
	void doSendMsg(Ref* pSender);
	void doClose(Ref* pSender);
	virtual void onEnter();
	virtual void onExit();

	cocos2d::EventListenerTouchOneByOne* listener;
	//cocos2d::EventListenerTouchAllAtOnce* listener;
	cocos2d::Size winSize;
	//cocos2d::RenderTexture* m_pTarget;
	//cocos2d::Vector<cocos2d::Sprite*> m_pBrush;
	//cocos2d::Sprite* sprite_brush;
	cocos2d::Sprite* sprite_1;
	//cocos2d::Sprite* sprite_2;
	//cocos2d::MenuItemFont* item1;
	//cocos2d::MenuItemFont* item2;
	//cocos2d::Menu* menu;
	TableView* tableView1;
	int num;

	cocos2d::SpriteFrameCache *cache;

	cocos2d::Vector<cocos2d::Sprite*> sprite_vector;
	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {};
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
};

#endif // __Toolbag_SCENE_H__
