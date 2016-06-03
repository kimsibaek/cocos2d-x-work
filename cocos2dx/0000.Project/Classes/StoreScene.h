#ifndef __StoreScene_H__
#define __StoreScene_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "CustomTableViewCell.h"
#include "MonsterCell.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class StoreScene : public cocos2d::Layer,
	public cocos2d::extension::TableViewDataSource,
	public cocos2d::extension::TableViewDelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(StoreScene);
	void doClick1(Ref *pSender);
	std::string dbfileName;
	void selectData(Ref* pSender);
	void selectGoldData(Ref* pSender);
	void doBuy(Ref* pSender);
	void doSendMsg(int num);
	void doSell(Ref* pSender);
	virtual void onEnter();
	virtual void onExit();

	cocos2d::EventListenerTouchOneByOne* listener;
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Size winSize;
	cocos2d::Sprite* sprite_1;
	MonsterCell *temp[4];
	TableView* tableView1;
	TableView* tableView2;
	int x_Num;
	int Cell_Num;
	int FireSize;
	int EarthSize;
	int WaterSize;
	int WindSize;
	cocos2d::SpriteFrameCache *cache;

	//효과음 변수
	unsigned int m_nSoundId;

	cocos2d::Vector<cocos2d::Sprite*> sprite_vector;
	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {};
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	void Monster(int num, int row);
	cocos2d::Sprite *tableViewSprite;
	void UpdatePlayerDB();
	void UpdateItemsDB(int num);
	cocos2d::Sprite *Upgrade;
	bool setUpdateItemproperty;
	int Gold;
	cocos2d::LabelAtlas *Gold_Label;
	cocos2d::Sprite* Gold_Img;
	cocos2d::Sprite* Gold_text;
	cocos2d::Sprite* TexScene;
};

#endif // __StoreScene_SCENE_H__
