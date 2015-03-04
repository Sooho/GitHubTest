#ifndef __WORD_CARD_TITLE_LAYER_H__
#define __WORD_CARD_TITLE_LAYER_H__

#include "cocos2d.h"
#include "WordCardScene.h"
#include "WordCard.h"

using namespace cocos2d;
class WordCardScene;

class WordCardTitleLayer : public cocos2d::LayerColor
{
private:
	LabelTTF*	m_lblTitle;
	Sprite*		m_sprPicture;

	EventListenerTouchOneByOne* m_listener;

    void _goWordCard(void);

public:
	static WordCardScene* m_parentScene;
    static void	setParentScene(WordCardScene* parent);

    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *event);

    CREATE_FUNC(WordCardTitleLayer);

};

#endif // __WORD_CARD_TITLE_LAYER_H__
