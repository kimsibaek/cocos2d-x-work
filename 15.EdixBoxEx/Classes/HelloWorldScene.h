#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"						//extensions/cocos-ext.h 인클루드르르 위해 참조 디렉터리 추가 : 프로젝트 - 우클릭 - 속성 - 구성 속성 - c/c++ - 일반 - 추가 포함디렉터리 에서 $(EngineRoot)추가
class HelloWorld : public cocos2d::LayerColor, public cocos2d::extension::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);

	cocos2d::extension::EditBox* m_pEditName;
	cocos2d::extension::EditBox* m_pEditPassword;
	cocos2d::extension::EditBox* m_pEditEmail;
};

#endif // __HELLOWORLD_SCENE_H__
