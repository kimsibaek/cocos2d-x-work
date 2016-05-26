#include "MonsterCell.h"
#include "stdafx.h"

USING_NS_CC;

MonsterCell::MonsterCell()
	: _listener(nullptr)
	, _fixedPriority(0)
	, _fixedPriority2(0)
	, _useNodePriority(false)
	, usevalue(false)
{
	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
}

void MonsterCell::setPriority(int fixedPriority)
{
	_fixedPriority = fixedPriority;
	_useNodePriority = false;
	usevalue = true;
}

void MonsterCell::setPriority2(int fixedPriority)
{
	_fixedPriority2 = fixedPriority;
	_useNodePriority = false;
	usevalue = false;
}

void MonsterCell::setPriorityWithThis(bool useNodePriority) {
	_useNodePriority = useNodePriority;
	//_fixedPriority = true;
}

void MonsterCell::onEnter() {
	Sprite::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		_useNodePriority = true;
		return true;
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event) {
		_useNodePriority = false;
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		if (_useNodePriority) {
			Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
			Size s = this->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);
			if (rect.containsPoint(locationInNode)) {
				//reZorder(target);
				//log("touch began..%d", _fixedPriority);
				if (usevalue) {
					MonsterCellNum = _fixedPriority;
				}
				else {
					MonsterCellNum2 = _fixedPriority2;
				}
			
				//this->setColor(Color3B::RED);
			}
			//this->setColor(Color3B::WHITE);
		}
		
	};

	if (_useNodePriority) {
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	else {
		_eventDispatcher->removeEventListener(listener);
		//_eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
	}
	_listener = listener;
}

void MonsterCell::onExit() {
	_eventDispatcher->removeEventListener(_listener);
	
	Sprite::onExit();
}