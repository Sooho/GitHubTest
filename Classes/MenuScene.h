#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class MenuScene : public cocos2d::Scene
{
private:
	Layer* m_menuLayer;
public:
    virtual bool init();  
    
    CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
