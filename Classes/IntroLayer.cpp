#include "WordCardConfigure.h"
#include "IntroLayer.h"
#include "MenuScene.h"
#include "MyPage.h"

USING_NS_CC;

Scene* IntroLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IntroLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroLayer::init()
{
	if ( !LayerColor::initWithColor(Color4B::WHITE))
	{
        return false;
    }
    
    // project init TODO - need to be relocated (sooho)
    WordCardConfigure::init();
    MyPage::init();

    auto l_label = LabelTTF::create("Welcome to PICtalk", "", 56,
    						Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 56 * 4),  TextHAlignment::CENTER, TextVAlignment::BOTTOM);
    l_label->setAnchorPoint(Point(0,0));
    l_label->setPosition(Vec2(0, this->getContentSize().height - 56 * 4));
    l_label->setColor(Color3B::ORANGE);
    this->addChild(l_label, 1);

    // TODO link to level test
    auto l_temp = LabelTTF::create("[TBD] Level Test ->", "", 32,
    						Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 32 * 4),  TextHAlignment::CENTER, TextVAlignment::BOTTOM);
    l_temp->setAnchorPoint(Point(0,0));
    l_temp->setPosition(Vec2(0, this->getContentSize().height  - 56 * 4 - 32 * 4));
    l_temp->setColor(Color3B::GRAY);
    this->addChild(l_temp, 1);

	this->setTouchEnabled(true);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(IntroLayer::onTouchBegan, this);
	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

    return true;
}


bool IntroLayer::onTouchBegan(Touch* touch, Event* event) {
     _goMenu();

    return true;
}

void IntroLayer::_goMenu(void)
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = MenuScene::create();
	auto pScene = TransitionFade::create(0.5f, hScene);

	Director::getInstance()->replaceScene(pScene);
}

