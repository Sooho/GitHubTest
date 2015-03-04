#include <string>
#include "cocos2d.h"
#include "WordCardConfigure.h"
#include "WordCardLayer.h"
#include "MenuScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

WordCardScene* WordCardLayer::m_parentScene = NULL;

// on "init" you need to initialize your instance
bool WordCardLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B::BLACK) )
    {
        return false;
    }
    this->setContentSize(Size(WordCardConfigure::m_screenSize.width, WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT - WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT));

	////////////////////////////////
	// add Word
	m_lblWord = LabelTTF::create("",  "Arial", 48,  Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 48 * 1.5),  TextHAlignment::LEFT, TextVAlignment::BOTTOM);
	m_lblWord->setAnchorPoint(Point(0,0));
	m_lblWord->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN, this->getContentSize().height - 48 * 1.5));
	m_lblWord->setColor(Color3B::BLACK);
	this->addChild(m_lblWord, 1);

	// add Meaning
	m_lblWord_korean = LabelTTF::create("",  "Arial", 32, Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 32 * 1.5),  TextHAlignment::LEFT, TextVAlignment::BOTTOM);
	m_lblWord_korean->setAnchorPoint(Point(0,0));
	m_lblWord_korean->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN, this->getContentSize().height - 48 * 1.5 - 32 * 1.5));
	m_lblWord_korean->setColor(Color3B::GRAY);
	this->addChild(m_lblWord_korean, 1);

    // add Example
	m_lblExample = LabelTTF::create("", "Arial", 32, Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN , 32 * 2),  TextHAlignment::LEFT, TextVAlignment::CENTER);
	m_lblExample->setAnchorPoint(Point(0,0));
	m_lblExample->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN, 0));
	m_lblExample->setColor(Color3B::BLACK);
	this->addChild(m_lblExample, 1);

	// add Picture
	m_sprPicture = Sprite::create();
	m_sprPicture->setAnchorPoint(Point(0,0));
	m_sprPicture->setPosition(Vec2(0, 0));
	this->addChild(m_sprPicture, 0);

	m_wordCardValue = NULL;

   /////////////////////////////
    // 2. init listener
	this->setTouchEnabled(true);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(WordCardLayer::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(WordCardLayer::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(WordCardLayer::onTouchEnded, this);
	m_listener->onTouchCancelled = CC_CALLBACK_2(WordCardLayer::onTouchCancelled, this);
	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

	return true;
}

void WordCardLayer::setWordCardValue(int wordCardId)
{
	m_wordCardValue = m_parentScene->m_wordCard->getWordCardValue(wordCardId);
	_setWordCardValue(m_wordCardValue);
}


void WordCardLayer::setParentScene(WordCardScene* parent)
{
//	if (NULL == m_parentScene)
		m_parentScene = parent;
}

bool WordCardLayer::_isPositionBetweenBounds(Point pos)
{
	bool rtn = getBoundingBox().containsPoint(pos);
	if (!rtn)
	{
	    CCLOG("[ERROR] WordCardLayer, Out of bounds! (pos.x:%f, pox.y:%f) \n", pos.x, pos.y);

	}
	return rtn;
}


void WordCardLayer::_setWordCardValue(WordCardValue* strArg)
{
    CCLOG("[WordCardLayer::_setWordCardValue] \n");

    m_wordCardValue = strArg;
    m_wordCardValue->print();

    m_lblWord->setString(strArg->word);
    m_lblWord_korean->setString(strArg->word_korean);
	m_lblExample->setString(strArg->example);
	m_sprPicture->setTexture(strArg->picture);

	m_sprPicture->setScaleX(WordCardConfigure::m_screenSize.width/m_sprPicture->getContentSize().width);
	m_sprPicture->setScaleY((WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT - WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT)/m_sprPicture->getContentSize().height);

}

void WordCardLayer::_playSoundWord(std::string sound_word)
{
	CCLOG("sound_word.c_str():%s\n", sound_word.c_str());
//	SimpleAudioEngine::getInstance()->playEffect(sound_word.c_str());
}

int WordCardLayer::_getSwipeDirection(Point p1, Point p2)
{
	CCLOG("[_getSwipeDirection] p1.x:%f, p2.x:%f, p1.y:%f, p2.y:%f, SWIPE_MIN_DISTANCE:%d\n", p1.x, p2.x, p1.y, p2.y, SWIPE_MIN_DISTANCE);
	// Calculate the distance
	float l_deltaX = p1.x - p2.x;
	float l_deltaY = p1.y - p2.y;

	float l_horSwipeDistancePercentage = fabs((l_deltaX / getContentSize().width) * 100);
	float l_verSwipeDistancePercentage = fabs((l_deltaY / getContentSize().height) * 100);


	CCLOG("[_getSwipeDirection] deltaX:%f, deltaY:%f, l_horSwipeDistancePercentage:%f, l_verSwipeDistancePercentage:%f, SWIPE_MIN_DISTANCE:%d \n",
						l_deltaX, l_deltaY, l_horSwipeDistancePercentage, l_verSwipeDistancePercentage, SWIPE_MIN_DISTANCE);

	int l_direction = SWIPE_DIRECTION_UNKOWN ;
	if (fabs(l_deltaX) > fabs(l_deltaY) && l_horSwipeDistancePercentage > SWIPE_MIN_DISTANCE ) // horizontal
	{
		if (l_deltaX < 0)
			l_direction = SWIPE_DIRECTION_RIGTH;
		if (l_deltaX > 0)
			l_direction = SWIPE_DIRECTION_LEFT;

	}
	else if (fabs(l_deltaX) < fabs(l_deltaY) && l_verSwipeDistancePercentage > SWIPE_MIN_DISTANCE ) // Vertical
	{
		if (l_deltaY < 0)
			l_direction = SWIPE_DIRECTION_UP;
		if (l_deltaY > 0)
			l_direction = SWIPE_DIRECTION_DOWN;
	}
	// TODO for touch TAB
	//	else if (deltaTime >= this->_xtLongTapTime) // No movement, tap detected
	//	{
	//		this->xtLongTapGesture(location);
	//	}
	//	else
	//		{
	//			if (this->_xtNumberOfTaps == 0)
	//			{
	//				this->_xtTouchStart = this->millisecondNow();
	//				this->schedule(schedule_selector(XTLayer::tapHandler), (this->_xtDoubleTapTime / 1000), 1, 0);
	//			}
	//			this->_xtNumberOfTaps++;
	//	}
	return l_direction;
}

bool WordCardLayer::onTouchBegan(Touch* touch, Event* event)
{
    if (m_isRecognizing) {
    	m_isRecognizing = false;
        return false;
    }

	m_initialPosition = touch->getLocation();
	if (!_isPositionBetweenBounds(m_initialPosition))
	{
		CCLOG("onTouchBegan, return due to Out of bounds\n");
    	m_isRecognizing = false;
    	return false;
 	}

	m_startTime = _getMillisecondNow();
	m_prevPosition = m_initialPosition;	 // for moving event
	m_isRecognizing = true;

	CCLOG("[****************************************************************************************]\n");
	CCLOG("[onTouchBegan] m_startTime:%ld, m_initialPosition.x=%f, m_initialPosition.y=%f\n", m_startTime, m_initialPosition.x, m_initialPosition.y);
	CCLOG("[****************************************************************************************]\n");

    return true;
}

void WordCardLayer::onTouchMoved(Touch *touch, Event *event)
{
	if (!m_isRecognizing) return;
	Point l_currentLocation = touch->getLocation();
	if (!_isPositionBetweenBounds(l_currentLocation))
	{
	    m_isRecognizing = false;
	    return;
	}

    float l_deltaX = l_currentLocation.x-m_prevPosition.x;
    float l_deltaY = l_currentLocation.y-m_prevPosition.y;

 	CCLOG("[onTouchMoved] m_prevPosition.x=%f, m_prevPosition.y=%f\n", m_prevPosition.x, m_prevPosition.y);
 	CCLOG("[onTouchMoved] l_currentLocation.x=%f, l_currentLocation.y=%f\n", l_currentLocation.x, l_currentLocation.y);
 	CCLOG("[onTouchMoved] before: getPositionX()=%f, getPositionY()=%f, deltaX=%f, deltaY=%f\n", getPositionX(), getPositionY(), l_deltaX, l_deltaY);

#ifdef SWIPE_LEFT_RIGHT
    m_parentScene->m_currentWordCardLayer->moveLayerLeftRight(l_deltaX);

    if (m_parentScene->m_currentWordCardLayer->m_wordCardValue->wordId == m_parentScene->m_wordCard->getLastWordId())
    	m_parentScene->m_wordCardEndingLayer->setPosition(m_parentScene->m_wordCardEndingLayer->getPositionX() + l_deltaX, m_parentScene->m_wordCardEndingLayer->getPositionY());
    else
    	m_parentScene->m_nextWordCardLayer->moveLayerLeftRight(l_deltaX);

    if (NULL != m_parentScene->m_prevWordCardLayer)
        m_parentScene->m_prevWordCardLayer->moveLayerLeftRight(l_deltaX);
#else
	m_parentScene->m_currentWordCardLayer->moveLayerUpDown(l_deltaY);
	m_parentScene->m_nextWordCardLayer->moveLayerUpDown(l_deltaY);
	m_parentScene->m_prevWordCardLayer->moveLayerUpDown(l_deltaY);
#endif
//	CCLOG("[onTouchMoved]  after: getPositionX()=%f, getPositionY()=%f, deltaX=%f, deltaY=%f\n", getPositionX(), getPositionY(), l_deltaX, l_deltaY);

	m_prevPosition = l_currentLocation;

}

//void WordCardLayer::moveLayer(float deltaX, float deltaY )
void WordCardLayer::moveLayerLeftRight(float deltaX)
{
	float l_targetX= getPositionX() + deltaX;

//	CCLOG("[moveLayer] getPositionX():%f, deltaX=%f, l_targetX:%f, layerPosition:%d\n", getPositionX() , deltaX, l_targetX, m_layerPosition);
	setPosition(l_targetX, getPositionY());
}

void WordCardLayer::moveLayerUpDown(float deltaY)
{
	float l_targetY= getPositionY() + deltaY;

//	CCLOG("[moveLayer] getPositionX():%f, deltaX=%f, l_targetX:%f, layerPosition:%d\n", getPositionX() , deltaX, l_targetX, m_layerPosition);
	setPosition(getPositionX(), l_targetY);
}


long WordCardLayer::_getMillisecondNow()
{
	long l_msec;
	struct timeval l_now;
    gettimeofday(&l_now, NULL);
    l_msec = (l_now.tv_sec * 1000 + l_now.tv_usec / 1000);

    CCLOG("[_getMillisecondNow] l_now.tv_sec:%ld,  l_now.tv_usec:%ld, l_msec:%ld", l_now.tv_sec, l_now.tv_usec, l_msec);

    return l_msec;
}

void WordCardLayer::onTouchEnded(Touch *touch, Event *event)
{
	Point l_finalPosition = touch->getLocation();

	CCLOG("[****************************************************************************************]\n");
	CCLOG(" onTouchEnded: l_finalPosition.x=%f, l_finalPosition.y=%f\n", l_finalPosition.x, l_finalPosition.y);
	CCLOG("[****************************************************************************************]\n");
	if (!m_isRecognizing)
	{
		return;
	}

	if (!_isPositionBetweenBounds(l_finalPosition))
	{
		return;
	}

	m_isRecognizing = false;

	float l_distance	= _getDistanceBetweenPoints(m_initialPosition, l_finalPosition);
	long l_endTime		= _getMillisecondNow();
	long l_deltaTime	= l_endTime - m_startTime;
	int l_direction		= _getSwipeDirection(m_initialPosition, l_finalPosition);

//	CCLOG("[onTouchEnded] m_startTime:%ld,  l_endTime:%ld, deltaTime:%ld, SWIPE_MAX_DURATION:%d\n", m_startTime, l_endTime, l_deltaTime,SWIPE_MAX_DURATION);
//	CCLOG("[onTouchEnded] l_distance:%f, SWIPE_MIN_DISTANCE:%d, l_direction:%d \n", l_distance, SWIPE_MIN_DISTANCE, l_direction);

 //   if (l_distance >= SWIPE_MIN_DISTANCE && l_duration <= SWIPE_MAX_DURATION && l_direction != SWIPE_DIRECTION_UNKOWN) {

	if (l_distance >= SWIPE_MIN_DISTANCE && l_direction != SWIPE_DIRECTION_UNKOWN) {
		// When swipe is applied
    	switch (l_direction)
    	{
      	case SWIPE_DIRECTION_RIGTH:
       		CCLOG("[onTouchEnded] swipe direction= SWIPE_DIRECTION_RIGHT. \n");
#ifdef SWIPE_LEFT_RIGHT
     		_goPrevWordCardLayer();
#else
     		_backToMenuScene();
#endif
       		break;

      	case SWIPE_DIRECTION_LEFT:
    		CCLOG("[onTouchEnded] swipe direction= SWIPE_DIRECTION_LEFT. \n");
#ifdef SWIPE_LEFT_RIGHT
     		_goNextWordCardLayer();
#endif
    		break;

      	case SWIPE_DIRECTION_UP:
       		CCLOG("[onTouchEnded] swipe direction= SWIPE_DIRECTION_UP. \n");
#ifndef SWIPE_LEFT_RIGHT
     		_goNextWordCardLayer();
#endif
     		break;

      	case SWIPE_DIRECTION_DOWN:
       		CCLOG("[onTouchEnded] swipe direction= SWIPE_DIRECTION_DOWN. \n");
#ifdef SWIPE_LEFT_RIGHT
       		_backToMenuScene();
#else
       		_goPrevWordCardLayer();
#endif

       		break;
       	default:
       		CCLOG("[onTouchEnded] swipe direction= SWIPE_DIRECTION_UNKOWN. \n");
       	}
    }
    else	// swipe is not applied.
    {
		float deltaX = l_finalPosition.x-m_prevPosition.x;
		float deltaY = l_finalPosition.y-m_prevPosition.y;

		CCLOG("[****************************************************************************************]\n");
		CCLOG(" onTouchEnded-(B) ( layerPosition:%d) \n", m_layerPosition);
		CCLOG("[****************************************************************************************]\n");
		CCLOG(" m_initialPosition.x=%f, m_initialPosition.y=%f\n", m_initialPosition.x, m_initialPosition.y);
		CCLOG(" m_prevPosition.x=%f, m_prevPosition.y=%f\n", m_prevPosition.x, m_prevPosition.y);
		CCLOG(" l_finalPosition.x=%f, l_finalPosition.y=%f\n", l_finalPosition.x, l_finalPosition.y);
		CCLOG(" before: getPositionX()=%f, getPositionY()=%f, deltaX=%f, deltaY=%f\n", getPositionX(), getPositionY(), deltaX, deltaY);

		_goCurrentWordCardLayer();

    }

}

void WordCardLayer::onTouchCancelled(Touch *touch, Event *event)
{
	CCLOG("[****************************************************************************************]\n");
	CCLOG(" onTouchCancelled\n");
	CCLOG("[****************************************************************************************]\n");
	_goCurrentWordCardLayer();
}

float WordCardLayer::_getDistanceBetweenPoints(Point p1, Point p2)
{
    float deltaX = p2.x-p1.x;
    float deltaY = p2.y-p1.y;
    return fabs(sqrtf(deltaX*deltaX+deltaY*deltaY));
}

void WordCardLayer::_backToMenuScene(void)
{
	Director::getInstance()->replaceScene(MenuScene::create());
}


void WordCardLayer::_goNextWordCardLayer(void)
{
	// change position
	auto actionCurrent = MoveTo::create(SLIDING_TIME, m_parentScene->getCurrentWordCardLayerPosition());
    if (m_parentScene->m_currentWordCardLayer->m_wordCardValue->wordId == m_parentScene->m_wordCard->getLastWordId())
    	m_parentScene->m_wordCardEndingLayer->runAction(actionCurrent);
   	else
    	m_parentScene->m_nextWordCardLayer->runAction(actionCurrent);

	auto actionPrev = MoveTo::create(SLIDING_TIME, m_parentScene->getPrevWordCardLayerPosition());
//	auto actionPrev1 = EaseBackIn::create(actionPrev);
	m_parentScene->m_currentWordCardLayer->runAction(actionPrev);

	if (m_parentScene->m_currentWordCardLayer->m_wordCardValue->wordId != m_parentScene->m_wordCard->getLastWordId())
		m_parentScene->m_prevWordCardLayer->setPosition(m_parentScene->getNextWordCardLayerPosition());

	// change pointers
	WordCardLayer* l_tempWordCardLayer;

	l_tempWordCardLayer = m_parentScene->m_prevWordCardLayer;

	m_parentScene->m_prevWordCardLayer = m_parentScene->m_currentWordCardLayer;
	m_parentScene->m_currentWordCardLayer = m_parentScene->m_nextWordCardLayer;

	m_parentScene->m_nextWordCardLayer = l_tempWordCardLayer;

	// set next data to m_nextWordCardLayer
	int l_currentWordId = m_parentScene->m_currentWordCardLayer->m_wordCardValue->wordId;
	CCLOG("currentId:%d, lastId:%d\n", l_currentWordId,  m_parentScene->m_wordCard->getLastWordId());
	if (l_currentWordId ==  m_parentScene->m_wordCard->getLastWordId())
	{
		m_parentScene->setNextWordCardEnding();
	}
	else
		m_parentScene->m_nextWordCardLayer->_setWordCardValue(m_parentScene->m_wordCard->getNextWordCardValue(l_currentWordId));

	// set focus to currentLayer
	m_parentScene->m_currentWordCardLayer->focusCurrentLayer();
}

void WordCardLayer::_goPrevWordCardLayer(void)
{
	if (m_parentScene->m_currentWordCardLayer->m_wordCardValue->wordId == m_parentScene->m_wordCard->getFirstWordId())
	{
		CCLOG("The first word card!!\n");
		_goCurrentWordCardLayer();
		return;
	}

	// change position
	auto actionCurrent = MoveTo::create(SLIDING_TIME, m_parentScene->getCurrentWordCardLayerPosition());
	m_parentScene->m_prevWordCardLayer->runAction(actionCurrent);

	auto actionNext = MoveTo::create(SLIDING_TIME, m_parentScene->getNextWordCardLayerPosition());
//	auto actionNext1 = EaseBackIn::create(actionNext);
	m_parentScene->m_currentWordCardLayer->runAction(actionNext);

	m_parentScene->m_nextWordCardLayer->setPosition(m_parentScene->getPrevWordCardLayerPosition());

	// change pointers
	CCLOG("[_goPrevWordCardLayer 4]\n");
	WordCardLayer* l_tempWordCardLayer;

	l_tempWordCardLayer = m_parentScene->m_nextWordCardLayer;

	m_parentScene->m_nextWordCardLayer = m_parentScene->m_currentWordCardLayer;
	m_parentScene->m_currentWordCardLayer = m_parentScene->m_prevWordCardLayer;

	m_parentScene->m_prevWordCardLayer = l_tempWordCardLayer;

	// set next data to m_nextWordCardLayer
	int l_currentWordId = m_parentScene->m_currentWordCardLayer->m_wordCardValue->wordId;
	if (l_currentWordId ==  m_parentScene->m_wordCard->getFirstWordId())
		m_parentScene->m_prevWordCardLayer->setEmpty();
	else
		m_parentScene->m_prevWordCardLayer->_setWordCardValue( m_parentScene->m_wordCard->getPrevWordCardValue(l_currentWordId));

	// set focus to currentLayer
	m_parentScene->m_currentWordCardLayer->focusCurrentLayer();
}


void WordCardLayer::_goCurrentWordCardLayer(void)
{
	auto actionCurrent = MoveTo::create(ACTION_TIME, m_parentScene->getCurrentWordCardLayerPosition());
	auto actionCurrent1 = EaseElasticOut::create(actionCurrent);
	m_parentScene->m_currentWordCardLayer->runAction(actionCurrent1);

	auto actionPrev = MoveTo::create(ACTION_TIME, m_parentScene->getPrevWordCardLayerPosition());
	m_parentScene->m_prevWordCardLayer->runAction(actionPrev);

	auto actionNext= MoveTo::create(ACTION_TIME, m_parentScene->getNextWordCardLayerPosition());
	m_parentScene->m_nextWordCardLayer->runAction(actionNext);
}

void WordCardLayer::focusCurrentLayer(void)
{
	_playSoundWord(m_wordCardValue->word_sound);
}

bool WordCardLayer::isEmpty(void)
{
	bool rtn = false;
	if ( NULL == m_wordCardValue)
		rtn = true;

	return rtn;
}

void WordCardLayer::setEmpty(void)
{
    CCLOG("[WordCardLayer::setEmpty] \n");

    m_wordCardValue = NULL;

    m_lblWord->setString("");
    m_lblWord_korean->setString("");
	m_lblExample->setString("");
	m_sprPicture->cleanup();

}

void WordCardLayer::addMyWord()
{
    CCLOG("[WordCardLayer::addMyWord] \n");
	MyPage::getInstance()->addMyWord(m_wordCardValue->lessonId, m_wordCardValue->wordId, m_wordCardValue->word);
}

void WordCardLayer::addArchive()
{
    CCLOG("[WordCardLayer::addArchive] \n");
	MyPage::getInstance()->addArchivedWord(m_wordCardValue->lessonId, m_wordCardValue->wordId, m_wordCardValue->word);
}

