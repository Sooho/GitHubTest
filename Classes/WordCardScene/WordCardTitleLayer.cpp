#include <string>
#include "cocos2d.h"
#include "WordCardConfigure.h"
#include "WordCardTitleLayer.h"
#include "WordCardLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

WordCardScene* WordCardTitleLayer::m_parentScene = NULL;

// on "init" you need to initialize your instance
bool WordCardTitleLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B::YELLOW) )
    {
        return false;
    }

    this->setContentSize(Size(WordCardConfigure::m_screenSize.width, WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT - WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT));

	////////////////////////////////
	// add Word

    CCLOG("&m_parentScene->m_wordCard:%x", &m_parentScene->m_wordCard);
    CCLOG("m_parentScene->m_wordCard:%x", m_parentScene->m_wordCard);
    std::string l_lessonTitle =  m_parentScene->m_wordCard->getLessonTitle();
	CCLOG("m_parentScene->m_wordCard->getLessonTitle():%s\n", l_lessonTitle.c_str());
    m_lblTitle = LabelTTF::create(m_parentScene->m_wordCard->getLessonTitle(),  "Arial", 80,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 80 * 1.5),  TextHAlignment::RIGHT, TextVAlignment::CENTER);
    m_lblTitle->setAnchorPoint(Point(0,0));
    m_lblTitle->setPosition(Vec2(0, 80 * 1.5));
    m_lblTitle->setColor(Color3B::WHITE);
	this->addChild(m_lblTitle, 1);

	// add Picture
	std::string l_lessonTitlePicture = m_parentScene->m_wordCard->m_folderPath + m_parentScene->m_wordCard->getLessonTitlePicture();

	CCLOG("l_lessonTitlePicture:%s\n", l_lessonTitlePicture.c_str());

	m_sprPicture = Sprite::create(l_lessonTitlePicture);
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
	m_listener->onTouchBegan = CC_CALLBACK_2(WordCardTitleLayer::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

	return true;
}

void WordCardTitleLayer::setParentScene(WordCardScene* parent)
{
	CCLOG("setParentScene() before: m_parentScene=%x, parent=%x \n", m_parentScene, parent);
//	if (NULL == m_parentScene)
		m_parentScene = parent;
}


bool WordCardTitleLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = touch->getStartLocation();
    CCLOG("WordCardTitleLayer (pos.x:%f, pox.y:%f) \n", pos.x, pos.y);

	if (!this->getBoundingBox().containsPoint(pos))
	{
	    CCLOG("[ERROR] WordCardTitleLayer, Out of bounds! (pos.x:%f, pox.y:%f) \n", pos.x, pos.y);
	    return false;
	}

	CCLOG("WordCardTitleLayer has been clicked!!");
	_goWordCard();

    return true;
}

void WordCardTitleLayer::_goWordCard(void)
{
	/// current word card  layer
	int l_firstWordId = m_parentScene->m_wordCard->getFirstWordId();

	m_parentScene->m_currentWordCardLayer->setZOrder(1);
	m_parentScene->m_currentWordCardLayer->focusCurrentLayer();
	m_parentScene->m_nextWordCardLayer->setZOrder(1);
	m_parentScene->m_prevWordCardLayer->setZOrder(1);
	m_parentScene->m_wordCardTitleLayer->setZOrder(0);
	m_parentScene->m_wordCardEndingLayer->setZOrder(0);

	m_parentScene->m_toolBarLayer->setContext(STATUS_WORD_CARD);

}

