#include <string>
#include "cocos2d.h"
#include "MyPageScene.h"
#include "MyPageMenuLayer.h"
#include "WordCardConfigure.h"

USING_NS_CC;

MyPageScene* MyPageMenuLayer::m_parentScene = NULL;

// on "init" you need to initialize your instance
bool MyPageMenuLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B::WHITE) )
    {
        return false;
    }
    this->setContentSize(Size(WordCardConfigure::m_screenSize.width, WordCardConfigure::TOOL_BAR_HEIGHT * 1.5));
    
    /////////////////////////////
    // 2. add nodes

    m_label = LabelTTF::create("My level is .....", "", 32,
    						Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 40 * 2),  TextHAlignment::LEFT, TextVAlignment::TOP);
    m_label->setAnchorPoint(Point(0, 0));
    m_label->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN, this->getContentSize().height - 40 * 2));
    m_label->setColor(Color3B::BLACK);
    this->addChild(m_label, 0);

    int l_menuIconHeight = WordCardConfigure::ICON_HEIGHT * 1.5;
    // add lesson picture
    m_sprMyWord = Sprite::create(ICON_FAVORTIE_WORD);
    m_sprMyWord->setAnchorPoint(Point(0,0));
    m_sprMyWord->setPosition(Vec2(this->getContentSize().width/2 - l_menuIconHeight/2 - WordCardConfigure::LEFT_MARGIN*2 - l_menuIconHeight*2,
    							this->getContentSize().height - 40*2 - l_menuIconHeight));
    m_sprMyWord->setScaleX(l_menuIconHeight/ m_sprMyWord->getContentSize().width);
    m_sprMyWord->setScaleY(l_menuIconHeight/ m_sprMyWord->getContentSize().height);
	this->addChild(m_sprMyWord, 1);

    // add m_sprArchive picture
	m_sprArchive = Sprite::create(ICON_ARCHIRVE);
	m_sprArchive->setAnchorPoint(Point(0,0));
	m_sprArchive->setPosition(Vec2(this->getContentSize().width/2 - l_menuIconHeight/2,
								this->getContentSize().height - 40*2 - l_menuIconHeight));
	m_sprArchive->setScaleX(l_menuIconHeight/ m_sprArchive->getContentSize().width);
	m_sprArchive->setScaleY(l_menuIconHeight/ m_sprArchive->getContentSize().height);
	this->addChild(m_sprArchive, 1);

    // add lesson picture
	m_sprRecord = Sprite::create(ICON_RECORD);
	m_sprRecord->setAnchorPoint(Point(0,0));
	m_sprRecord->setPosition(Vec2(this->getContentSize().width/2 + l_menuIconHeight/2 + WordCardConfigure::LEFT_MARGIN + l_menuIconHeight,
								this->getContentSize().height - 40*2 - l_menuIconHeight));
	m_sprRecord->setScaleX(l_menuIconHeight / m_sprRecord->getContentSize().width);
	m_sprRecord->setScaleY(l_menuIconHeight / m_sprRecord->getContentSize().height);
	this->addChild(m_sprRecord, 1);

	this->setTouchEnabled(true);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(MyPageMenuLayer::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

    return true;
}


bool MyPageMenuLayer::onTouchBegan(Touch* touch, Event* event) {
	//CCLOG("MyPageMenuLayer::onTouchBegan has been clicked!!\n");
	Point pos = touch->getStartLocation();
	if (!this->getBoundingBox().containsPoint(pos))
	{
	    //CCLOG("[ERROR] MyPageMenuLayer, Out of bounds! (pos.x:%f, pox.y:%f) \n", pos.x, pos.y);
	    return false;
	}

	Point relativePos = Point(pos.x, pos.y - (WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT - WordCardConfigure::TOOL_BAR_HEIGHT*1.5));

	if (m_sprMyWord->getBoundingBox().containsPoint(relativePos))
	{
		goMyWord();
	}
	else if (m_sprArchive->getBoundingBox().containsPoint(relativePos))
	{
		goArchive();
	}
	else if (m_sprRecord->getBoundingBox().containsPoint(relativePos))
	{
		goRecord();
	}
	else
		CCLOG("Out of m_sprLesson has been clicked!\n");

    return true;
}


void MyPageMenuLayer::goMyWord(void)
{
	CCLOG(" MyPageMenuLayer::goMyWord() called \n");
	m_parentScene->showMyWordLayer();
}

void MyPageMenuLayer::goArchive(void)
{
	CCLOG(" MyPageMenuLayer::goArchive() called \n");
	m_parentScene->showArchiveLayer();
}

void MyPageMenuLayer::goRecord(void)
{
	CCLOG(" MyPageMenuLayer::goRecord() called \n");
	m_parentScene->showRecordLayer();
}

void MyPageMenuLayer::setParentScene(MyPageScene* parent)
{
	//if (NULL == m_parentScene)
		m_parentScene = parent;
}


//void MyPageMenuLayer::changeWordCardScene(int lessonId)
//{
//	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
//
//	auto hScene = WordCardScene::createWordCardScene(lessonId);
//	auto pScene = TransitionFade::create(0.5f, hScene);
//
//	Director::getInstance()->replaceScene(pScene);
//}
