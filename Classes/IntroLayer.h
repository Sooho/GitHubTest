#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#define COCOS2D_DEBUG 1

#include "cocos2d.h"

using namespace cocos2d;

class IntroLayer : public cocos2d::LayerColor
{
private:
	EventListenerTouchOneByOne* m_listener;

    void _goMenu(void);


public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    bool onTouchBegan(Touch *touch, Event *event);

    // implement the "static create()" method manually
    CREATE_FUNC(IntroLayer);
};

#endif // __INTRO_SCENE_H__
