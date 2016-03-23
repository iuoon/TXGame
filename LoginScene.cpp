#include "LoginScene.h"

USING_NS_CC;

LoginScene::LoginScene()
{
}

LoginScene::~LoginScene()
{
}

Scene* LoginScene::createScene()
{
		// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoginScene::create();

	// add layer as a child to scene
	scene->addChild(layer);



	return scene;
}

bool LoginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->loginLayer = LoginLayer::create();
	this->loginLayer->setAnchorPoint(ccp(0, 0));
	this->loginLayer->setPosition(ccp(0, 0));
	this->addChild(loginLayer);


	return true;
}

void LoginScene::update(float delta)
{
	log("%s","runing scroll");
	this->loginLayer->scrollBackground();
}

void LoginScene::onEnterTransitionDidFinish()
{
	Node::onEnterTransitionDidFinish();
	// 场景加载完毕才滚动背景
	this->scheduleUpdate();
}
