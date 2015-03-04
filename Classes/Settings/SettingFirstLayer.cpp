#include <string>
#include "cocos2d.h"
#include "SettingFirstLayer.h"
#include "WordCardConfigure.h"
#include "SettingScene.h"
#include "WordCardLayer.h"

USING_NS_CC;
class SettingScene;

SettingScene* SettingFirstLayer::m_parentScene = NULL;

bool SettingFirstLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }

        setFirstLayer();

	    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan=CC_CALLBACK_2(SettingFirstLayer::onTouchBegan, this);
		listener->onTouchMoved=CC_CALLBACK_2(SettingFirstLayer::onTouchMoved, this);
		listener->onTouchEnded=CC_CALLBACK_2(SettingFirstLayer::onTouchEnded, this);
		listener->onTouchCancelled=CC_CALLBACK_2(SettingFirstLayer::onTouchCancelled, this);
		dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}
void	SettingFirstLayer::setParentScene(SettingScene* parent)
{
	if (NULL == m_parentScene)
			m_parentScene = parent;
}
void SettingFirstLayer::setFirstLayer()
{
	//Layer for blindAnimation
		auto blindLayer = LayerColor::create(Color4B(0, 0, 0, 0));
		blindLayer->setContentSize(Size(WordCardConfigure::m_screenSize.width, WordCardConfigure::m_screenSize.height));
		blindLayer->setAnchorPoint(Point::ZERO);
		blindLayer->setTag(11);
		this->addChild(blindLayer,2);

		auto btn_back_spr = Sprite::create("btn_back0.png");
		btn_back_spr->setAnchorPoint(Point::ZERO);
		btn_back_spr->setPosition(Point(0, WordCardConfigure::m_screenSize.height-50));
		btn_back_spr->setTag(12);
		this->addChild(btn_back_spr, 0);

		auto btn_close_spr = Sprite::create("btn_close0.png");
		btn_close_spr->setAnchorPoint(Point::ZERO);
		btn_close_spr->setPosition(Point(WordCardConfigure::m_screenSize.width-120, WordCardConfigure::m_screenSize.height-50));
		btn_close_spr->setTag(13);
		this->addChild(btn_close_spr, 0);

		auto labeltitle = LabelTTF::create("Setting","Arial",40);
		labeltitle->setAnchorPoint(Point(0.5, 0));
		labeltitle->setPosition(Point(WordCardConfigure::m_screenSize.width/2, WordCardConfigure::m_screenSize.height-100));
		labeltitle->setColor(Color3B(0,0,0));
		this->addChild(labeltitle);

   //Layer for line up sprits under button_spr
		m_bgLayer = Layer::create();
		m_bgLayer->setAnchorPoint(Point::ZERO);
		m_bgLayer->setPosition(Point(0, -200));
		this->addChild(m_bgLayer);

		auto bg_dragbtn_spr = Sprite::create("bg_setting_btn.png");
		bg_dragbtn_spr->setAnchorPoint(Point(1,0));
		bg_dragbtn_spr->setPosition(Point(WordCardConfigure::m_screenSize.width-10, WordCardConfigure::m_screenSize.height-WordCardConfigure::m_screenSize.height*0.08*2));
		bg_dragbtn_spr->setTag(14);
		m_bgLayer->addChild(bg_dragbtn_spr,2);


		auto dragbtn_spr = Sprite::create("setting_drag_btn.png");
		dragbtn_spr->setAnchorPoint(Point(1,0));
		dragbtn_spr->setPosition(Point(WordCardConfigure::m_screenSize.width-60, WordCardConfigure::m_screenSize.height-WordCardConfigure::m_screenSize.height*0.08*2));
		dragbtn_spr->setTag(15);
		m_bgLayer->addChild(dragbtn_spr,3);
		btn_dragwordsound=m_bgLayer->convertToWorldSpace( m_bgLayer->getChildByTag(15)->boundingBox().origin);

		auto btn_next1= Sprite::create("btn_next.png");
		btn_next1->setAnchorPoint(Point(1,0));
		btn_next1 ->setPosition(Point(WordCardConfigure::m_screenSize.width, WordCardConfigure::m_screenSize.height-WordCardConfigure::m_screenSize.height*0.08*7));
		btn_next1 ->setTag(21);
		this->addChild(btn_next1,3);

		auto btn_next2= Sprite::create("btn_next.png");
		btn_next2->setAnchorPoint(Point(1,0));
		btn_next2->setPosition(Point(WordCardConfigure::m_screenSize.width, WordCardConfigure::m_screenSize.height-WordCardConfigure::m_screenSize.height*0.08*8));
		btn_next2->setTag(22);
		this ->addChild(btn_next2,3);

	    for(int i=0; i<6; i++)
		{
			auto line_spr=Sprite::create("line.png");
			line_spr->setAnchorPoint(Point::ZERO);
			line_spr->setPosition(Point(0, WordCardConfigure::m_screenSize.height-WordCardConfigure::m_screenSize.height*0.08*i));
			m_bgLayer->addChild(line_spr);
		}
		std::string str[6]={"레벨바꾸기","발음음성 download","퀴즈효과음","My word 알람으로 사용","Information","계정"};
		for(int i=0; i<6; i++)
		{
			auto label1 = LabelTTF::create(str[i],"Arial",25);
			label1->setAnchorPoint(Point::ZERO);
			label1->setPosition(Point(WordCardConfigure::m_screenSize.width*0.08, WordCardConfigure::m_screenSize.height-WordCardConfigure::m_screenSize.height*0.08*i));
			label1->setColor(Color3B(0,0,0));
			m_bgLayer->addChild(label1);
		}
}

