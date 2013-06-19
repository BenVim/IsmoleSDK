//
//  GameScrollView.cpp
//  Navigations
//
//  Created by Yao on 13-1-28.
//
//

#include "GameScrollView.h"

USING_NS_CC;

GameScrollView::GameScrollView():
CCScrollView()
{
    
}
GameScrollView::~GameScrollView()
{
    //m_pTouches->release();
}

GameScrollView* GameScrollView::create(cocos2d::CCSize size, cocos2d::CCNode* container/* = NULL*/)
{
    GameScrollView* pRet = new GameScrollView();
    if (pRet && pRet->initWithViewSize(size, container))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void GameScrollView::registerWithTouchDispatcher()
{
   CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -130, false);
}

void GameScrollView::onExit()
{
    CCLayer::onExit();
    //CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
