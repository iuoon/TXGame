#include "HelloWorldScene.h"
#include "RoleNode.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"//UI��ص�ͷ�ļ�
#include "cocostudio/CocoStudio.h"
#include "searchArithmetic.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace cocostudio;
using namespace cocos2d;//CSLoaderλ��cocos2d�����ռ䡣
using namespace cocostudio::timeline;//������ص���λ��cocostuio::timeline����

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);



	return scene;
}

HelloWorld::HelloWorld() :
	_tileMap(nullptr),
	_bgLayer(nullptr),
	_objectLayer(nullptr),
	_batchNode(nullptr),
	m_pRole(nullptr)
{
}

HelloWorld::~HelloWorld()
{
}

bool HelloWorld::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		//��ͼcsb
		m_mapNode = CSLoader::createNode("cocosScene.csb");
		m_mapNode->setAnchorPoint(Vec2(0, 0));
		m_mapNode->setPosition(Vec2(0, 0));
		m_mapNode->setVertexZ(1);
		this->addChild(m_mapNode);


		//��ȡ��ͼ
		_tileMap = (TMXTiledMap *)m_mapNode->getChildByName("Map_2");

		//��ʼ����
		Point spawnTileCoord(6, 9);
		Point spawnPos = this->positionForTileCoord(spawnTileCoord);
		this->setViewpointCenter(spawnPos);

		//��ײ��
		_bgLayer = _tileMap->getLayer("obstacle");

		//���������㷨
		searchArithmetic::getArithmeticInstance()->setMainthis(this);


		m_pRole = RoleNode::createWithLayer(this);
		//m_pRole->setVertexZ(200);
		m_pRole->setPosition(spawnPos);
		_tileMap->addChild(m_pRole, 300);

		//�¼�����
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [this](Touch *touch, Event *event) {

			Point touchLocation = _tileMap->convertTouchToNodeSpace(touch);
			Point toTileCoord = this->tileCoordForPosition(touchLocation);
			m_pRole->moveToward(toTileCoord);


			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		this->scheduleUpdate();


		bRet = true;
	} while (0);


	return bRet;
}
void HelloWorld::loadFinish(float i)
{
	//    Size size =  Director::getInstance()->getWinSize();
	//    Armature* armature = cocostudio::Armature::create("hero_ani_11001_4");
	//    armature->setPosition(Vec2(size.width*0.5,size.height*0.5));
	//    this->addChild(armature,10000);
}
//����ǲ��ǿ�������
bool HelloWorld::isRoadAtTileCoord(const Point &tileCoord) const
{
	return this->isPropAtTileCoordForLayer("road", tileCoord, _bgLayer);
}

//λ��ת������ͼ
Point HelloWorld::tileCoordForPosition(const Point &position) const
{
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return Point(x, y);
}

Point HelloWorld::positionForTileCoord(const Point &tileCoord) const
{
	int x = (tileCoord.x * _tileMap->getTileSize().width) + _tileMap->getTileSize().width / 2;

	int y = (_tileMap->getMapSize().height * _tileMap->getTileSize().height) -
		(tileCoord.y * _tileMap->getTileSize().height) - _tileMap->getTileSize().height / 2;

	return Point(x, y);
}



