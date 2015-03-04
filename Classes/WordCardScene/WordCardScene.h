#ifndef __WORD_CARD_SCENE_H__
#define __WORD_CARD_SCENE_H__

#include "cocos2d.h"
#include "WordCardLayer.h"
#include "WordCardTitleLayer.h"
#include "WordCardEndingLayer.h"
#include "ToolBarBottomLayer.h"
#include "ToolBarLayer.h"
#include "WordCardConfigure.h"

#define SWIPE_LEFT_RIGHT

class WordCardLayer;
class WordCardTitleLayer;
class WordCardEndingLayer;
class ToolBarLayer;
class ToolBarBottomLayer;

class WordCardScene : public cocos2d::Scene
{
private:

public:
	WordCardTitleLayer*		m_wordCardTitleLayer;
	WordCardEndingLayer*	m_wordCardEndingLayer;
	ToolBarLayer*			m_toolBarLayer;
	ToolBarBottomLayer*		m_toolBarBottomLayer;

	WordCardLayer*			m_prevWordCardLayer;
	WordCardLayer*			m_currentWordCardLayer;
	WordCardLayer*			m_nextWordCardLayer;

	WordCard*				m_wordCard;

    static WordCardScene*	createWordCardScene(int lessonId);

    virtual bool init();  
    CREATE_FUNC(WordCardScene);

#ifdef SWIPE_LEFT_RIGHT
	Point getPrevWordCardLayerPosition(void) {return Point(-720,WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT);}
	Point getCurrentWordCardLayerPosition(void) {return Point(0,WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT);}
	Point getNextWordCardLayerPosition(void) {return Point( 720,WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT);}
#else
    float l_prevY = WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT;
	Point getPrevWordCardLayerPosition(void) {return Point(0, l_prevY);}
	Point getCurrentWordCardLayerPosition(void) {return Point(0,0);}
	Point getNextWordCardLayerPosition(void) {return Point( 0, -1 * l_prevY);}

#endif

	void goBackToWordCardTitle(void);
	void setNextWordCardEnding(void);

};

#endif // __WORD_CARD_SCENE_H__
