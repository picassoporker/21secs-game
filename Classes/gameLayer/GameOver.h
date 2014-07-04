#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_
#include "cocos2d.h"
class GameOver:public cocos2d::Layer
{
public:
	GameOver();
	~GameOver();
	virtual bool init();
	CREATE_FUNC(GameOver);
	
public:
	static cocos2d::Scene* createScene();
public:
	void closeGame(cocos2d::Ref* pSender);
	void reStrartGame(cocos2d::Ref* pSender);
};

#endif // !_GAME_OVER_H_
