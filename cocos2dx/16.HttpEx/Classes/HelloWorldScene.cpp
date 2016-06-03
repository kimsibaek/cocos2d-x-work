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
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255) ))
    {
        return false;
    }
	MenuItemFont::setFontSize(24);
	MenuItemFont::setFontName("Courier New");
	
	auto pMenuItem1 = MenuItemFont::create("Get", CC_CALLBACK_1(HelloWorld::onGetTest, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));

	auto pMenuItem2 = MenuItemFont::create("Post", CC_CALLBACK_1(HelloWorld::onPostTest, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));

	auto pMenuItem3 = MenuItemFont::create("Post Binary", CC_CALLBACK_1(HelloWorld::onPostBinaryTest, this));
	pMenuItem3->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);
	pMenu->alignItemsVertically();

	this->addChild(pMenu);

	_labelStatusCode = LabelTTF::create("HTTP Status Code", "Courier New", 20);
	_labelStatusCode->setPosition(Vec2(240, 260));
	_labelStatusCode->setColor(Color3B::BLUE);
	addChild(_labelStatusCode);


    return true;
}

void HelloWorld::onGetTest(Ref* sender) {
	{
		//test1
	HttpRequest* request = new HttpRequest();
	request->setUrl("http://just-make-this-request-failed.com");
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted));
	request->setTag("GET test1");
	HttpClient::getInstance()->send(request);
	request->release();

	}
	{
		//test2
		HttpRequest* request = new HttpRequest();
		request->setUrl("http://ipip.kr/");
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted));
		request->setTag("GET test2");
		HttpClient::getInstance()->send(request);
		request->release();

	}
	{
		//test3
		HttpRequest* request = new HttpRequest();
		request->setUrl("http://httpbin.org/get");
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted));
		request->setTag("GET test3");
		HttpClient::getInstance()->send(request);
		request->release();

	}

	_labelStatusCode->setString("waiting...");
}
void HelloWorld::onPostTest(Ref* sender) {
	{
		//test1
		HttpRequest* request = new HttpRequest();
		request->setUrl("http://httpbin.org/post");
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted));
		
		const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";

		request->setRequestData(postData, strlen(postData));
		request->setTag("POST test1");
		HttpClient::getInstance()->send(request);
		request->release();

	}
	{
		//test2
		HttpRequest* request = new HttpRequest();
		request->setUrl("http://httpbin.org/post");
		request->setRequestType(HttpRequest::Type::POST);
		
		std::vector<std::string> headers;
		headers.push_back("Content-Type: application/json; charset=utf-8");
		request->setHeaders(headers);

		request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted));
		const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
		request->setRequestData(postData, strlen(postData));
		request->setTag("POST test2");
		HttpClient::getInstance()->send(request);
		request->release();

	}
	_labelStatusCode->setString("waiting...");
}
void HelloWorld::onPostBinaryTest(Ref* sender) {
	HttpRequest* request = new HttpRequest();
	request->setUrl("http://httpbin.org/post");
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted));
	
	char postData[22] = "binary=hello\0\0cocos2d";
	request->setRequestData(postData, 22);

	request->setTag("POST Binary test");
	HttpClient::getInstance()->send(request);
	request->release();

	_labelStatusCode->setString("waiting...");
}

void HelloWorld::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response) {
	if (!response) {
		return;
	}

	if (0 != strlen(response->getHttpRequest()->getTag())) {
		log("%s completed", response->getHttpRequest()->getTag());
	}

	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code:%d, \n tag = %s", statusCode, response->getHttpRequest()->getTag());
	_labelStatusCode->setString(statusString);
	log("response code: %d", statusCode);

	if (!response->isSucceed()) {
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	printf("Http Test, dump data: ");
	for (unsigned int i = 0; i < buffer->size(); i++) {
		printf("%c", (*buffer)[i]);
	}
	printf("\n");
}