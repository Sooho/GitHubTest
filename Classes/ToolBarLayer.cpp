#include "cocos2d.h"
#include "WordCardConfigure.h"
#include "WordCardScene.h"
#include "ToolBarLayer.h"
#include "MenuScene.h"
#include "MyPageScene.h"

USING_NS_CC;

WordCardScene* ToolBarLayer::m_parentWordCardScene = NULL;
MyPageScene* ToolBarLayer::m_parentMyPageScene = NULL;

// on "init" you need to initialize your instance
bool ToolBarLayer::init()
{
	if ( !LayerColor::initWithColor(Color4B::WHITE))
	{
        return false;
    }

	this->setContentSize(Size(WordCardConfigure::m_screenSize.width, WordCardConfigure::TOOL_BAR_HEIGHT));

    m_sprBack = Sprite::create(ICON_BACK);
    m_sprBack->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN + WordCardConfigure::ICON_HEIGHT/2, WordCardConfigure::TOOL_BAR_HEIGHT/2));
    m_sprBack->setScaleX(WordCardConfigure::ICON_HEIGHT/ m_sprBack->getContentSize().width);
    m_sprBack->setScaleY(WordCardConfigure::ICON_HEIGHT/ m_sprBack->getContentSize().height);
 	this->addChild(m_sprBack, 1);

 	m_sprArchive = Sprite::create(ICON_ARCHIRVE);
 	m_sprArchive->setPosition(Vec2(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN - WordCardConfigure::ICON_HEIGHT/2, WordCardConfigure::TOOL_BAR_HEIGHT/2));
 	m_sprArchive->setScaleX(WordCardConfigure::ICON_HEIGHT/ m_sprArchive->getContentSize().width);
 	m_sprArchive->setScaleY(WordCardConfigure::ICON_HEIGHT/ m_sprArchive->getContentSize().height);
 	this->addChild(m_sprArchive, 1);

    m_sprFavorite = Sprite::create(ICON_FAVORTIE_WORD);
    m_sprFavorite->setPosition(Vec2(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN *2 - WordCardConfigure::ICON_HEIGHT - WordCardConfigure::ICON_HEIGHT/2, WordCardConfigure::TOOL_BAR_HEIGHT/2));
    m_sprFavorite->setScaleX(WordCardConfigure::ICON_HEIGHT/ m_sprFavorite->getContentSize().width);
    m_sprFavorite->setScaleY(WordCardConfigure::ICON_HEIGHT/ m_sprFavorite->getContentSize().height);
 	this->addChild(m_sprFavorite, 1);

	this->setTouchEnabled(true);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(ToolBarLayer::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

    return true;
}


bool ToolBarLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = touch->getStartLocation();
    //CCLOG("ToolBarLayer (pos.x:%f, pox.y:%f) \n", pos.x, pos.y);

	if (!this->getBoundingBox().containsPoint(pos))
	{
	   // CCLOG("[ERROR] ToolBarLayer, Out of bounds! (pos.x:%f, pox.y:%f) \n", pos.x, pos.y);
	    return false;
	}

	Point relativePos = Point(pos.x, pos.y - (WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT));
	if (m_sprBack->getBoundingBox().containsPoint(relativePos))
	{
		CCLOG("m_sprBack has been clicked!!");
		_goBack();
	}
	else if (m_sprFavorite->getBoundingBox().containsPoint(relativePos))
	{
		CCLOG("m_sprFavorite has been clicked!!");
		_goFavorite();
	}
	else if (m_sprArchive->getBoundingBox().containsPoint(relativePos))
	{
		CCLOG("m_sprArchive has been clicked!!");
		_goAchive();
	}
	else
	{
		CCLOG("Out of icons has been clicked!!");
	}

	return true;
}

void ToolBarLayer::_goBack(void)
{
	switch (m_contextLayer)
	{
	case STATUS_WORD_CARD_TITLE:
		CCLOG("ToolBarLayer::_goBack(void), context: STATUS_WORD_CARD_TITLE");
		Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
		delete m_parentWordCardScene->m_wordCard;
		CCLOG("m_parentWordCardScene->m_wordCard is deleted.\n");
		Director::getInstance()->replaceScene(MenuScene::create());
		break;

	case STATUS_WORD_CARD:
		CCLOG("ToolBarLayer::_goBack(void), context: STATUS_WORD_CARD");
		m_parentWordCardScene->goBackToWordCardTitle();
		break;

	case STATUS_MY_PAGE_MENU:
		CCLOG("ToolBarLayer::_goBack(void), context: STATUS_MY_PAGE_MENU");
		Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
		Director::getInstance()->replaceScene(MenuScene::create());
		break;

	default:
		CCLOG("ToolBarLayer::_goBack(void)");
	}

}

void ToolBarLayer::setContext(int context)
{
	m_contextLayer = context;

	switch (m_contextLayer)
	{
	case STATUS_WORD_CARD_TITLE:
	case STATUS_WORD_CARD_ENDING:
	case STATUS_MY_PAGE_MENU:
		CCLOG("ToolBarLayer::setContext(void), context: STATUS_WORD_CARD_TITLE");
		m_sprFavorite->setVisible(false);
		m_sprArchive->setVisible(false);

		break;

	case STATUS_WORD_CARD:
		CCLOG("ToolBarLayer::_goBack(void), context: STATUS_WORD_CARD");
		m_sprFavorite->setVisible(true);
		m_sprArchive->setVisible(true);
		break;

	default:
		CCLOG("ToolBarLayer::_goBack(void)");
	}

}

void ToolBarLayer::setParentWordCardScene(WordCardScene* parent)
{
	if (NULL == m_parentWordCardScene)
		m_parentWordCardScene = parent;
}

void ToolBarLayer::setParentMyPageScene(MyPageScene* parent)
{
	if (NULL == m_parentMyPageScene)
		m_parentMyPageScene = parent;
}

void ToolBarLayer::_goFavorite(void)
{
	m_parentWordCardScene->m_currentWordCardLayer->addMyWord();
}


void ToolBarLayer::_goAchive(void)
{
	m_parentWordCardScene->m_currentWordCardLayer->addArchive();
}

