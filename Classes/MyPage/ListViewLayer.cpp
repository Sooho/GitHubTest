#include <stdlib.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MyPageScene.h"
#include "WordCardConfigure.h"
#include "ListViewLayer.h"

using namespace cocos2d;
using namespace cocos2d::ui;

MyPageScene* ListViewLayer::m_parentScene = NULL;

// on "init" you need to initialize your instance
bool ListViewLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B::WHITE) )
    {
        return false;
    }

    int l_thisHeight = WordCardConfigure::m_screenSize.height - WordCardConfigure::TOOL_BAR_HEIGHT - WordCardConfigure::TOOL_BAR_HEIGHT *1.5 - WordCardConfigure::TOOL_BAR_BOTTOM_HEIGHT;
    this->setContentSize(Size(WordCardConfigure::m_screenSize.width, l_thisHeight));

    // add word list
	CCLOG("MyWordLayer::init add m_listMyWords \n");
	m_lvWordList = ListView::create();
	m_lvWordList->setContentSize(Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN*2, this->getContentSize().height));
	m_lvWordList->setGravity(ListView::Gravity::CENTER_HORIZONTAL);
	m_lvWordList->setAnchorPoint(Point(0,0));
	m_lvWordList->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN,0));
	m_lvWordList->setDirection(ui::ScrollView::Direction::VERTICAL);
	m_lvWordList->setTouchEnabled(true);

	m_lvWordList->setBounceEnabled(true);
	m_lvWordList->setBackGroundImage("background.jpg");
	m_lvWordList->setBackGroundImageScale9Enabled(true);
	m_lvWordList->ignoreContentAdaptWithSize(true);

	this->addChild(m_lvWordList);

 	this->setTouchEnabled(true);
  	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
  	m_listener = EventListenerTouchOneByOne::create();
  	m_listener->setSwallowTouches(true);
  	m_listener->onTouchBegan = CC_CALLBACK_2(ListViewLayer::onTouchBegan, this);
  	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

    return true;
}

ListViewLayer* ListViewLayer::createListViewLayer(int myPageType)
{
	auto l_lvLayer = ListViewLayer::create();
	l_lvLayer->setPageType(myPageType);

	if (myPageType == MY_PAGE_TYPE_MY_WORD)
		l_lvLayer->setWordsData(m_parentScene->getMyWords());
  	else if (myPageType == MY_PAGE_TYPE_ARCHIVE)
  		l_lvLayer->setWordsData(m_parentScene->getArchivedWords());
  	else
  	{
  		// TODO assert
  	}

	return l_lvLayer;
}

