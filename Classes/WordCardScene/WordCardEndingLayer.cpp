#include <string>
#include "cocos2d.h"
#include "WordCardConfigure.h"
#include "WordCardEndingLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

WordCardScene* WordCardEndingLayer::m_parentScene = NULL;

// on "init" you need to initialize your instance
bool WordCardEndingLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B::YELLOW) )
    {
        return false;
    }

    this->setContentSize(Size(WordCardConfigure::m_screenSize.width, WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT - WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT));

	////////////////////////////////
	// add Word
	CCLOG("m_parentScene->m_wordCard->getLessonTitle():%s\n", m_parentScene->m_wordCard->getLessonTitle().c_str());
	m_lblEnding = LabelTTF::create(m_parentScene->m_wordCard->getLessonEndingText(),  "Arial", 72,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 72 * 6),  TextHAlignment::CENTER, TextVAlignment::CENTER);
	m_lblEnding->setPosition(Vec2(WordCardConfigure::m_screenSize.width/2, this->getContentSize().height/2));
	m_lblEnding->setColor(Color3B::WHITE);
	this->addChild(m_lblEnding, 1);

	// add Picture
	std::string l_lessonEndingPicture = m_parentScene->m_wordCard->m_folderPath + m_parentScene->m_wordCard->getLessonEndingPicture();

	CCLOG("l_lessonEndingPicture:%s\n", l_lessonEndingPicture.c_str());

	m_sprPicture = Sprite::create(l_lessonEndingPicture);
	m_sprPicture->setAnchorPoint(Point(0,0));
	m_sprPicture->setPosition(Vec2(0, 0));

	m_sprPicture->setScaleX(WordCardConfigure::m_screenSize.width/m_sprPicture->getContentSize().width);
	m_sprPicture->setScaleY((WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT - WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT)/m_sprPicture->getContentSize().height);

	this->addChild(m_sprPicture, 0);

   /////////////////////////////
    // 2. init listener
	this->setTouchEnabled(true);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(WordCardEndingLayer::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
	return true;
}

void WordCardEndingLayer::setParentScene(WordCardScene* parent)
{
//	if (NULL == m_parentScene)
		m_parentScene = parent;
}


bool WordCardEndingLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = touch->getStartLocation();
    CCLOG("WordCardTitleLayer (pos.x:%f, pox.y:%f) \n", pos.x, pos.y);

	if (!this->getBoundingBox().containsPoint(pos))
	{
	    CCLOG("[ERROR] WordCardTitleLayer, Out of bounds! (pos.x:%f, pox.y:%f) \n", pos.x, pos.y);
	    return false;
	}

	CCLOG("m_sprHome has been clicked!!");
	//_goQuizeScene();


    return true;
}

void WordCardEndingLayer::_goQuizeScene(void)
{
	CCLOG("WordCardEndingLayer::_goQuizeScene\n");
}

