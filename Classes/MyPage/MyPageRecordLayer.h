#ifndef __MY_PAGE_RECORD_LAYER_H__
#define __MY_PAGE_RECORD_LAYER_H__

#include "cocos2d.h"
#include "MyPageScene.h"
#include "MyPage.h"

using namespace cocos2d;
class MyPageScene;

class MyPageRecordLayer : public cocos2d::LayerColor
{
private:
	MyRecord	m_totalRecord;

	LabelTTF*	m_lblTitle;
	LabelTTF*	m_lblNumOfMyWords;
	LabelTTF*	m_lblNumOfArchivedWords;
	LabelTTF*	m_lblNumOfAvgReviews;
	LabelTTF*	m_lblQuizePassRate;

//	Sprite*		m_sprPicture;

	EventListenerTouchOneByOne* m_listener;


	void _setRecordData(void);

public:
	static MyPageScene* m_parentScene;
    static void	setParentScene(MyPageScene* parent);

    virtual bool init();
    bool onTouchBegan(Touch *touch, Event *event);

    CREATE_FUNC(MyPageRecordLayer);

};

#endif // __MY_PAGE_RECORD_LAYER_H__
