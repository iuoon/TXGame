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

	// 滚动背景
	void scrollBackground();

private:
		// 初始化背景
	void initBackground();
private:
		// 背景地图
	cocos2d::Sprite *bgsprite1;
	cocos2d::Sprite *bgsprite2;
		// 沿x轴滚动速度
	double speed;

};



#endif
