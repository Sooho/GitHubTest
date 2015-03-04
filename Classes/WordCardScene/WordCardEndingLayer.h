#ifndef __WORD_CARD_ENDING_LAYER_H__
#define __WORD_CARD_ENDING_LAYER_H__

#include "cocos2d.h"
#include "WordCardScene.h"

using namespace cocos2d;
class WordCardScene;

class WordCardEndingLayer : public cocos2d::LayerColor
{
private:
	LabelTTF*	m_lblEnding;
	Sprite*		m_sprPicture;

	EventListenerTouchOneByOne* m_listener;

    void _goQuizeScene(void);

public:
	static WordCardScene* m_parentScene;
    static void	setParentScene(WordCardScene* parent);

    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *event);

    CREATE_FUNC(WordCardEndingLayer);

};

#endif // __WORD_CARD_ENDING_LAYER_H__
