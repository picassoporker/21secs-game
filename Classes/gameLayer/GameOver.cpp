#include "GameOver.h"
#include "InGameLayer.h"
USING_NS_CC;

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
	//delete InGameLayer::score;
}
bool GameOver::init()
{
	Layer::init();
	//创建背景图
	Size winSize = Director::getInstance()->getVisibleSize();
	Size ballSize = this->getContentSize();
	Sprite* background = Sprite::create("backEnd.jpg");
	this->addChild(background);
	background->setAnchorPoint(Point::ZERO);

	//退出游戏按钮
	Sprite* closeSprite = Sprite::create("gameover.png");
	MenuItemSprite *closed = MenuItemSprite::create(closeSprite,NULL,NULL,
																						CC_CALLBACK_1(GameOver::closeGame,this));
	Menu* closeMenu = Menu::create(closed,NULL);
	this->addChild(closeMenu);
	closeMenu->setPosition(winSize.width*2/3,winSize.height/3);
	//重新开始游戏按钮
	Sprite* reStrart = Sprite::create("reStrart.png");
	MenuItemSprite *reStrartSprite = MenuItemSprite::create(reStrart,NULL,NULL,
		CC_CALLBACK_1(GameOver::reStrartGame,this));
	Menu* reStrartMenu = Menu::create(reStrartSprite,NULL);
	this->addChild(reStrartMenu);
	reStrartMenu->setPosition(winSize.width/3,winSize.height/3);

	//创建显示分数文本
	char ch[1233];
	sprintf(ch,"%d",*InGameLayer::score);
	LabelTTF* resScore = LabelTTF::create(ch,"WRYH",35);
	this->addChild(resScore);
	resScore->setPosition(winSize.width/5,winSize.height/5);
	return true;
}
Scene* GameOver::createScene()
{
	Scene* sc = Scene::create();
	GameOver* ly = GameOver::create();
	sc->addChild(ly);
	return sc;
}
void GameOver::closeGame(Ref* pSender)
{
	Director::getInstance()->end();	
}
void GameOver::reStrartGame(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.5f,InGameLayer::createScene()));
}
