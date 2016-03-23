#pragma once
#ifndef _LOGIN_SCENE_H_
#define _LOGIN_SCENE_H_

#include "cocos2d.h"
#include "LoginLayer.h"

class LoginScene :public cocos2d::Layer
{
public:
	LoginScene();
	~LoginScene();

	static cocos2d::Scene* createScene();

	virtual bool init();

	// 定时器，每一帧调用
	virtual void update(float delta) override;
	// 此场景加载完毕后的操作
	virtual void onEnterTransitionDidFinish() override;

	CREATE_FUNC(LoginScene);

private:
	LoginLayer* loginLayer;

};




#endif