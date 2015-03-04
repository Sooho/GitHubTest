#ifndef __LIST_VIEW_LAYER_H__
#define __LIST_VIEW_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MyPageScene.h"
#include "MyPage.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class MyPageScene;

class ListViewLayer : public cocos2d::LayerColor
{
private:
	int m_myPageType;
	std::vector<WordListValue>* m_words;

	ListView*	m_lvWordList;

	EventListenerTouchOneByOne* m_listener;

	int			_getCurrentItem_LessonId(void);
	int			_getCurrentItem_WordId(void);
	std::string	_getCurrentItem_Word(void);

public:
	static MyPageScene* m_parentScene;

    static ListViewLayer*	createListViewLayer(int myPageType);
	virtual bool init();
    CREATE_FUNC(ListViewLayer);

    static void	setParentScene(MyPageScene* parent);

    void setPageType(int pageType) { m_myPageType = pageType;}
    void setWordsData(std::vector<WordListValue>* words) { m_words = words ; }

	void refreshListViewData(void);

    void onRecoverButtonTouched(Ref *pSender, Widget::TouchEventType type);
    void onArchivingButtonTouched(Ref *pSender, Widget::TouchEventType type);
    void onMyWordButtonTouched(Ref *pSender, Widget::TouchEventType type);
//    bool onTouchBegan(Touch *touch, Event *event);

    void doRecover(void);
    void addArchive(void);
    void addMyWord(void);

};

#endif // __MY_WORD_LAYER_H__