void ListViewLayer::refreshListViewData(void)
{
	m_lvWordList->setContentSize(Size(WordCardConfigure::m_screenSize.width - WordCardConfigure::LEFT_MARGIN*2, this->getContentSize().height));
	m_lvWordList->setGravity(ListView::Gravity::CENTER_HORIZONTAL);
	m_lvWordList->setAnchorPoint(Point(0,0));
	m_lvWordList->setPosition(Vec2(WordCardConfigure::LEFT_MARGIN,0));
	m_lvWordList->setDirection(ui::ScrollView::Direction::VERTICAL);
	m_lvWordList->setTouchEnabled(true);

	m_lvWordList->setBounceEnabled(true);
	m_lvWordList->setBackGroundImage("background.jpg");
	m_lvWordList->setBackGroundImageScale9Enabled(true);
	m_lvWordList->ignoreContentAdaptWithSize(true);


	Size size = Size(getContentSize().width, WordCardConfigure::ICON_HEIGHT);

	m_lvWordList->removeAllChildren();

	for (int i = 0; i < m_words->size() ; ++i)
	{
		std::string l_lessonId = WordCardConfigure::numberToString(m_words->at(i).lessonId );
		CCLOG("myword index i = %d, lesson = %s \n", i, l_lessonId.c_str() );

		for (int j = 0; j <m_words->at(i).words.size() ; ++j)
		{
			auto l_layout = Layout::create();
			l_layout->setContentSize(size);

			// lessonId
			Text* l_lesson = Text::create(l_lessonId.c_str(), "", 36);
			l_lesson->setContentSize(Size(50, WordCardConfigure::ICON_HEIGHT));
			l_lesson->setAnchorPoint(Point(0,0));
			l_lesson->setColor(Color3B::BLACK);
			l_lesson->setPosition(Point(WordCardConfigure::LEFT_MARGIN *3, 0));
			l_layout->addChild(l_lesson, 0, "lessonId");

			// wordId - hidden in the listview
			int l_wordId = m_words->at(i).words[j].wordId;
			Text* l_myWordId= Text::create(WordCardConfigure::numberToString(l_wordId).c_str(), "", 36);
			l_myWordId->setVisible(false);
			l_layout->addChild(l_myWordId, 0, "wordId");

			// word
			std::string l_word = m_words->at(i).words[j].word;
			CCLOG("l_myWord index= %d, wordId=%d, word=%s \n", i, l_wordId, l_word.c_str());
			Text* l_myWord= Text::create(l_word.c_str(), "", 36);
			l_myWord->setContentSize(Size(200, WordCardConfigure::ICON_HEIGHT));
			l_myWord->setAnchorPoint(Point(0, 0));
			l_myWord->setColor(Color3B::BLACK);
			l_myWord->setPosition(Point(WordCardConfigure::LEFT_MARGIN *4 + 50, 0));
			l_layout->addChild(l_myWord, 0, "word");

			// recover button
			Button* l_btRecover = Button::create();
			l_btRecover->loadTextures("icons/recover_0.png", "icons/recover_1.png", "");
			l_btRecover->setContentSize(Size(WordCardConfigure::ICON_HEIGHT, WordCardConfigure::ICON_HEIGHT));
			l_btRecover->setAnchorPoint(Point(0,0));
			l_btRecover->setPosition(Point(this->getContentSize().width - WordCardConfigure::LEFT_MARGIN*3 - WordCardConfigure::ICON_HEIGHT*2, 0));
			l_btRecover->setScaleX(WordCardConfigure::ICON_HEIGHT/ l_btRecover->getContentSize().width);
			l_btRecover->setScaleY(WordCardConfigure::ICON_HEIGHT/ l_btRecover->getContentSize().height);
			l_btRecover->setTitleText("recover");
			l_btRecover->addTouchEventListener(CC_CALLBACK_2(ListViewLayer::onRecoverButtonTouched, this));
			l_layout->addChild(l_btRecover);

			if (m_myPageType == MY_PAGE_TYPE_MY_WORD)
			{
				// archive button for myWord layer
				Button* l_btArchiving = Button::create();
				l_btArchiving->loadTextures("icons/archive_0.jpg", "icons/archive_1.jpg", "");
				l_btArchiving->setContentSize(Size(WordCardConfigure::ICON_HEIGHT, WordCardConfigure::ICON_HEIGHT));
				l_btArchiving->setAnchorPoint(Point(0,0));
				l_btArchiving->setPosition(Point(this->getContentSize().width - WordCardConfigure::LEFT_MARGIN*2 - WordCardConfigure::ICON_HEIGHT, 0));
				l_btArchiving->setScaleX(WordCardConfigure::ICON_HEIGHT/ l_btArchiving->getContentSize().width);
				l_btArchiving->setScaleY(WordCardConfigure::ICON_HEIGHT/ l_btArchiving->getContentSize().height);
				l_btArchiving->setTitleText("archive");
				l_btArchiving->addTouchEventListener(CC_CALLBACK_2(ListViewLayer::onArchivingButtonTouched, this));
				l_layout->addChild(l_btArchiving);
			}
			else // MY_PAGE_TYPE_ARCHIVE
			{
				// myWord button for archive layer
				Button* l_btMyWord = Button::create();
				l_btMyWord->loadTextures("icons/favorite_0.jpg", "icons/favorite_1.jpg", "");
				l_btMyWord->setContentSize(Size(WordCardConfigure::ICON_HEIGHT, WordCardConfigure::ICON_HEIGHT));
				l_btMyWord->setAnchorPoint(Point(0,0));
				l_btMyWord->setPosition(Point(this->getContentSize().width - WordCardConfigure::LEFT_MARGIN*2 - WordCardConfigure::ICON_HEIGHT, 0));
				l_btMyWord->setScaleX(WordCardConfigure::ICON_HEIGHT/ l_btMyWord->getContentSize().width);
				l_btMyWord->setScaleY(WordCardConfigure::ICON_HEIGHT/ l_btMyWord->getContentSize().height);
				l_btMyWord->setTitleText("myWord");
				l_btMyWord->addTouchEventListener(CC_CALLBACK_2(ListViewLayer::onMyWordButtonTouched, this));
				l_layout->addChild(l_btMyWord);
			}

			m_lvWordList->addChild(l_layout);
		}
	}

	m_lvWordList->setItemsMargin(10);
}

