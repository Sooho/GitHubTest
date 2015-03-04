#ifndef __TOOL_BAR_LAYER_H__
#define __TOOL_BAR_LAYER_H__

#include "cocos2d.h"
#include "WordCardScene.h"
#include "MyPageScene.h"

using namespace cocos2d;

class WordCardScene;
class MyPageScene;

static const int STATUS_WORD_CARD_TITLE = 1;
static const int STATUS_WORD_CARD = 2;
static const int STATUS_WORD_CARD_ENDING = 3;
static const int STATUS_MY_PAGE_MENU = 4;

class ToolBarLayer : public cocos2d::LayerColor
{
private:
	Sprite*		m_sprBack;
	Sprite*		m_sprFavorite;
	Sprite*		m_sprArchive;

	int			m_contextLayer;

	EventListenerTouchOneByOne* m_listener;

    void _goBack(void);
    void _goFavorite(void);
    void _goAchive(void);

public:
	static WordCardScene* m_parentWordCardScene;
	static MyPageScene* m_parentMyPageScene;
	static void	setParentWordCardScene(WordCardScene* parent);
	static void	setParentMyPageScene(MyPageScene* parent);

	virtual bool init();
    bool onTouchBegan(Touch *touch, Event *event);

    CREATE_FUNC(ToolBarLayer);

    void setContext(int context);


};

#endif // __TOOL_BAR_LAYER_H__
