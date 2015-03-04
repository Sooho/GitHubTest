/****************************************************************************
Copyright (c) 2013 Artavazd Barseghyan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "GestureRecognizer.h"

USING_NS_CC;

GestureRecognizer::GestureRecognizer()
{
    isRecognizing = false;
    
    dispatcher = Director::sharedDirector()->getEventDispatcher();

/*	this->setTouchEnabled(true);

	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(WordCardLayer::onTouchBegan, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(WordCardLayer::onTouchMoved, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(WordCardLayer::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
*/
    
    setTouchEnabled(true);
    setCancelsTouchesInView(false);
}

GestureRecognizer::~GestureRecognizer()
{
   // dispatcher->removeDelegate(this);  TODO
}

void GestureRecognizer::setTarget(CCObject * tar, SEL_CallFuncO sel)
{
    target = tar;
    selector = sel;
}

float GestureRecognizer::distanceBetweenPoints(Point p1, Point p2)
{
    float deltaX = p2.x-p1.x;
    float deltaY = p2.y-p1.y;
    return fabs(sqrtf(deltaX*deltaX+deltaY*deltaY));
}

void GestureRecognizer::stopTouchesPropagation(Set * pTouches, Event * pEvent)
{
    //hack! cancel touch so it won't propagate
 //   dispatcher->touchesCancelled(pTouches, pEvent); TODO
}

void GestureRecognizer::setParent(Node*p)
{
    Layer::setParent(p);
    
    if (p!=NULL) {
        CCSize size = p->getContentSize();
        setContentSize(size);
        setPosition(p->getPosition());
        frame = p->boundingBox();
    }
}

CCSet * GestureRecognizer::createSetWithTouch(Touch * pTouch)
{
    Set * set = new Set();
    set->addObject(pTouch);
    return set;
}

/*
void GestureRecognizer::registerWithTouchDispatcher()
{
   // dispatcher->addTargetedDelegate(this, -256, false); // TODO
}
*/

bool GestureRecognizer::isPositionBetweenBounds(Point pos)
{
    return frame.containsPoint(pos);
}

void GestureRecognizer::gestureRecognized(cocos2d::Object * gesture)
{
    if (target && selector) (target->*selector)(gesture); //call selector
}
