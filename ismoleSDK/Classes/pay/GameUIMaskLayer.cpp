//
//  GameUIMaskLayer.cpp
//  SanguoX
//
//  Created by  ismole04 on 12-12-26.
//
//

#include "GameUIMaskLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

GameUIMaskLayer::GameUIMaskLayer()
{
    
}

GameUIMaskLayer::~GameUIMaskLayer()
{
    
}

void GameUIMaskLayer::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void GameUIMaskLayer::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool GameUIMaskLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint pt = pTouch->getLocation();
    pt = convertToWorldSpace(pt);
    CCRect ret = boundingBox();
    pt = ccpAdd(pt, ccp(-ret.origin.x,-ret.origin.y));
    if (ret.containsPoint(pt))
    {
        return true;
    }
    return false;
}

SEL_MenuHandler GameUIMaskLayer::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char*  pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler GameUIMaskLayer::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char*  pSelectorName)
{
    return NULL;
}

bool GameUIMaskLayer::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char*  pMemberVariableName, cocos2d::CCNode * pNode)
{
    return false;
}

void GameUIMaskLayer::onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader)
{
}