bool SettingFirstLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = touch->getLocation();

		if(!this->getBoundingBox().containsPoint(pos))
		{
			//CCLog("Not account layer Box[%s]\n",__func__);
			return false;
		}
		if(this->getChildByTag(21)->getBoundingBox().containsPoint(pos))
		{
			//CCLog("account.x:%f \n account.y:%f", pos.x, pos.y);
			m_parentScene->_moveAc(1);
	     }
		if(this->getChildByTag(22)->getBoundingBox().containsPoint(pos))
		{
			//CCLog("account.x:%f \n account.y:%f", pos.x, pos.y);
			m_parentScene->_moveAc(2);
	     }

//	Point pp = m_bgLayer->convertToWorldSpace( m_bgLayer->getChildByTag(15)->boundingBox().origin);
//
//	if(_isPointIn(m_bgLayer->getChildByTag(15), pos)==true)
//	{
//		int mnum_x=float(btn_dragwordsound.x)+50;
//		int mnum_y=float(btn_dragwordsound.y);
//		CCLog("move_mnum_x:%f \move_mnum_y:%f",float(mnum_x),float(mnum_y));
//		_btnMoveAc(mnum_x, mnum_y);
//	}
	return true;

}
void SettingFirstLayer::onTouchMoved(Touch *touch, Event* event)
{


}


void SettingFirstLayer::onTouchEnded(Touch *touch, Event* event)
{


}

void SettingFirstLayer::onTouchCancelled(Touch *touch, Event* event)
{

	Point pos = touch->getLocation();
	//CCLog("touch.x:%f \n touch.y:%f", pos.x, pos.y);
}

// make bounding box of childNode touch
bool SettingFirstLayer::_isPointIn(Node* sender, const Point &worldPoint)
{
    Point o =m_bgLayer->convertToWorldSpace(sender->boundingBox().origin);
    Rect rect = CCRectMake(o.x, o.y, sender->boundingBox().size.width, sender->boundingBox().size.height);

    return rect.containsPoint(worldPoint);
}

//touch
void SettingFirstLayer::_moveAc()
{
	//CCLog("[%s]\n", __func__);
	auto action_1=FadeTo::create(0.2, 255);
	this-> getChildByTag(11)-> runAction(action_1);
}

void SettingFirstLayer::_reversMoveAc()
{
	//CCLog("[%s]\n", __func__);
	auto action_1=FadeTo::create(0.5, 0);
	auto action_2=action_1->reverse();
	auto action_3= Sequence::create(action_1, action_2, NULL);
	this->getChildByTag(11) -> runAction(action_3);
}

void SettingFirstLayer::_btnMoveAc(int mnum_x, int mnum_y)
{
	CCLog("btnMoveAc[%d]\nbtnMoveAc[%d]",mnum_x,  mnum_y);
	auto action_1=MoveTo::create(0.2,Point(mnum_x, mnum_y));
	m_bgLayer -> getChildByTag(15)-> runAction(action_1);
 }

