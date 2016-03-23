#pragma once
#ifndef _LOGIN_LAYER_H_
#define _LOGIN_LAYER_H_

#include "cocos2d.h"

class LoginLayer :public cocos2d::Layer
{
public:
	LoginLayer();
	~LoginLayer();

	virtual bool init() override;

	CREATE_FUNC(LoginLayer);

	// ��������
	void scrollBackground();

private:
		// ��ʼ������
	void initBackground();
private:
		// ������ͼ
	cocos2d::Sprite *bgsprite1;
	cocos2d::Sprite *bgsprite2;
		// ��x������ٶ�
	double speed;

};



#endif
