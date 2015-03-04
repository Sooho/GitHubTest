#ifndef __SETTINGACCOUNTLAYER_H__
#define __SETTINGACCOUNTLAYER_H__

#include "cocos2d.h"
#include "SettingScene.h"

USING_NS_CC;
class SettingScene;
class SettingAccountLayer : public LayerColor
{
private:



public:
	static SettingScene* m_parentScene;

    virtual bool init();
    CREATE_FUNC(SettingAccountLayer);

    static void setParentScene(SettingScene* parent);
    void setAccountLayer();
    bool onTouchBegan(Touch* touch, Event* event);

    void _moveAc();
    void _reversMoveAc();
    bool _isPointIn(Node* sender, const Point &worldPoint);

 };


#endif // __SETTINGFIRSTACCOUNT_H__
