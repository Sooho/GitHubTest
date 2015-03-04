#include <string>
#include "cocos2d.h"
#include "WordCardConfigure.h"
#include "MyPageScene.h"
#include "MyPageRecordLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

MyPageScene* MyPageRecordLayer::m_parentScene = NULL;

// on "init" you need to initialize your instance
bool MyPageRecordLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B::YELLOW) )
    {
        return false;
    }
    int l_thisHight = WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT - WordCardConfigure::TOOL_BAR_HEIGHT *1.5 - WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT ;
    this->setContentSize(Size(WordCardConfigure::m_screenSize.width, l_thisHight));

	////////////////////////////////
	// add Word
    // add title
	m_lblTitle = LabelTTF::create("My record...",  "Arial", 70,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 70 * 1.5),  TextHAlignment::LEFT, TextVAlignment::CENTER);
    m_lblTitle->setAnchorPoint(Point(0,0));
    m_lblTitle->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN, l_thisHight - 70 * 1.5));
    m_lblTitle->setColor(Color3B::BLACK);
	this->addChild(m_lblTitle, 1);

	// add my words
	auto l_label1 = LabelTTF::create("The mumber of archived words: ",  "Arial", 40,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 40 * 1.5),  TextHAlignment::LEFT, TextVAlignment::CENTER);
	l_label1->setAnchorPoint(Point(0,0));
	l_label1->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN * 3, l_thisHight - 70 * 1.5 - 40 * 1.5));
	l_label1->setColor(Color3B::BLACK);
	this->addChild(l_label1, 1);

	m_lblNumOfMyWords = LabelTTF::create("1",  "Arial", 40,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN * 2 , 40 * 1.5),  TextHAlignment::RIGHT, TextVAlignment::CENTER);
	m_lblNumOfMyWords->setAnchorPoint(Point(0,0));
	m_lblNumOfMyWords->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN, l_thisHight - 70 * 1.5 - 40 * 1.5 * 2));
	m_lblNumOfMyWords->setColor(Color3B::BLACK);
	this->addChild(m_lblNumOfMyWords, 2);

	// add archived words
	auto l_label2 = LabelTTF::create("The mumber of my words: ",  "Arial", 40,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 40 * 1.5),  TextHAlignment::LEFT, TextVAlignment::CENTER);
	l_label2->setAnchorPoint(Point(0,0));
	l_label2->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN * 3, l_thisHight - 70 * 1.5 - 40 * 1.5 * 3));
	l_label2->setColor(Color3B::BLACK);
	this->addChild(l_label2, 1);

	m_lblNumOfArchivedWords = LabelTTF::create("2",  "Arial", 40,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN * 2, 40 * 1.5),  TextHAlignment::RIGHT, TextVAlignment::CENTER);
	m_lblNumOfArchivedWords->setAnchorPoint(Point(0,0));
	m_lblNumOfArchivedWords->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN, l_thisHight - 70 * 1.5 - 40 * 1.5 * 4));
	m_lblNumOfArchivedWords->setColor(Color3B::BLACK);
	this->addChild(m_lblNumOfArchivedWords, 2);

	// add m_lblNumOfAvgReviews
	auto l_label3 = LabelTTF::create("The average of reviews",  "Arial", 40,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 40 * 1.5),  TextHAlignment::LEFT, TextVAlignment::CENTER);
	l_label3->setAnchorPoint(Point(0,0));
	l_label3->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN * 3, l_thisHight - 70 * 1.5 - 40 * 1.5 * 5));
	l_label3->setColor(Color3B::BLACK);
	this->addChild(l_label3, 2);

	m_lblNumOfAvgReviews = LabelTTF::create("3",  "Arial", 40,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN * 2, 40 * 1.5),  TextHAlignment::RIGHT, TextVAlignment::CENTER);
	m_lblNumOfAvgReviews->setAnchorPoint(Point(0,0));
	m_lblNumOfAvgReviews->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN, l_thisHight - 70 * 1.5 - 40 * 1.5 * 6));
	m_lblNumOfAvgReviews->setColor(Color3B::BLACK);
	this->addChild(m_lblNumOfAvgReviews, 2);

	// add m_lblQuizePassRate
	auto l_label4 = LabelTTF::create("Quize Pass Rate",  "Arial", 40,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 40 * 1.5),  TextHAlignment::LEFT, TextVAlignment::CENTER);
	l_label4->setAnchorPoint(Point(0,0));
	l_label4->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN * 3, l_thisHight - 70 * 1.5 - 40 * 1.5 * 7));
	l_label4->setColor(Color3B::BLACK);
	this->addChild(l_label4, 1);

	m_lblQuizePassRate = LabelTTF::create("4",  "Arial", 40,
    								Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN * 2, 40 * 1.5),  TextHAlignment::RIGHT, TextVAlignment::CENTER);
	m_lblQuizePassRate->setAnchorPoint(Point(0,0));
	m_lblQuizePassRate->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN, l_thisHight - 70 * 1.5 - 40 * 1.5 * 8));
	m_lblQuizePassRate->setColor(Color3B::BLACK);
	this->addChild(m_lblQuizePassRate, 2);

	_setRecordData();

//	// add Picture
//	std::string l_lessonTitlePicture = m_parentScene->m_wordCard->m_folderPath + m_parentScene->m_wordCard->getLessonTitlePicture();
//
//	CCLOG("l_lessonTitlePicture:%s\n", l_lessonTitlePicture.c_str());
//
//	m_sprPicture = Sprite::create(l_lessonTitlePicture);
//	m_sprPicture->setAnchorPoint(Point(0,0));
//	m_sprPicture->setPosition(Vec2(0, 0));
//
//	m_sprPicture->setScaleX(WordCardConfigure::m_screenSize.width/m_sprPicture->getContentSize().width);
//	m_sprPicture->setScaleY((WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT - WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT)/m_sprPicture->getContentSize().height);
//
//	this->addChild(m_sprPicture, 0);

   /////////////////////////////
    // 2. init listener
	this->setTouchEnabled(true);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(MyPageRecordLayer::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

	return true;
}

void MyPageRecordLayer::_setRecordData(void)
{
    m_totalRecord = m_parentScene->getTotalRecord();

    CCLOG("[%s] m_totalRecord \n", __func__);
    m_totalRecord.print();

	m_lblNumOfMyWords->setString(WordCardConfigure::numberToString(m_totalRecord.numOfMyWords).c_str());
	m_lblNumOfArchivedWords->setString(WordCardConfigure::numberToString(m_totalRecord.numOfArchivedWords).c_str());
	m_lblNumOfAvgReviews->setString(WordCardConfigure::numberToString(m_totalRecord.numOfAvgReviews).c_str());
	m_lblQuizePassRate->setString(WordCardConfigure::numberToString(m_totalRecord.quizePassRate).c_str());
}

void MyPageRecordLayer::setParentScene(MyPageScene* parent)
{
//	if (NULL == m_parentScene)
		m_parentScene = parent;
}


bool MyPageRecordLayer::onTouchBegan(Touch* touch, Event* event)
{
	CCLOG("[MyPageRecordLayer::onTouchBegan] MyPageRecordLayer has been clicked!!\n");
//	if (this->getBoundingBox().containsPoint(touch->getStartLocation()))
//	{
//		CCLOG("MyPageRecordLayer has been clicked!!");
//	}
//	else
//		CCLOG("Out of m_listMyWords has been clicked!!");

    return true;
}


