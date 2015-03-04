#include "MenuScene.h"
#include "MenuLayer.h"
#include "WordCardScene.h"


USING_NS_CC;


// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add Layer
    m_menuLayer = MenuLayer::create();
    this->addChild(m_menuLayer, 1);

    return true;
}
