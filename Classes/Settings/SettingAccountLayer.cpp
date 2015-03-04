#include <string>
#include "cocos2d.h"
#include "WordCardConfigure.h"
#include "SettingAccountLayer.h"
#include "SettingScene.h"

USING_NS_CC;
class SettingScene;;
SettingScene* SettingAccountLayer::m_parentScene = NULL;
bool SettingAccountLayer::init()
{
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    	setAccountLayer();

    	    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    	     auto listener = EventListenerTouchOneByOne::create();
    		listener->setSwallowTouches (true);
    		listener->onTouchBegan=CC_CALLBACK_2(SettingAccountLayer::onTouchBegan, this);
    		dispatcher -> addEventListenerWithSceneGraphPriority(listener,this);

   return true;
}

void	SettingAccountLayer::setParentScene(SettingScene* parent)
{
	if (NULL == m_parentScene)
			m_parentScene = parent;
}
void SettingAccountLayer::setAccountLayer(){

	//add child (accountLayer)
		auto bgLayer3 = Layer::create();
		bgLayer3->setAnchorPoint(Vec2(0,0));
		bgLayer3->setPosition(Vec2(0, -200));
		this->addChild(bgLayer3);

	    auto btn_accountback_spr = Sprite::create("btn_back.png");
	   	btn_accountback_spr->setAnchorPoint(Vec2::ZERO);
	   	btn_accountback_spr->setPosition(Vec2(0, WordCardConfigure::m_screenSize.height-50));
	   	btn_accountback_spr->setTag(31);
	   	this->addChild(btn_accountback_spr,31);

		auto labeltitle = LabelTTF::create("계정","Arial",40);
		labeltitle->setAnchorPoint(Point(0.5, 0));
		labeltitle->setPosition(Point(WordCardConfigure::m_screenSize.width/2, WordCardConfigure::m_screenSize.height-100));
		labeltitle->setColor(Color3B(0,0,0));
		this->addChild(labeltitle);

	    for(int i=0; i<6; i++)
	   					{
	   						auto line_spr=Sprite::create("line.png");
	   						line_spr->setAnchorPoint(Point::ZERO);
	   						line_spr->setPosition(Point(0, WordCardConfigure::m_screenSize.height-WordCardConfigure::m_screenSize.height*0.08*i));
	   						bgLayer3->addChild(line_spr);

	   					}

	   				std::string str3[6]={"1111","2222","3333","4444","55555","66666"};
	   				for(int i=0; i<6; i++)
	   					{
	   						auto label1 = LabelTTF::create(str3[i],"Arial",25);
	   						label1->setAnchorPoint(Point::ZERO);
	   						label1->setPosition(Point(WordCardConfigure::m_screenSize.width*0.08, WordCardConfigure::m_screenSize.height-WordCardConfigure::m_screenSize.height*0.08*i));
	   						label1->setColor(Color3B(0,0,0));
	   						bgLayer3->addChild(label1);
	   					}
}

bool SettingAccountLayer::onTouchBegan(Touch* touch, Event* event)
{
   //	auto target=event->getCurrentTarget();
	//Point pos = target -> convertToNodeSpace(touch->getLocation());

	Point pos = touch->getLocation();
	if(!this->getBoundingBox().containsPoint(pos))
	{
	    	CCLog("Not account layer Box[%s]\n",__func__);
		   return false;
	}
	if(this->getBoundingBox().containsPoint(pos))
	{

		CCLog("account.x:%f \n account.y:%f", pos.x, pos.y);

     }
	//Point childpos = this->convertToWorldSpace(getChildByTag(31)->getPosition());
	//Point childpos = this->getChildByTag(31)->getPosition();

//	  if (isPointIn(this->getChildByTag(31), pos))
//
//	    {
//			CCLog("m_account31 location!!");
//			m_parentScene->reversMoveAc();
//	    }
//	auto target=event->getCurrentTarget();
//	Point targetpos = target->getPosition();;

//    Rect boundingBox = getChildByTag(TAG_SPRITE)->boundingBox();

//	if(this->getChildByTag(31)->getBoundingBox().containsPoint(targetpos))
    if(_isPointIn(this->getChildByTag(31), pos)==true)
	{
		CCLog("m_account31 location!!");
		m_parentScene->_reversMoveAc(2);
	}

    //Rect boundingBox =this-> getChildByTag(31)->boundingBox();
   //CCLog("boundingBox.originx:%f \n boundingBox.originy:%f\n boundingBox.width:%f\n boundingBox.height:%f", boundingBox.x, boundingBox.y, boundingBox.width,boundingBox.height);
   //CCLog("childByTag(31).x:%f \n childByTag(31).y:%f",childpos.x, childpos.y);
		return true;

}
bool SettingAccountLayer::_isPointIn(Node* sender, const Point &worldPoint)
{
    Point o =this->convertToWorldSpace(sender->boundingBox().origin);
    Rect rect = CCRectMake(o.x, o.y, sender->boundingBox().size.width, sender->boundingBox().size.height);

    return rect.containsPoint(worldPoint);
}

void SettingAccountLayer::_moveAc()
{
	CCLog("[%s]\n", __func__);
	auto action1=MoveTo::create(0.5, Point(0,0));
	auto action2=EaseInOut::create(action1,2);
	auto action3=Spawn::create(action1, action2, NULL);
	this -> runAction(action3);
}
void SettingAccountLayer::_reversMoveAc()
{
	CCLog("[%s]\n", __func__);
	auto action1=MoveTo::create(0.2, Point(WordCardConfigure::m_screenSize.width,0));
	auto action2=EaseInOut::create(action1,1);
	auto action3=Spawn::create(action1, action1, NULL);
	this -> runAction(action3);
}
