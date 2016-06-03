#ifndef __CustomTableViewCell_SCENE_H__
#define __CustomTableViewCell_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class CustomTableViewCell : public cocos2d::extension::TableViewCell
{
public:
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
};

#endif // __CustomTableViewCell_SCENE_H__
