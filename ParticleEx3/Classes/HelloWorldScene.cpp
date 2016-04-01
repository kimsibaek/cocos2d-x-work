#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 0) ))
    {
        return false;
    }
    return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	this->showParticle(touchPoint);
	return true;
}

void HelloWorld::showParticle(Vec2 pPoint) {
	const char* filename1 = "Particles/BoilingFoam.plist";
	const char* filename2 = "Particles/BoilingFoamStar.plist";
	const char* filename3 = "Particles/BurstPipe.plist";
	const char* filename4 = "Particles/ButterFly.plist";
	const char* filename5 = "Particles/ButterFlyYFlipped.plist";
	const char* filename6 = "Particles/Comet.plist";
	const char* filename7 = "Particles/debian.plist";
	const char* filename8 = "Particles/ExplodingRing.plist";
	const char* filename9 = "Particles/Flower.plist";
	const char* filename10 = "Particles/Galaxy.plist";
	const char* filename11 = "Particles/LavaFlow.plist";
	const char* filename12 = "Particles/lines.plist";
	const char* filename13 = "Particles/Phoenix.plist";
	const char* filename14 = "Particles/SmallSun.plist";
	const char* filename15 = "Particles/SpinningPeas.plist";
	const char* filename16 = "Particles/Spiral.plist";
	const char* filename17 = "Particles/SpookyPeas.plist";
	const char* filename18 = "Particles/TestPremultipliedAlpha.plist";
	const char* filename19 = "Particles/Upsidedown.plist";
	//const char* filename20 = "Particles/particle_texture.plist";

	ParticleSystem* emitter = ParticleSystemQuad::create(filename19);
	emitter->setPosition(pPoint);
	emitter->setDuration(2.0f);
	emitter->setAutoRemoveOnFinish(true);

	this->addChild(emitter);
}