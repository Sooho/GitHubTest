#ifndef __MY_PAGE_SCENE_H__
#define __MY_PAGE_SCENE_H__

#include "cocos2d.h"
#include "WordCardConfigure.h"
#include "ToolBarBottomLayer.h"
#include "ToolBarLayer.h"
#include "MyPageMenuLayer.h"
#include "ListViewLayer.h"
#include "MyPageRecordLayer.h"
#include "MyPage.h"


using namespace cocos2d;

class ToolBarLayer;
class ToolBarBottomLayer;
class MyPageMenuLayer;
class MyWordLayer;
class MyPageRecordLayer;


const static int MY_PAGE_TYPE_MY_WORD = 1;
const static int MY_PAGE_TYPE_ARCHIVE = 2;


class MyPageScene : public cocos2d::Scene
{
private:
	ToolBarLayer*			m_toolBarLayer;
	ToolBarBottomLayer*		m_toolBarBottomLayer;

	MyPageMenuLayer*		m_myPageMenuLayer;
	ListViewLayer*			m_myWordLayer;
	ListViewLayer*			m_archieveLayer;
	MyPageRecordLayer*		m_recordLayer;

	Point getPrevPrevLayerPosition(void) {return Point(-720*2, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT);}
	Point getPrevLayerPosition(void) {return Point(-720, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT);}
	Point getCurrentLayerPosition(void) {return Point(0, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT);}
	Point getNextLayerPosition(void) {return Point( 720, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT);}
	Point getNextNextLayerPosition(void) {return Point( 720*2, WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT);}

public:
	MyPage* m_myPageValue;

    virtual bool init();  
    
    CREATE_FUNC(MyPageScene);

    std::vector<WordListValue>*	getMyWords(void) { return m_myPageValue->getMyWords(); }
    std::vector<WordListValue>*	getArchivedWords(void) { return m_myPageValue->getArchivedWords(); }
    std::vector<MyRecord>*		getRecords(void) { return m_myPageValue->getRecords(); }
    MyRecord					getTotalRecord(void) { return m_myPageValue->getTotalRecord(); }

    void showMyWordLayer(void);
    void showArchiveLayer(void);
    void showRecordLayer(void);
};

#endif // __MY_PAGE_SCENE_H__
