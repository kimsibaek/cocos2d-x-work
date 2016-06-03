#ifndef __ContactListener_SCENE_H__
#define __ContactListener_SCENE_H__



#include "cocos2d.h"
#include "Box2D/Box2D.h"


using namespace cocos2d;

class ContactListener : public b2ContactListener
{
public:
	ContactListener();
	~ContactListener();

	virtual void BeginContack(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};

#endif // __ContactListener_SCENE_H__
