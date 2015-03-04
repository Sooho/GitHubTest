#include "cocos2d.h"
#include "WordCardConfigure.h"
#include "ToolBarBottomLayer.h"
#include "MenuScene.h"
#include "MyPageScene.h"
#include "WordCardScene.h"
#include "SettingScene.h"

USING_NS_CC;

WordCardScene* ToolBarBottomLayer::m_parentWordCardScene = NULL;
MyPageScene* ToolBarBottomLayer::m_parentMyPageScene = NULL;


// on "init" you need to initialize your instance
bool ToolBarBottomLayer::init()
{
	if ( !LayerColor::initWithColor(Color4B::WHITE))
	{
        return false;
    }

	this->setContentSize(Size(WordCardConfigure::m_screenSize.width, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT));

    m_sprHome = Sprite::create(ICON_HOME);
    m_sprHome->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN + WordCardConfigure::ICON_HEIGHT/2, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT/2));
    m_sprHome->setScaleX(WordCardConfigure::ICON_HEIGHT/ m_sprHome->getContentSize().width);
    m_sprHome->setScaleY(WordCardConfigure::ICON_HEIGHT/ m_sprHome->getContentSize().height);
 	this->addChild(m_sprHome, 1);

 	m_sprMyPage = Sprite::create(ICON_MY_PAGE);
 	m_sprMyPage->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN *2 + WordCardConfigure::ICON_HEIGHT + WordCardConfigure::ICON_HEIGHT/2, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT/2));
 	m_sprMyPage->setScaleX(WordCardConfigure::ICON_HEIGHT/ m_sprMyPage->getContentSize().width);
 	m_sprMyPage->setScaleY(WordCardConfigure::ICON_HEIGHT/ m_sprMyPage->getContentSize().height);
 	this->addChild(m_sprMyPage, 1);

    m_sprSettings = Sprite::create(ICON_SETTING);
    m_sprSettings->setPosition(Vec2(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN - WordCardConfigure::ICON_HEIGHT/2, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT/2));
    m_sprSettings->setScaleX(WordCardConfigure::ICON_HEIGHT/ m_sprSettings->getContentSize().width);
    m_sprSettings->setScaleY(WordCardConfigure::ICON_HEIGHT/ m_sprSettings->getContentSize().height);
 	this->addChild(m_sprSettings, 1);

	this->setTouchEnabled(true);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(ToolBarBottomLayer::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

    return true;
}


bool ToolBarBottomLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = touch->getStartLocation();
    //CCLOG("ToolBarBottomLayer (pos.x:%f, pox.y:%f) \n", pos.x, pos.y);

	if (!this->getBoundingBox().containsPoint(pos))
	{
	    //CCLOG("[ERROR] ToolBarBottomLayer, Out of bounds! (pos.x:%f, pox.y:%f) \n", pos.x, pos.y);
	    return false ;
	}

	Point relativePos = pos;
	if (m_sprHome->getBoundingBox().containsPoint(relativePos))
	{
		CCLOG("m_sprHome has been clicked!!");
		_goHome();
	}
	else if (m_sprSettings->getBoundingBox().containsPoint(relativePos))
	{
		CCLOG("m_sprSettings has been clicked!!");
		_goSettings();
	}
	else if (m_sprMyPage->getBoundingBox().containsPoint(relativePos))
	{
		CCLOG("m_sprMyPage has been clicked!!");
		_goMyPage();
	}
	else
	{
		CCLOG("Out of icons has been clicked!!");
	}

    return true;
}

void ToolBarBottomLayer::_goHome(void)
{
	switch (m_contextLayer)
	{
	case STATUS_MY_PAGE_MENU:
		CCLOG("ToolBarBottomLayer::_goHome, STATUS_MY_PAGE_MENU\n");
		//delete m_parentMyPageScene->m_myPageValue;
		CCLOG("m_parentMyPageScene->m_myPageValue is deleted.\n");
		break;

	case STATUS_WORD_CARD_TITLE:
	case STATUS_WORD_CARD_ENDING:
	case STATUS_WORD_CARD:
		CCLOG("ToolBarBottomLayer::_goHome, STATUS_WORD_CARD\n");
		delete m_parentWordCardScene->m_wordCard;
		CCLOG("m_parentWordCardScene->m_wordCard is deleted.\n");
		break;

	default:
		CCLOG("ToolBarLayer::setContext(void)");
	}

	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = MenuScene::create();
	auto pScene = TransitionFade::create(0.5f, hScene);

	Director::getInstance()->replaceScene(pScene);
}


void ToolBarBottomLayer::_goMyPage(void)
{
	CCLOG("ToolBarBottomLayer::_goMyPage\n");

	delete m_parentWordCardScene->m_wordCard;
	CCLOG("m_parentWordCardScene->m_wordCard is deleted.\n");

	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	auto hScene = MyPageScene::create();
	auto pScene = TransitionFade::create(0.5f, hScene);

	Director::getInstance()->replaceScene(pScene);
}


void ToolBarBottomLayer::_goSettings(void)
{
	CCLOG("ToolBarBottomLayer::_goSettings\n");

	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	auto hScene = SettingScene::createSettingScene();
	auto pScene = TransitionFade::create(0.5f, hScene);

	Director::getInstance()->replaceScene(pScene);
}


void ToolBarBottomLayer::setContext(int context)
{
	m_contextLayer = context;

	switch (m_contextLayer)
	{
	case STATUS_MY_PAGE_MENU:
		CCLOG("ToolBarLayer::setContext(void), context: STATUS_MY_PAGE_MENU");
		m_sprMyPage->setVisible(false);

		break;

	case STATUS_WORD_CARD_TITLE:
	case STATUS_WORD_CARD_ENDING:
	case STATUS_WORD_CARD:
		CCLOG("ToolBarLayer::_goBack(void), context: STATUS_WORD_CARD_TITLE, STATUS_WORD_CARD_ENDING, STATUS_WORD_CARD");
		m_sprMyPage->setVisible(true);
		break;

	default:
		CCLOG("ToolBarLayer::setContext(void)");
	}

}

void ToolBarBottomLayer::setParentWordCardScene(WordCardScene* parent)
{
	if (NULL == m_parentWordCardScene)
		m_parentWordCardScene = parent;
}

void ToolBarBottomLayer::setParentMyPageScene(MyPageScene* parent)
{
	if (NULL == m_parentMyPageScene)
		m_parentMyPageScene = parent;
}

