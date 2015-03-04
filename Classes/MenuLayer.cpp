#include <string>
#include "cocos2d.h"
#include "MenuLayer.h"
#include "WordCardScene.h"
#include "MenuScene.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MenuLayer::init()
{
    //////////////////////////////
    // 1. super init first

    if ( !LayerColor::initWithColor(Color4B::WHITE) )
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add nodes
    m_label = LabelTTF::create("Where are you now?", "", 48,
    						Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 48 * 4),  TextHAlignment::CENTER, TextVAlignment::BOTTOM);
    m_label->setAnchorPoint(Point(0,0));
    m_label->setPosition(Vec2(0, this->getContentSize().height - 48 * 4));
    m_label->setColor(Color3B::BLACK);
    this->addChild(m_label, 1);

    // add lesson picture
	m_sprLesson = Sprite::create("lessons/cafe.jpg");
	m_sprLesson->setPosition(Vec2( WordCardConfigure::m_screenSize.width/2, WordCardConfigure::m_screenSize.height/2));
	m_sprLesson->setScaleX( (WordCardConfigure::m_screenSize.width/3)/ m_sprLesson->getContentSize().width);
	m_sprLesson->setScaleY( (WordCardConfigure::m_screenSize.width/3)/ m_sprLesson->getContentSize().height);
	this->addChild(m_sprLesson, 1);

    auto l_lessonName = LabelTTF::create("Cafe", "", 32,
    						Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 32 * 1.5),  TextHAlignment::CENTER, TextVAlignment::BOTTOM);
    l_lessonName->setAnchorPoint(Point(0,0));
    l_lessonName->setPosition(Vec2(0, this->getContentSize().height/2 - m_sprLesson->getContentSize().height/2 - 32 * 1.5));
    l_lessonName->setColor(Color3B::ORANGE);
    this->addChild(l_lessonName, 1);

	this->setTouchEnabled(true);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(MenuLayer::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

    return true;
}


bool MenuLayer::onTouchBegan(Touch* touch, Event* event) {


	if (m_sprLesson->getBoundingBox().containsPoint(touch->getStartLocation()))
	{
		CCLOG("m_sprLesson has been clicked!!");
		int firstLessonId = 1;
		_goToWordCardScene(firstLessonId);
	}
	else
		CCLOG("Out of m_sprLesson has been clicked!!");

    return true;
}


void MenuLayer::goHelp(Object* pSender)
{
	//CCLOG("")
	m_label->setString("goHelp()");
}

void MenuLayer::goPlay(Object* pSender)
{

}

void MenuLayer::goQuit(Object* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void MenuLayer::_goToWordCardScene(int lessonId)
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = WordCardScene::createWordCardScene(lessonId);
	auto pScene = TransitionFade::create(0.5f, hScene);

	Director::getInstance()->replaceScene(pScene);
}
