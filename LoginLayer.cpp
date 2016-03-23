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
	   // ����������������ʱ��λ��
		auto nextPos_1 = this->bgsprite1->getPositionX() - this->speed;
		auto nextPos_2 = this->bgsprite2->getPositionX() - this->speed;
		this->bgsprite1->setPositionX(nextPos_1);
		this->bgsprite2->setPositionX(nextPos_2);
		//�����ƶ��ľ���ֵ���ڵ��ڱ����Ŀ��,�������ñ�����λ��
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
	bgsprite1->setAnchorPoint(ccp(0, 0)); //���ñ�������ê��Ϊ���½�
	bgsprite1->setPosition(ccp(0, 0)); //���þ����λ��
	this->addChild(bgsprite1, 1);

	bgsprite2 = Sprite::create("bg.jpg");
	bgsprite2->setAnchorPoint(ccp(0, 0)); //���ñ�������ê��Ϊ���½�
	bgsprite2->setPosition(ccp(bgsprite1->getContentSize().width, 0)); //���þ����λ��
	this->addChild(bgsprite2, 1);

	// ���ó�ʼ�����ٶ�
	this->speed = 2;
	// ��ֹ����������ʱ������ͼƬ�νӲ��ֳ��ֺڱ�
//	this->bgsprite1->getTexture()->setAliasTexParameters();
}