void ListViewLayer::onRecoverButtonTouched(Ref *pSender, Widget::TouchEventType type)
{
	if( type == Widget::TouchEventType::ENDED)
	{
		doRecover();
	}
}

void ListViewLayer::onArchivingButtonTouched(Ref* pSender, Widget::TouchEventType type)
{
	if( type == Widget::TouchEventType::ENDED)
	{
		addArchive();
	}
}

void ListViewLayer::onMyWordButtonTouched(Ref* pSender, Widget::TouchEventType type)
{
	if( type == Widget::TouchEventType::ENDED)
	{
		addMyWord();
	}
}


void ListViewLayer::doRecover(void)
{
	if (m_myPageType == MY_PAGE_TYPE_MY_WORD)
		m_parentScene->m_myPageValue->removeMyWord(_getCurrentItem_LessonId(), _getCurrentItem_WordId());
	else
		m_parentScene->m_myPageValue->removeArchivedWord(_getCurrentItem_LessonId(), _getCurrentItem_WordId());

	m_lvWordList->removeItem(m_lvWordList->getCurSelectedIndex());

}

void ListViewLayer::addArchive(void)
{
	m_parentScene->m_myPageValue->addArchivedWord(_getCurrentItem_LessonId(), _getCurrentItem_WordId(), _getCurrentItem_Word());
}

void ListViewLayer::addMyWord(void)
{
	m_parentScene->m_myPageValue->addMyWord(_getCurrentItem_LessonId(), _getCurrentItem_WordId(), _getCurrentItem_Word());
}

int ListViewLayer::_getCurrentItem_LessonId(void)
{
	Layout* l_layout = static_cast<Layout*>(m_lvWordList->getItem(m_lvWordList->getCurSelectedIndex()));
	Text* l_lessonIdText = static_cast<Text*>(l_layout->getChildByName("lessonId"));

	return atoi(l_lessonIdText->getString().c_str());
}

int ListViewLayer::_getCurrentItem_WordId(void)
{
	Layout* l_layout = static_cast<Layout*>(m_lvWordList->getItem(m_lvWordList->getCurSelectedIndex()));
	Text* l_wordIdText = static_cast<Text*>(l_layout->getChildByName("wordId"));

	return atoi(l_wordIdText->getString().c_str());
}

std::string	ListViewLayer::_getCurrentItem_Word(void)
{
	Layout* l_layout = static_cast<Layout*>(m_lvWordList->getItem(m_lvWordList->getCurSelectedIndex()));
	Text* l_wordText = static_cast<Text*>(l_layout->getChildByName("word"));

	return l_wordText->getString();
}

void ListViewLayer::setParentScene(MyPageScene* parent)
{
	//if (NULL == m_parentScene)
		m_parentScene = parent;
}

