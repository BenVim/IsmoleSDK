//
//  RequestLoadingView.cpp
//  Pay
//
//  Created by Ben on 6/27/13.
//
//

#include "RequestLoadingView.h"

RequestLoadingView::RequestLoadingView()
{
    
}
RequestLoadingView::~RequestLoadingView()
{
    
}

bool RequestLoadingView::init()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor* clayer = CCLayerColor::create(ccc4(0, 0, 0, 55), size.width, size.height);
    this->addChild(clayer);
    
    
    CCNode* loadingCCNode = CCNode::create();
    this->addChild(loadingCCNode);
    

    m_pAnimFrmes = CCArray::createWithCapacity(10);
    m_pAnimFrmes->retain();
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("loading.plist");
    
    CCSprite* loading = CCSprite::createWithSpriteFrameName("loading_2.png");
    loading->setPosition(ccp(240, 400));
    char str[100] = {0};
    for(int i = 1; i < 11; i++)
    {
        sprintf(str, "loading_%i.png",(i+1));
        //CCLog(str);
        CCSpriteFrame *frame = cache->spriteFrameByName(str);
        m_pAnimFrmes->addObject(frame);
    }
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(m_pAnimFrmes, 0.08f);
    loadingCCNode->addChild(loading);
    loading->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    
    return true;
}

void RequestLoadingView::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1000, true);
}

void RequestLoadingView::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

