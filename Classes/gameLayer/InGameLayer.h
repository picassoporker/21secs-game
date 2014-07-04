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
	//记录分数
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
	//小球时间计数文本
	cocos2d::LabelAtlas* timeTxt;
	//时间计数
	int timeCount;
	//小球容器
	cocos2d::Vector<Ball*> ballList;
	//黄色小球的容器
	cocos2d::Vector<cocos2d::Sprite*> touchBallList;
	//当前点击的黄色球
	cocos2d::Sprite* yBall;
	//记录当前点击的坐标
	cocos2d::Point touchPos;
	//状态：点击暂停的时候，让黄色的球也停下来。
	bool isTouched;
	//按钮
	cocos2d::Menu* pauseMenu ;
	/*时间进度条*/
	cocos2d::Sprite* timeBar;
	
	
};

#endif // !_INGAME_LAYER_H_
