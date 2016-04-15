#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "vector"

class Sprite_num {

	int gemType;
	float xPos;
	float yPos;
	float xSpeed;
	float ySpeed;
	Sprite_num() {
		gemType = 0;
		xPos = 0;
		yPos = 0;
		xSpeed = 0;
		ySpeed = 0;
	}
};


extern Sprite_num* gGameOverGems;
extern int gGameOverGemsSize;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	int kGemSize = 40;
	int kBoardWidth = 8;
	int kBoardHeight = 10;
	int kNumTotalGems = kBoardWidth * kBoardHeight;
	int kTimeBetweenGemAdds = 8;
	int kTotalGameTime = 1000 * 60;
	int kIntroTime = 1800;
	int kNumRemovalFrames = 8;
	int kDelayBeforeHint = 3000;
	int kMaxTimeBetweenConsecutiveMoves = 1000;
	float kGameOverGemSpeed = 0.1;
	float kGameOverGemAcceleration = 0.005;

	int kBoardTypeGem0 = 0;
	int kBoardTypeGem1 = 1;
	int kBoardTypeGem2 = 2;
	int kBoardTypeGem3 = 3;
	int kBoardTypeGem4 = 4;
	int kBoardTypePup0 = 5;
	
	int *gBoard;

	cocos2d::Vector<Sprite_num> gFallingGems;


	cocos2d::Vector<cocos2d::Sprite*> gBoardSprites;
	float *gNumGemsInColumn;
	int *gTimeSinceAddInColumn;

	int gLastTakenGemTime;
	int gNumConsecutiveGems;
	bool gIsPowerPlay;
	//var gPowerPlayParticles;
	//var gPowerPlayLayer;

	int gScore;

	cocos2d::Sprite* gTimer;

	int gStartTime;
	int gLastMoveTime;
	bool gIsDisplayingHint;

	bool gBoardChangedSinceEvaluation;
	int gPossibleMove;
	
	bool gIsGameOver = false;
	//var gGameOverGems;
	//var gScoreLabel;
	bool gEndTimerStarted;
	//cocos2d::Vector<Sprite_num*> gFallingGems[8];

	cocos2d::ProgressTimer *m_pHPProgress;

	void setupShimmer();
	void addScore(int score);
	void onScore();
	void onPressPause(Ref *pSender);
	
	void removeMarkedGems();
	int findMove();
	int getGemType(int x, int y);
	void createRandomMove();
	void setGemType(int x, int y, int newType);
	void updatePowerPlay();
	void updateSparkle();
	void createGameOver();
	void removeShimmer();
	void displayHint();
	std::vector<int> findConnectedGems_(int x, int y, std::vector<int> arr, int gemType);
	std::vector<int> findConnectedGems(int x, int y);
	void updateGameOver();
	
	void onUpdate(float f);

	virtual void onEnter();
	virtual void onExit();
	bool activatePowerUp(int x, int y);
	bool removeConnectedGems(int x, int y);
	void onRemoveFromParent(cocos2d::Vec2 vec);
	void processClick(cocos2d::Vec2 loc);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	

	int Score_Num = 0;
	cocos2d::Label* label;
	cocos2d::Size winSize;
	unsigned int m_nSoundId;
	
	
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__
