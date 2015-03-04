#ifndef __WORD_CARD_CONFIGURE_H__
#define __WORD_CARD_CONFIGURE_H__

#include "cocos2d.h"
#include <iostream>
#include <string>

using namespace cocos2d;

//icons
static std::string ICON_FAVORTIE_WORD = "icons/favorite.jpg";
static std::string ICON_ARCHIRVE = "icons/archive.jpg";
static std::string ICON_RECORD = "icons/record.png";
static std::string ICON_HOME = "icons/home.jpg";
static std::string ICON_MY_PAGE = "icons/mypage.png";
static std::string ICON_SETTING = "icons/setting.jpg";
static std::string ICON_BACK = "icons/back.png";


class WordCardConfigure
{
private:
    static WordCardConfigure* m_instance;

    WordCardConfigure() {}
    ~WordCardConfigure() {}

public:

    static Size m_screenSize;

    static int TOOL_BAR_HEIGHT ;
    static int TOOL_BAR_BOTTOM_HEIGHT ;
    static int ICON_HEIGHT ;

    static int LABEL_SCALE;
    static int LEFT_MARGIN;


    static void init(void);
    static WordCardConfigure* getInstance(void);
	static void releaseInstance(void);

	static std::string numberToString(int i)
	{
		std::stringstream ss;
		ss << i;

		std::string str;
		ss >> str;

		return str;

	}

	static std::string numberToString(float i)
	{
		std::stringstream ss;
		ss << i;

		std::string str;
		ss >> str;

		return str;

	}

};


#endif // __WORD_CARD_CONFIGURE_H__
