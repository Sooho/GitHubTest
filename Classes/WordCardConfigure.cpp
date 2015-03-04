#include "WordCardConfigure.h"

using namespace cocos2d;

WordCardConfigure* WordCardConfigure::m_instance = NULL;
Size WordCardConfigure::m_screenSize(0,0);
int WordCardConfigure::TOOL_BAR_HEIGHT = 0;
int WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT = 0;
int WordCardConfigure::ICON_HEIGHT = 0;
int WordCardConfigure::LABEL_SCALE = 0;
int WordCardConfigure::LEFT_MARGIN = 0;


WordCardConfigure* WordCardConfigure::getInstance()
{
	if(m_instance == NULL)
		m_instance = new WordCardConfigure();

	return m_instance;
}

void WordCardConfigure::releaseInstance()
{
	if(m_instance != NULL)
		delete m_instance;
}

void WordCardConfigure::init(void)
{
	WordCardConfigure::getInstance();
	m_screenSize = Director::sharedDirector()->getWinSize();

	TOOL_BAR_HEIGHT =  static_cast<int>(m_screenSize.height * 0.1) ; //10% of window height
	TOOL_BAR_BOTTOM_HEIGHT = static_cast<int>(m_screenSize.height * 0.08) ; //10% of window height

	ICON_HEIGHT = static_cast<int>(TOOL_BAR_BOTTOM_HEIGHT * 0.6) ;

    LABEL_SCALE = 2;
    LEFT_MARGIN  = 20;

	CCLOG("[WordCardConfigure] WordCardConfigure has been initialized.");
}
