//
//  UIMaskLayerView.cpp
//  Pay
//
//  Created by Ben on 6/27/13.
//
//

#include "UIMaskLayerView.h"
UIMaskLayerView::UIMaskLayerView()
{
    
}
UIMaskLayerView::~UIMaskLayerView()
{
    
}

bool UIMaskLayerView::init()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor* clayer = CCLayerColor::create(ccc4(88, 88, 88, 244), size.width, size.height);
    this->addChild(clayer);
    return true;
}

void UIMaskLayerView::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1000, true);
}

void UIMaskLayerView::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

