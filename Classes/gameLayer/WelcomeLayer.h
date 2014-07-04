#ifndef _WELCOME_LAYER_H
#define _WELCOME_LAYER_H
#include "cocos2d.h"
class WelcomeLayer : public cocos2d::Layer
{
public:
	WelcomeLayer();
	~WelcomeLayer();

public:
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);

public:
	static cocos2d::Scene* createScene();

public:
	void startCallBack(Ref* sender);
	void StrartGame(Ref* pSender);
};

#endif // !_WELCOME_LAYER_H
