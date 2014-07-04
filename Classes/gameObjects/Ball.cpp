#include "Ball.h"
USING_NS_CC;

Ball::Ball() : vx(CCRANDOM_0_1() * 10 ),
			   vy(CCRANDOM_0_1() * 10 ),
			   isHited(false)
{
}
Ball::~Ball()
{
}
bool Ball::init()
{
	Sprite::init();
	initWithFile("ball_1.png");
	
	return true;
}

void Ball::move()
{
	float nextPosX = this->getPositionX() + vx; 
	float nextPosY = this->getPositionY() + vy;
	this->setPosition(nextPosX,nextPosY);
	Size winSize = Director::getInstance()->getVisibleSize();
	Size ballSize = this->getContentSize();
	if (nextPosX <= ballSize.width/2)
	{
		vx *= -1;
		this->setPositionX(ballSize.width/2);
	}
	else if (nextPosX >= winSize.width - ballSize.width / 2)
	{
		vx *= -1;
		this->setPositionX(winSize.width - ballSize.width / 2);
	}
	if (nextPosY <= ballSize.height/2)
	{
		vy *= -1;
		this->setPositionY(ballSize.height/2);
	}
	else if (nextPosY >= winSize.height - ballSize.height /2 )
	{
		vy *= -1;
		this->setPositionY(winSize.height - ballSize.height / 2);
	}
}

void Ball::destory()
{
	this->removeFromParent(); //将显示对象本身从父容器当中直接删除
}
void Ball::rebound()
{
	vx *= -1;
	vy *= -1;
}
void Ball::setisHited(bool bl)
{
	isHited = bl;
	if (bl)
	{
		this->scheduleOnce(SEL_SCHEDULE(&Ball::resetCanHit),0.55f);
	}
}
bool Ball::getisHited() const
{
	return isHited;
}
void Ball::resetCanHit(float dt)
{
	isHited = false;
}