bool HelloWorld::isPropAtTileCoordForLayer(const char *prop, const Point &tileCoord, TMXLayer *layer) const
{
	if (!this->isValidTileCoord(tileCoord))//ȷ��λ���Ƿ��ڵ�ͼ��
	{
		return false;
	}

	int gid = layer->getTileGIDAt(tileCoord);
	Value properties = _tileMap->getPropertiesForGID(gid);//��ȡ��������
	if (properties.isNull())
	{
		return false;
	}
	return properties.asValueMap().find(prop) != properties.asValueMap().end();
}
//ȷ��λ���Ƿ��ڵ�ͼ��
bool HelloWorld::isValidTileCoord(const Point &tileCoord) const
{
	if (tileCoord.x < 0 || tileCoord.y < 0 ||
		tileCoord.x >= _tileMap->getMapSize().width ||
		tileCoord.y >= _tileMap->getMapSize().height)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool HelloWorld::isRoadRect(const cocos2d::Point &tileCoord)const
{
	bool isRoad = false;
	bool t = false;
	bool l = false;
	bool b = false;
	bool r = false;

	// ��
	Point UpPoint(tileCoord.x, tileCoord.y - 1);
	if (this->isValidTileCoord(UpPoint) && this->isRoadAtTileCoord(UpPoint))//ȷ��λ���Ƿ��ڵ�ͼ���Լ��ǲ����ϰ���
	{
		t = true;
	}

	// ��
	Point LeftPoint(tileCoord.x - 1, tileCoord.y);
	if (this->isValidTileCoord(LeftPoint) && this->isRoadAtTileCoord(LeftPoint))
	{
		l = true;
	}

	// ��
	Point DownPoint(tileCoord.x, tileCoord.y + 1);
	if (this->isValidTileCoord(DownPoint) && this->isRoadAtTileCoord(DownPoint))
	{
		b = true;
	}

	// ��
	Point RightPoint(tileCoord.x + 1, tileCoord.y);
	if (this->isValidTileCoord(RightPoint) && this->isRoadAtTileCoord(RightPoint))
	{
		r = true;
	}
	if (t && l && b && r)
	{
		isRoad = true;
	}
	return isRoad;
}
//��ȡָ��λ�õ��ܱ߶���(����1.Ϊ���������������2.Ϊ�������������)
PointArray *HelloWorld::walkableAdjacentTilesCoordForTileCoord(int checkType, int index, const Point &tileCoord) const
{
	int len = index * 8;
	PointArray *tmp = PointArray::create(len);

	bool t = false;
	bool l = false;
	bool b = false;
	bool r = false;

	// ��
	Point UpPoint(tileCoord.x, tileCoord.y - index);
	if (this->isValidTileCoord(UpPoint) && this->isRoadAtTileCoord(UpPoint))//ȷ��λ���Ƿ��ڵ�ͼ���Լ��ǲ����ϰ���
	{
		tmp->addControlPoint(UpPoint);
		t = true;
	}

	// ��
	Point LeftPoint(tileCoord.x - index, tileCoord.y);
	if (this->isValidTileCoord(LeftPoint) && this->isRoadAtTileCoord(LeftPoint))
	{
		tmp->addControlPoint(LeftPoint);
		l = true;
	}

	// ��
	Point DownPoint(tileCoord.x, tileCoord.y + index);
	if (this->isValidTileCoord(DownPoint) && this->isRoadAtTileCoord(DownPoint))
	{
		tmp->addControlPoint(DownPoint);
		b = true;
	}

	// ��
	Point RightPoint(tileCoord.x + index, tileCoord.y);
	if (this->isValidTileCoord(RightPoint) && this->isRoadAtTileCoord(RightPoint))
	{
		tmp->addControlPoint(RightPoint);
		r = true;
	}

	if (checkType == 1)//�����������
	{
		// ����
		Point p(tileCoord.x - index, tileCoord.y - index);
		if (t && l && this->isValidTileCoord(p) && this->isRoadAtTileCoord(p))
		{
			tmp->addControlPoint(p);
		}

		// ����
		p.setPoint(tileCoord.x - index, tileCoord.y + index);
		if (b && l && this->isValidTileCoord(p) && this->isRoadAtTileCoord(p))
		{
			tmp->addControlPoint(p);
		}

		// ����
		p.setPoint(tileCoord.x + index, tileCoord.y - index);
		if (t && r && this->isValidTileCoord(p) && this->isRoadAtTileCoord(p))
		{
			tmp->addControlPoint(p);
		}

		// ����
		p.setPoint(tileCoord.x + index, tileCoord.y + index);
		if (b && r && this->isValidTileCoord(p) && this->isRoadAtTileCoord(p))
		{
			tmp->addControlPoint(p);
		}
	}
	else //�������������⴦��
	{
		//�����ĸ���������
		for (int i = -index; i <= index; i++)
		{
			if (i != 0)
			{
				// �ϲ�
				Point tempPosition1(UpPoint.x - i, UpPoint.y);
				if (this->isValidTileCoord(tempPosition1) && this->isRoadAtTileCoord(tempPosition1))
				{
					tmp->addControlPoint(tempPosition1);
				}
				// �²�
				Point tempPosition2(DownPoint.x - i, DownPoint.y);
				if (this->isValidTileCoord(tempPosition2) && this->isRoadAtTileCoord(tempPosition2))
				{
					tmp->addControlPoint(tempPosition2);
				}
			}

		}

		int rangeIndex = index - 1;
		for (int i = -rangeIndex; i <= rangeIndex; i++)
		{
			if (i != 0)
			{
				// �Ҳ�
				Point tempPosition1(RightPoint.x, RightPoint.y - i);
				if (this->isValidTileCoord(tempPosition1) && this->isRoadAtTileCoord(tempPosition1))
				{
					tmp->addControlPoint(tempPosition1);
				}
				//���
				Point tempPosition2(LeftPoint.x, LeftPoint.y - i);
				if (this->isValidTileCoord(tempPosition2) && this->isRoadAtTileCoord(tempPosition2))
				{
					tmp->addControlPoint(tempPosition2);
				}
			}
		}
	}

	return tmp;
}


//��ͼ���澵ͷ
void HelloWorld::setViewpointCenter(const Point &position)
{
	Size winSize = Director::getInstance()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Point actualPosition(x, y);

	Point centerOfView(winSize.width / 2, winSize.height / 2);
	Point viewPoint = centerOfView - actualPosition;

	m_mapNode->setPosition(viewPoint);
}


void HelloWorld::update(float delta)
{
	this->setViewpointCenter(m_pRole->getPosition());
}


