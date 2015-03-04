#ifndef __SETTINGSCENE_H__
#define __SETTINGSCENE_H__

#include "cocos2d.h"
#include "SettingFirstLayer.h"
#include "SettingInfoLayer.h"
#include "SettingAccountLayer.h"
#include "ToolBarBottomLayer.h"

USING_NS_CC;

class SettingFirstLayer;
class SettingInfoLayer;
class SettingAccountLayer;
class ToolBarBottomLayer;

class SettingScene : public Scene
{
private:



public:

 static SettingScene* createSettingScene();

 SettingFirstLayer*  m_settingfirstLayer;
 SettingInfoLayer*  m_settingInfoLayer;
 SettingAccountLayer*  m_settingaccountLayer;
 ToolBarBottomLayer*  m_toolBarBottomLayer;


virtual bool init();

void _moveAc(int lnum);
void _reversMoveAc(int lnum);


CREATE_FUNC(SettingScene);

 };


#endif // __SETTINGSCENE_H__
