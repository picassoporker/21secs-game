#include "InGameLayer.h"
#include "gameLayer/GameOver.h"
USING_NS_CC;
int* InGameLayer::score = new int(4);
InGameLayer::InGameLayer(void) : ballList(), timeCount(0), timeTxt(NULL),touchBallList(),yBall(NULL),isTouched(false)
{
}

InGameLayer::~InGameLayer(void)
{
}
bool InGameLayer::init()
{
	Layer::init();
	//获取屏幕宽度大小
	Size winSize				= Director::getInstance()->getVisibleSize();
	Size ballSize			    = this->getContentSize();
	//创建背景图
	Sprite* background = Sprite::create("backMain.jpg");
	this->addChild(background);
	background->setAnchorPoint(Point::ZERO);
	//创建黄色球
	yBall						= Sprite::create("mouse_1.png");
	this->addChild(yBall);
	yBall->setPosition(winSize.width - 100,winSize.height - 500);	
	//创建时间计时文本
	char chTxt[1024];
	sprintf(chTxt,"%d",timeCount);
	timeTxt					= LabelAtlas::create(chTxt,"farAwayCount_38x45.png", 38,45,'0');
	this->addChild(timeTxt);
	timeTxt->setPosition(10,winSize.height - timeTxt->getContentSize().height);
	//创建小球
	createBalls(50);
	//添加侦听
	addEvents();
	//添加播放暂停按钮
	MenuItemImage* pauseItem = MenuItemImage::create(	"pause.png","pause.png",
																								CC_CALLBACK_1(InGameLayer
																								::pauseCallBack,this));
	pauseMenu  = Menu::create(pauseItem,NULL);
	this->addChild(pauseMenu,1);
	pauseMenu->setPosition(winSize.width - 100,winSize.height - 40);

	MenuItemImage* replayItem = MenuItemImage::create(	"play.png","play.png",
																								CC_CALLBACK_1(InGameLayer
																								::replayCallBack,this));
	Menu* replayMenu					= Menu::create(replayItem,NULL);
	this->addChild(replayMenu,1);
	replayMenu->setPosition(winSize.width - 50,winSize.height - 40);
	//遮造物
	Sprite* mask							=	Sprite::create("progressBar1.png");
	//被遮物
	timeBar									=	Sprite::create("progressBar.png");
	ClippingNode* clip					=  ClippingNode::create(mask);
	clip->addChild(timeBar);
	this->addChild(clip);
	clip->setPosition(winSize.width / 2,winSize.height - 15);

	
	
	return true;
}

Scene* InGameLayer::createScene()
{
	Scene* sc = Scene::create();
	InGameLayer* ly = InGameLayer::create();
	sc->addChild(ly);
	return sc;
}
void InGameLayer::createBalls(int count)
{
	Ball* mBall = NULL;
	for (int i = 0; i < count; i++)
	{
		mBall = Ball::create();
		this->addChild(mBall,1); //放到第一层
		mBall->setPosition(CCRANDOM_0_1() * 800 , CCRANDOM_0_1() * 800 );
		ballList.pushBack(mBall);
	}
}
void InGameLayer::moveAllBalls(float dt)
{
	Ball* mBall = NULL;
	for (int i = 0; i < ballList.size(); i++)
	{
		mBall = ballList.at(i);
		mBall->move();
		mBall->setRotation(mBall->getRotation() + 10);
	}
	hitTest();
	eachotherHit();
}
void InGameLayer::hitTest()
{
	Ball* first = NULL;
	Ball* next = NULL;
	for (int i = 0; i < ballList.size(); i++)
	{
		first = ballList.at(i);
		for (int j = i + 1; j < ballList.size(); j++)
		{
			next = ballList.at(j);
			if (getDistance(first, next) <= 60 && !first->getisHited() && !next->getisHited() )
			{
				first->rebound();
				first->setisHited(true);
				next->rebound();
				next->setisHited(true);
			}
		}
	}
}
float InGameLayer::getDistance(Node* a, Node* b)
{
	Point ds = a->getPosition() - b->getPosition();
	return sqrt(ds.x* ds.x + ds.y * ds.y);
}
float InGameLayer::getDistance(Point a, Point b)
{
	Point pos = a - b;
	return sqrt(pos.x * pos.x + pos.y * pos.y);
}
void InGameLayer::addEvents()
{
	EventListenerTouchOneByOne* touchEvt  = EventListenerTouchOneByOne::create();
	touchEvt->onTouchBegan				  = CC_CALLBACK_2(InGameLayer::onTouchBegan, this);
	touchEvt->onTouchMoved				= CC_CALLBACK_2(InGameLayer::onTouchMoved,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvt, this);
}
bool InGameLayer::onTouchBegan(Touch *touch,Event *unused_event)
{
	return true;
}
void InGameLayer::onTouchMoved(Touch * touch, Event *unused_event)
{
	if (isTouched)
	{
		return ;
	}
	Point pos = touch->getLocation();
	if (getDistance(pos,yBall->getPosition()) <= 100 )
	{
		yBall->setPosition(touch->getLocation());
	}
}
void InGameLayer::eachotherHit()
{
	Ball* next = NULL;
	for (int i = 0; i < ballList.size(); i++)
	{
			next = ballList.at(i);
			if (getDistance(yBall, next) <= 60)
			{
				Director::getInstance()->replaceScene(TransitionMoveInT::create(0.5f, GameOver::createScene()));
				score = &timeCount;
				ballList.clear();
			}
	}
}
void InGameLayer::timeFunCount(float dt)
{
	timeCount++;
	char a[1024];
	sprintf(a,"%d",timeCount);
	timeTxt->setString(a);

	float w		=	timeBar->getContentSize().width;
	timeBar->setPositionX(timeBar->getPositionX() - w  / 21);
	if(timeBar->getPositionX() <= -w)
	{
		ballList.clear();
		Director::getInstance()->replaceScene(TransitionMoveInT::create(0.5f, GameOver::createScene()));
	}
}
void InGameLayer::replayCallBack(Ref* sender)
{
	isTouched = false;
	this->schedule(SEL_SCHEDULE(&InGameLayer::moveAllBalls),0.02f);
	this->schedule(SEL_SCHEDULE(&InGameLayer::timeFunCount),1.0f);

}
void InGameLayer::pauseCallBack(Ref* sender)
{
	isTouched = true;
	this->unscheduleAllSelectors();
}
void InGameLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	//时间步进器
	this->schedule(SEL_SCHEDULE(&InGameLayer::moveAllBalls),0.02f);
	//添加文本计时步进器
	this->schedule(SEL_SCHEDULE(&InGameLayer::timeFunCount),1.0f);
}
