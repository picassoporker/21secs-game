#include "WelcomeLayer.h"
#include "gameLayer/InGameLayer.h"
USING_NS_CC;

WelcomeLayer::WelcomeLayer()
{
}


WelcomeLayer::~WelcomeLayer()
{
}
bool WelcomeLayer::init()
{
	Layer::init();
	Size winSize = Director::getInstance()->getVisibleSize();
	//添加背景图
	Sprite* background					    = Sprite::create("background.png");
	this->addChild(background);
	background->setAnchorPoint(Point::ZERO);
	//添加开始游戏按钮
	MenuItemImage* start = MenuItemImage::create("startnormal.png","startnormal.png",
																					 CC_CALLBACK_1(WelcomeLayer::StrartGame,
																					 this));
	Menu* StrartMenu = Menu::create(start,NULL);
	this->addChild(StrartMenu,1);
	StrartMenu->setPosition(winSize.width/2,winSize.height/2);
	return true;
}
Scene* WelcomeLayer::createScene()
{
	Scene* sc					= Scene::create();
	WelcomeLayer* ly	= WelcomeLayer::create();
	sc->addChild(ly);
	return sc;
}
void WelcomeLayer::startCallBack(Ref* sender)
{
	Director::getInstance()->replaceScene(TransitionJumpZoom::create(0.5f, InGameLayer::createScene()));
}
void WelcomeLayer::StrartGame(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.5f,InGameLayer::createScene()));

}