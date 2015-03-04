#ifndef __WORD_CARD_LAYER_H__
#define __WORD_CARD_LAYER_H__

#include "cocos2d.h"
#include "WordCardScene.h"
#include "WordCard.h"

using namespace cocos2d;
class WordCardScene;

static const int SWIPE_MAX_DURATION = 500;
static const int SWIPE_MIN_DISTANCE = 30; //60;

static const int SWIPE_DIRECTION_RIGTH = 1;
static const int SWIPE_DIRECTION_LEFT = 2;
static const int SWIPE_DIRECTION_UP = 3;
static const int SWIPE_DIRECTION_DOWN = 4;
static const int SWIPE_DIRECTION_UNKOWN = 0;

static const int PREV_LAYER = 0;
static const int CURRENT_LAYER = 1;
static const int NEXT_LAYER = 2;

static const float SLIDING_TIME = 0.4;
static const float ACTION_TIME = 0.7;

class WordCardLayer : public cocos2d::LayerColor
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

    // for moving layers
    void	_backToMenuScene(void);
	void	_goNextWordCardLayer(void);
	void	_goPrevWordCardLayer(void);
	void	_goCurrentWordCardLayer(void);


public:
	static WordCardScene* m_parentScene;

	virtual bool init();
    CREATE_FUNC(WordCardLayer);

    static void	setParentScene(WordCardScene* parent);

    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);

    void setWordCardValue(int wordCardId);

    // for swipe
	void moveLayerLeftRight(float deltaX);
	void moveLayerUpDown(float deltaY);

	void focusCurrentLayer(void);

	bool isEmpty(void) ;
	void setEmpty(void) ;

	void addMyWord();
	void addArchive();
};

#endif // __WORD_CARD_LAYER_H__
