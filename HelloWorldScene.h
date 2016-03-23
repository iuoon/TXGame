#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class RoleNode;

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	~HelloWorld();

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	bool isRoadAtTileCoord(const cocos2d::Point &tileCoord) const;
	cocos2d::Point tileCoordForPosition(const cocos2d::Point &position) const;
	cocos2d::Point positionForTileCoord(const cocos2d::Point &tileCoord) const;

	bool isValidTileCoord(const cocos2d::Point &tileCoord) const;
	cocos2d::PointArray *walkableAdjacentTilesCoordForTileCoord(int checkType, int index, const cocos2d::Point &tileCoord) const;
	void loadFinish(float i);
	bool isRoadRect(const cocos2d::Point &tileCoord)const;
private:
	bool isPropAtTileCoordForLayer(const char *prop, const cocos2d::Point &tileCoord, cocos2d::TMXLayer *layer) const;
	void setViewpointCenter(const cocos2d::Point &position);


	virtual void update(float delta) override;

private:
	Node* m_mapNode;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_bgLayer;
	cocos2d::TMXLayer *_objectLayer;
	cocos2d::SpriteBatchNode *_batchNode;
	RoleNode *m_pRole;
};

#endif // __HELLOWORLD_SCENE_H__
