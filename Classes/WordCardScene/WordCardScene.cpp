#include "cocos2d.h"

#include "MenuScene.h"
#include "WordCard.h"
#include "WordCardLayer.h"
#include "WordCardEndingLayer.h"
#include "WordCardTitleLayer.h"
#include "WordCardConfigure.h"
#include "WordCardScene.h"
#include "ToolBarLayer.h"
#include "ToolBarBottomLayer.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool WordCardScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    m_wordCard= NULL;

    return true;
}

WordCardScene* WordCardScene::createWordCardScene(int lessonId)
{
	auto scene = WordCardScene::create();

	// create wordCards for the lessonId from json data
	scene->m_wordCard = new WordCard(lessonId);
	CCLOG("scene->m_wordCard:%x\n", scene->m_wordCard);
	scene->m_wordCard->print();

	// add toolbar
	ToolBarLayer::setParentWordCardScene(scene);
	CCLOG("scene->m_wordCard:%x1\n", scene->m_wordCard);
	scene->m_toolBarLayer = ToolBarLayer::create();
	CCLOG("scene->m_wordCard:%x2\n", scene->m_wordCard);
	scene->m_toolBarLayer->setAnchorPoint(Point(0,0));
	scene->m_toolBarLayer->setPosition(Point(0, WordCardConfigure::m_screenSize.height- WordCardConfigure::TOOL_BAR_HEIGHT));
	scene->m_toolBarLayer->setContext(STATUS_WORD_CARD_TITLE);
	scene->addChild(scene->m_toolBarLayer, 1);

	// add toolbarbottom
	ToolBarBottomLayer::setParentWordCardScene(scene);
	CCLOG("scene->m_wordCard:%x3\n", scene->m_wordCard);
	scene->m_toolBarBottomLayer = ToolBarBottomLayer::create();
	CCLOG("scene->m_wordCard:%x4\n", scene->m_wordCard);
	scene->m_toolBarBottomLayer->setAnchorPoint(Point(0,0));
	scene->m_toolBarBottomLayer->setPosition(Point(0, 0));
	scene->addChild(scene->m_toolBarBottomLayer, 1);

	// add word card title for the lessonId
	CCLOG("m_wordCardTitleLayer\n");
	CCLOG("scene->m_wordCard:%x5\n", scene->m_wordCard);
	WordCardTitleLayer::setParentScene(scene);
	CCLOG("scene->m_wordCard:%x6\n", scene->m_wordCard);
	CCLOG("scene->m_wordCard:%x6\n", scene->m_wordCard);
	CCLOG("m_wordCardTitleLayer2\n");
	scene->m_wordCardTitleLayer = WordCardTitleLayer::create();
	CCLOG("m_wordCardTitleLayer3\n");
	scene->m_wordCardTitleLayer->setAnchorPoint(Point(0,0));
	CCLOG("m_wordCardTitleLayer4\n");
	scene->m_wordCardTitleLayer->setPosition(Point(0, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT));
	CCLOG("m_wordCardTitleLayer5\n");
	scene->addChild(scene->m_wordCardTitleLayer, 1);

	// add word card ending
	CCLOG("m_wordCardEndingLayer\n");
	WordCardEndingLayer::setParentScene(scene);
	scene->m_wordCardEndingLayer = WordCardEndingLayer::create();
	scene->m_wordCardEndingLayer->setAnchorPoint(Point(0,0));
	scene->m_wordCardEndingLayer->setPosition(Point(0, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT));
	scene->addChild(scene->m_wordCardEndingLayer, 0);

	// add current word card
	CCLOG("m_currentWordCardLayer\n");
	WordCardLayer::setParentScene(scene);
	scene->m_currentWordCardLayer = WordCardLayer::create();
	scene->m_currentWordCardLayer->setAnchorPoint(Point(0,0));
	scene->m_currentWordCardLayer->setPosition(scene->getCurrentWordCardLayerPosition());
	int l_firstWordId = scene->m_wordCard->getFirstWordId();
	scene->m_currentWordCardLayer->setWordCardValue(l_firstWordId);
	scene->addChild(scene->m_currentWordCardLayer, 0);

	// add next word card
	CCLOG("m_nextWordCardLayer\n");
	scene->m_nextWordCardLayer = WordCardLayer::create();
	scene->m_nextWordCardLayer->setAnchorPoint(Point(0,0));
	scene->m_nextWordCardLayer->setPosition(scene->getNextWordCardLayerPosition());
	scene->m_nextWordCardLayer->setWordCardValue(scene->m_wordCard->getNextWordId(l_firstWordId));
	scene->addChild(scene->m_nextWordCardLayer, 0);

	// add prev word card
	CCLOG("m_prevWordCardLayer\n");
	scene->m_prevWordCardLayer = WordCardLayer::create();
	scene->m_prevWordCardLayer->setAnchorPoint(Point(0,0));
	scene->m_prevWordCardLayer->setPosition(scene->getPrevWordCardLayerPosition());
	scene->addChild(scene->m_prevWordCardLayer, 0);

	return scene;
}


void WordCardScene::goBackToWordCardTitle(void)
{
	// add word card title for the lessonId
	m_wordCardTitleLayer->setZOrder(1);
	m_wordCardEndingLayer->setZOrder(0);
	m_currentWordCardLayer->setZOrder(0);
	m_nextWordCardLayer->setZOrder(0);
	m_prevWordCardLayer->setZOrder(0);

	m_toolBarLayer->setContext(STATUS_WORD_CARD_TITLE);
}

void WordCardScene::setNextWordCardEnding(void)
{
	CCLOG("setNextWordCardEnding\n");
	m_nextWordCardLayer->setZOrder(0);
	m_wordCardEndingLayer->setPosition(getNextWordCardLayerPosition());
	m_wordCardEndingLayer->setZOrder(1);
}
