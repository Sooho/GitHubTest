#ifndef __MY_PAGE_MENU_LAYER_H__
#define __MY_PAGE_MENU_LAYER_H__

#include "cocos2d.h"
#include "MyPageScene.h"

using namespace cocos2d;

class MyPageScene;

class MyPageMenuLayer : public cocos2d::LayerColor
{
private:
	LabelTTF*	m_label;

	Sprite*		m_sprMyWord;
	Sprite*		m_sprArchive;
	Sprite*		m_sprRecord;

	EventListenerTouchOneByOne* m_listener;

public:

	static MyPageScene* m_parentScene;

	virtual bool init();
    CREATE_FUNC(MyPageMenuLayer);

    static void	setParentScene(MyPageScene* parent);

    bool onTouchBegan(Touch *touch, Event *event);

    void goMyWord(void);
    void goArchive(void);
    void goRecord(void);

};

#endif // __MY_PAGE_MENU_LAYER_H__
