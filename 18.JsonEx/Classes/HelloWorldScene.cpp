#include "HelloWorldScene.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"

USING_NS_CC;

using namespace rapidjson;

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

	Document document;
	std::string fileName = FileUtils::getInstance()->fullPathForFilename("data/test_data.json");
	log("[%s]", fileName.c_str());
	
	std::string clearData = FileUtils::getInstance()->getStringFromFile(fileName);

	if (document.Parse<0>(clearData.c_str()).HasParseError()) {
		log("%s",document.GetParseError());
		return 1;
	}

	std::string str1 = document["hello"].GetString();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	this->log2("hello = %s\n", str1.c_str());
#else
		log("hello = %s\n", str1.c_str());
#endif


	int n1 = document["i"].GetInt();
	log("i = %d\n", n1);

	bool isT = document["t"].GetBool();
	log("t = %d\n", isT);

	const rapidjson::Value& a = document["a"];
	for (SizeType i = 0; i < a.Size(); i++) {
		log("a = %d", a[i].GetInt());
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