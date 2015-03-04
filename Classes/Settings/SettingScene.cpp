#include "cocos2d.h"
#include "SettingScene.h"
#include "SettingFirstLayer.h"
#include "SettingInfoLayer.h"
#include "SettingAccountLayer.h"
#include "ToolBarBottomLayer.h"
#include "WordCardConfigure.h"

USING_NS_CC;

class SettingAccountLayer;
class SettingFirstLayer;
bool SettingScene::init()
{

    if (!Scene::init())
    {
        return false;
    }

    return true;
}

SettingScene* SettingScene::createSettingScene()
{
	auto scene= SettingScene::create();

	SettingFirstLayer::setParentScene(scene);
	scene->m_settingfirstLayer = SettingFirstLayer::create();
	scene->m_settingfirstLayer->setAnchorPoint(Vec2(0,0));
	scene->m_settingfirstLayer->setPosition(Vec2(0, 0));
	scene->addChild(scene->m_settingfirstLayer,1);

	SettingInfoLayer::setParentScene(scene);
	scene->m_settingInfoLayer = SettingInfoLayer::create();
	scene->m_settingInfoLayer->setAnchorPoint(Vec2(0,0));
	scene->m_settingInfoLayer->setPosition(Vec2(WordCardConfigure::m_screenSize.width,0));
	scene->addChild(scene->m_settingInfoLayer, 2);

	SettingAccountLayer::setParentScene(scene);
	scene->m_settingaccountLayer = SettingAccountLayer::create();
	scene->m_settingaccountLayer->setAnchorPoint(Vec2(0,0));
	scene->m_settingaccountLayer->setPosition(Vec2(WordCardConfigure::m_screenSize.width,0));
	scene->addChild(scene->m_settingaccountLayer, 2);

	scene->m_toolBarBottomLayer = ToolBarBottomLayer::create();
	scene->m_toolBarBottomLayer->setAnchorPoint(Vec2(WordCardConfigure::m_screenSize.width,0));
	scene->m_toolBarBottomLayer->setPosition(Vec2(0, 0));
	scene->addChild(scene->m_toolBarBottomLayer, 2);

	return scene;

}


void SettingScene::_moveAc(int lnum)
{

	if(lnum==1)
	{
		CCLog("[%s]\n", __func__);
		m_settingfirstLayer -> _moveAc();
		m_settingInfoLayer -> _moveAc();
	}
	if(lnum==2)
	{
		CCLog("[%s]\n", __func__);
		m_settingfirstLayer -> _moveAc();
		m_settingaccountLayer -> _moveAc();
	}
}

void SettingScene::_reversMoveAc(int lnum)
{
	if(lnum==1)
	{
		CCLog("[%s]\n", __func__);
		m_settingfirstLayer -> _reversMoveAc();
		m_settingInfoLayer -> _reversMoveAc();
     }
	if(lnum==2)
	{
		CCLog("[%s]\n", __func__);
		CCLog("[%s]\n", __func__);
		m_settingfirstLayer -> _reversMoveAc();
		m_settingaccountLayer -> _reversMoveAc();

	}
}


