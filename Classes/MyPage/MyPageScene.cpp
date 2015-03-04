#include "MyPageScene.h"
#include "MyPageMenuLayer.h"
#include "ListViewLayer.h"
#include "ToolBarBottomLayer.h"
#include "ToolBarLayer.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MyPageScene::init()
{
    //////////////////////////////
    // super init first
    if ( !Scene::init() )
    {
        return false;
    }
    

    //////////////////////////////
	// create wordCards for the lessonId from json data
	m_myPageValue = MyPage::getInstance();

    /////////////////////////////
    // add Layer
    // add my word layer
    ListViewLayer::setParentScene(this);
	m_myWordLayer = ListViewLayer::createListViewLayer(MY_PAGE_TYPE_MY_WORD);
	m_myWordLayer->setAnchorPoint(Point(0,0));
	m_myWordLayer->setPosition(getCurrentLayerPosition());
	this->addChild(m_myWordLayer, 1);

	// add archive layer
	m_archieveLayer = ListViewLayer::createListViewLayer(MY_PAGE_TYPE_ARCHIVE);
	m_archieveLayer->setAnchorPoint(Point(0,0));
	m_archieveLayer->setPosition(getNextLayerPosition());
	this->addChild(m_archieveLayer,1);

	// add records layer
	MyPageRecordLayer::setParentScene(this);
	m_recordLayer = MyPageRecordLayer::create();
	m_recordLayer->setAnchorPoint(Point(0,0));
	m_recordLayer->setPosition(Point(getNextNextLayerPosition()));
	this->addChild(m_recordLayer, 0);


    // add menuLayer
	MyPageMenuLayer::setParentScene(this);
	m_myPageMenuLayer = MyPageMenuLayer::create();
	m_myPageMenuLayer->setAnchorPoint(Point(0,0));
	m_myPageMenuLayer->setPosition(Point(0,  WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT - WordCardConfigure::TOOL_BAR_HEIGHT * 1.5));
    this->addChild(m_myPageMenuLayer, 2);

    // add toolbar
	ToolBarLayer::setParentMyPageScene(this);
	m_toolBarLayer = ToolBarLayer::create();
	m_toolBarLayer->setAnchorPoint(Point(0,0));
	m_toolBarLayer->setPosition(Point(0, WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT));
	m_toolBarLayer->setContext(STATUS_MY_PAGE_MENU);
	this->addChild(m_toolBarLayer, 2);

	// add toolbarbottom
	ToolBarBottomLayer::setParentMyPageScene(this);
	m_toolBarBottomLayer = ToolBarBottomLayer::create();
	m_toolBarBottomLayer->setAnchorPoint(Point(0,0));
	m_toolBarBottomLayer->setPosition(Point(0, 0));
	m_toolBarBottomLayer->setContext(STATUS_MY_PAGE_MENU);
	this->addChild(m_toolBarBottomLayer, 2);

    return true;
}


void MyPageScene::showMyWordLayer(void)
{
	CCLOG("MyPageMenuScene::showMyWordLayer() is called. \n");

	auto actionCurrent = MoveTo::create(SLIDING_TIME, getCurrentLayerPosition());
	m_myWordLayer->runAction(actionCurrent);
	m_myWordLayer->setZOrder(1);
	m_myWordLayer->refreshListViewData();

	auto actionNext = MoveTo::create(SLIDING_TIME, getNextLayerPosition());
	m_archieveLayer->runAction(actionNext);
	m_archieveLayer->setZOrder(0);

	auto actionNextNext = MoveTo::create(SLIDING_TIME, getNextNextLayerPosition());
	m_recordLayer->runAction(actionNextNext);
	m_recordLayer->setZOrder(0);
}


void MyPageScene::showArchiveLayer(void)
{
	CCLOG("MyPageMenuScene::showArchiveLayer() is called.\n");
	auto actionPrev= MoveTo::create(SLIDING_TIME, getPrevLayerPosition());
	m_myWordLayer->runAction(actionPrev);
	m_myWordLayer->setZOrder(0);

	auto actionCurrent= MoveTo::create(SLIDING_TIME, getCurrentLayerPosition());
	m_archieveLayer->runAction(actionCurrent);
	m_archieveLayer->setZOrder(1);
	m_archieveLayer->refreshListViewData();

	auto actionNext = MoveTo::create(SLIDING_TIME, getNextLayerPosition());
	m_recordLayer->runAction(actionNext);
	m_recordLayer->setZOrder(0);
}
void MyPageScene::showRecordLayer(void)
{
	CCLOG("MyPageMenuScene::showRecordLayer() is called. \n");
	auto actionPrevPrev = MoveTo::create(SLIDING_TIME, getPrevPrevLayerPosition());
	m_myWordLayer->runAction(actionPrevPrev);
	m_myWordLayer->setZOrder(0);

	auto actionPrev= MoveTo::create(SLIDING_TIME, getPrevLayerPosition());
	m_archieveLayer->runAction(actionPrev);
	m_archieveLayer->setZOrder(0);

	auto actionCurrent = MoveTo::create(SLIDING_TIME, getCurrentLayerPosition());
	m_recordLayer->runAction(actionCurrent);
	m_recordLayer->setZOrder(1);
}
