#include "HelloWorldScene.h"
#include "pugixml/pugixml.hpp"

USING_NS_CC;

using namespace pugi;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255) ))
    {
        return false;
    }

	xml_document xmlDoc;

	std::string fileName = FileUtils::getInstance()->fullPathForFilename("data/test_data.xml");
	xml_parse_result result = xmlDoc.load_file(fileName.c_str());

	if (!result) {
		log("Error description: %s", result.description());
		log("Error offset: %d", result.offset);
		return false;
	}

	xml_node nodeResult = xmlDoc.child("result");
	xml_node nodeItems = nodeResult.child("items");

	for (xml_node nodeItem = nodeItems.child("item"); nodeItem; nodeItem = nodeItem.next_sibling("item")) {
		std::string symbolName = nodeItem.child("subject").text().get();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		this->log2("1. %s", symbolName.c_str());
#else
		log("%s", symbolName.c_str());
#endif
	}

	for (xml_node nodeItem : nodeItems.children("item")) {
		std::string symbolName = nodeItem.child("subject").text().get();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		this->log2("2. %s", symbolName.c_str());
#else
		log("%s", symbolName.c_str());
#endif
	}

	for (xml_node_iterator it = nodeItems.begin(); it != nodeItems.end(); ++it) {
		xpath_node node = *it;

		std::string symbolName = node.node().child("subject").text().get();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		this->log2("3. %s", symbolName.c_str());
#else
		log("%s", symbolName.c_str());
#endif
	}
    return true;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
void HelloWorld::log2(const char * pszFormat, ...) {
	static const int kMaxLogLen = 16 * 1024;

	char szBuf[kMaxLogLen];

	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf_s(szBuf, kMaxLogLen, kMaxLogLen, pszFormat, ap);
	va_end(ap);

	WCHAR wszBuf[kMaxLogLen] = { 0 };
	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
	OutputDebugStringW(wszBuf);
	OutputDebugStringA("\n");

	WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(szBuf), szBuf, sizeof(szBuf), nullptr, FALSE);
	printf("%s\n", szBuf);
}
#endif