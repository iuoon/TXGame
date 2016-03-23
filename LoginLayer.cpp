#include "LoginLayer.h"

USING_NS_CC;

LoginLayer::LoginLayer()
{
}

LoginLayer::~LoginLayer()
{
}

bool LoginLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->initBackground();

	return true;
}

void LoginLayer::scrollBackground()
{
	   // 计算出背景往左滚动时的位置
		auto nextPos_1 = this->bgsprite1->getPositionX() - this->speed;
		auto nextPos_2 = this->bgsprite2->getPositionX() - this->speed;
		this->bgsprite1->setPositionX(nextPos_1);
		this->bgsprite2->setPositionX(nextPos_2);
		//向左移动的绝对值大于等于背景的宽度,重新设置背景的位置
		if (fabs(nextPos_1) >= this->bgsprite1->getContentSize().width)
		{
				this->bgsprite1->setPositionX(this->bgsprite2->getContentSize().width+this->bgsprite1->getPositionX());
				Sprite *t = this->bgsprite1;
				this->bgsprite1 = this->bgsprite2;
				this->bgsprite2 = t;
		}
}

void LoginLayer::initBackground()
{
	bgsprite1 = Sprite::create("bg.jpg");
	bgsprite1->setAnchorPoint(ccp(0, 0)); //设置背景精力锚点为左下角
	bgsprite1->setPosition(ccp(0, 0)); //设置精灵的位置
	this->addChild(bgsprite1, 1);

	bgsprite2 = Sprite::create("bg.jpg");
	bgsprite2->setAnchorPoint(ccp(0, 0)); //设置背景精力锚点为左下角
	bgsprite2->setPosition(ccp(bgsprite1->getContentSize().width, 0)); //设置精灵的位置
	this->addChild(bgsprite2, 1);

	// 设置初始滚动速度
	this->speed = 2;
	// 防止背景滚动的时候两张图片衔接部分出现黑边
//	this->bgsprite1->getTexture()->setAliasTexParameters();
}

