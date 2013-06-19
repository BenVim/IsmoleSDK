//
//  GameUIBigMaskLayer.cpp
//  Navigations
//
//  Created by Yao on 13-1-24.
//
//

#include "GameUIBigMaskLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

GameUIBigMaskLayer::GameUIBigMaskLayer()
{
    
}

GameUIBigMaskLayer::~GameUIBigMaskLayer()
{
    
}

void GameUIBigMaskLayer::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -130, true);
}