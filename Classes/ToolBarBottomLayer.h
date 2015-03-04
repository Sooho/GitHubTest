#ifndef __TOOL_BAR_BOTTOM_LAYER_H__
#define __TOOL_BAR_BOTTOM_LAYER_H__

#include "cocos2d.h"
#include "WordCardScene.h"
#include "MyPageScene.h"

using namespace cocos2d;

class WordCardScene;
class MyPageScene;

class ToolBarBottomLayer : public cocos2d::LayerColor
{
private:
	Sprite*		m_sprHome;
	Sprite*		m_sprMyPage;
	Sprite*		m_sprSettings;

	EventListenerTouchOneByOne* m_listener;

	int			m_contextLayer;

    void _goHome(void);
    void _goMyPage(void);
    void _goSettings(void);

public:
	static WordCardScene* m_parentWordCardScene;
	static MyPageScene* m_parentMyPageScene;
	static void	setParentWordCardScene(WordCardScene* parent);
	static void	setParentMyPageScene(MyPageScene* parent);


    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *event);

    CREATE_FUNC(ToolBarBottomLayer);

    void setContext(int context);

};

#endif // __TOOL_BAR_BOTTOM_LAYER_H__
