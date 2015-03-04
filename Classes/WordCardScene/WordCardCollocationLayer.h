#ifndef __WORD_CARD_COLLOCATION_LAYER_H__
#define __WORD_CARD_COLLOCATION_LAYER_H__

#include "cocos2d.h"
#include "WordCardScene.h"
#include "WordCard.h"

using namespace cocos2d;
class WordCardScene;

class WordCardCollocationLayer : public cocos2d::LayerColor
{
private:
	WordCardValue* m_wordCardValue;

	LabelTTF*	m_lblWord;
	LabelTTF*	m_lblWord_korean;
	LabelTTF*	m_lblExample;
	Sprite*		m_sprPicture;

	// for swipe gesture
    bool	m_isRecognizing;
	Point	m_initialPosition;
	Point 	m_prevPosition;
	long	m_startTime;

	// from Scene, layer poision
	int		m_layerPosition;

	int		_getTouchCounter(void);
	void	_setLabel(int iValue);

	EventListenerTouchOneByOne* m_listener;

	void	_setWordCardValue(WordCardValue* strArg);

	// for swipe gesture
    int		_getSwipeDirection(Point p1, Point p2);
    float	_getDistanceBetweenPoints(Point p1, Point p2);
    bool	_isPositionBetweenBounds(Point pos);
    long	_getMillisecondNow(void);

    // play sound
    void	_playSoundWord(std::string sound_word);
    void	_playSoundExample(std::string sound_example);


    // for moving layers
    void	_backToMenuScene(void);
	void	_goNextWordCardLayer(void);
	void	_goPrevWordCardLayer(void);
	void	_goCurrentWordCardLayer(void);


public:
	static WordCardScene* m_parentScene;

	virtual bool init();
    CREATE_FUNC(WordCardCollocationLayer);

    static WordCardCollocationLayer*	createWordCardCollocationLayer(int wordCardId);
    static void				setParentScene(WordCardScene* parent);

    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);


    // for swipe
	void moveLayerLeftRight(float deltaX);
	void moveLayerUpDown(float deltaY);

	void focusCurrentLayer(void);


};

#endif // __WORD_CARD_COLLOCATION_LAYER_H__
