#ifndef _INGAME_LAYER_H_
#define _INGAME_LAYER_H_
#include "cocos2d.h"
#include "gameObjects/Ball.h"
class InGameLayer: public cocos2d::Layer
{
public:
	InGameLayer();
	~InGameLayer();

public:
	virtual bool init();
	CREATE_FUNC(InGameLayer);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event *unused_event);
	virtual void onEnterTransitionDidFinish();
public:
	static cocos2d::Scene* createScene();
	//��¼����
	static int* score ;
	void createBalls(int count);
	void moveAllBalls(float dt);
	void hitTest();
	float getDistance(cocos2d::Node* a, cocos2d::Node* b);
	void addEvents();
	float getDistance(cocos2d::Point a, cocos2d::Point b);
	void eachotherHit();
	void timeFunCount(float dt);
	void replayCallBack(Ref* sender);
	void pauseCallBack(Ref* sender);
	
private:
	//С��ʱ������ı�
	cocos2d::LabelAtlas* timeTxt;
	//ʱ�����
	int timeCount;
	//С������
	cocos2d::Vector<Ball*> ballList;
	//��ɫС�������
	cocos2d::Vector<cocos2d::Sprite*> touchBallList;
	//��ǰ����Ļ�ɫ��
	cocos2d::Sprite* yBall;
	//��¼��ǰ���������
	cocos2d::Point touchPos;
	//״̬�������ͣ��ʱ���û�ɫ����Ҳͣ������
	bool isTouched;
	//��ť
	cocos2d::Menu* pauseMenu ;
	/*ʱ�������*/
	cocos2d::Sprite* timeBar;
	
	
};

#endif // !_INGAME_LAYER_H_
