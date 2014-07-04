#ifndef _BALL_H_
#define _BALL_H_
#include "cocos2d.h"
class Ball :public cocos2d::Sprite
{
public:
	Ball();
	~Ball();
	virtual bool init();
	CREATE_FUNC(Ball);


	
public:
	void move();
	void destory();
	void rebound();
	void setisHited(bool bl);
	bool getisHited() const;
	void resetCanHit(float dt);

private:
	float vx;
	float vy;
	bool isHited;


	
};
#endif // !_BALL_H_

