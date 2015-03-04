#ifndef __SETTINGFIRSTLAYER_H__
#define __SETTINGFIRSTLAYER_H__

#include "cocos2d.h"
#include "SettingScene.h"

USING_NS_CC;
class SettingScene;
class SettingFirstLayer : public LayerColor
{
private:


public:
	static SettingScene* m_parentScene;
    Layer* m_bgLayer;

    virtual bool init();
    CREATE_FUNC(SettingFirstLayer);

    static void	setParentScene(SettingScene* parent);
    void setFirstLayer();

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch *touch, Event* event);
    void onTouchEnded(Touch *touch, Event* event);
    void onTouchCancelled(Touch *touch, Event* event);

    bool _isPointIn(Node* sender, const Point &worldPoint);
    void _moveAc();
    void _reversMoveAc();
    void _btnMoveAc(int mnum_x, int mnum_y);

    Point btn_dragwordsound;

 };


#endif // __SETTINGFIRSTLAYER_H__
