﻿#ifndef __ClassChange_H__
#define __ClassChange_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "CustomTableViewCell.h"
#include "MonsterCell.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class ClassChange : public cocos2d::Layer,
	public cocos2d::extension::TableViewDataSource,
	public cocos2d::extension::TableViewDelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(ClassChange);
	void doClick1(Ref *pSender);
	std::string dbfileName;
	void selectData(Ref* pSender);
	void doContinue(Ref* pSender);
	void doSendMsg(Ref* pSender);
	void doClose(Ref* pSender);
	virtual void onEnter();
	virtual void onExit();
	//효과음 변수
	unsigned int m_nSoundId;
	cocos2d::EventListenerTouchOneByOne* listener;
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Size winSize;
	cocos2d::Sprite* sprite_1;
	MonsterCell *temp[4];
	TableView* tableView1;
	int x_Num;
	int Cell_Num;
	int FireSize;
	int EarthSize;
	int WaterSize;
	int WindSize;
	cocos2d::SpriteFrameCache *cache;

	cocos2d::Vector<cocos2d::Sprite*> sprite_vector;
	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {};
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	void Monster(int num, int row);
	cocos2d::Sprite *tableViewSprite;
	bool CheckClass(int num);
	void UpdateMonsterDB(int num, int Type);
	void MonsterAdd(int num, cocos2d::Sprite *st);
	void RemoveSprite();
	cocos2d::Sprite *Upgrade;
};

#endif // __ClassChange_SCENE_H__
