#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class MenuLayer : public cocos2d::LayerColor
{
private:
//	Menu*		m_menu;
	LabelTTF*	m_label;
	Sprite*		m_sprLesson;

	EventListenerTouchOneByOne* m_listener;

    void _goToWordCardScene(int lessonId);

public:
    virtual bool init();  
    CREATE_FUNC(MenuLayer);

    bool onTouchBegan(Touch *touch, Event *event);

    void goHelp(Object* pSender);
    void goPlay(Object* pSender);
    void goQuit(Object* pSender);

};

#endif // __MENU_LAYER_H__
