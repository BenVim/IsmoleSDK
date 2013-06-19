//
//  LoadingView.cpp
//  Navigations
//
//  Created by Yao on 13-1-24.
//
//

#include "LoadingView.h"

USING_NS_CC;
USING_NS_CC_EXT;

LoadingView::LoadingView():
m_pLoadingCCNode(NULL),
m_pAnimFrmes(NULL),
m_pLoadingCCLayer(NULL)
{
    
}

LoadingView::~LoadingView()
{
    if (m_pAnimFrmes) {
        m_pAnimFrmes->removeAllObjects();
        CC_SAFE_RELEASE(m_pAnimFrmes);
        m_pAnimFrmes = NULL;
    }
    CC_SAFE_RELEASE(m_pLoadingCCNode);
    CC_SAFE_RELEASE(m_pLoadingCCLayer);
}

void LoadingView::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -200, true);
}

void LoadingView::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool LoadingView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
        return true;

}

SEL_MenuHandler LoadingView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

SEL_CCControlHandler LoadingView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){
	return NULL;
}

bool LoadingView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "LoadingCCNode:", cocos2d::CCNode *, this->m_pLoadingCCNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "LoadingCCLayer:", cocos2d::CCLayer *, this->m_pLoadingCCLayer);
	return false;
}

void LoadingView::onNodeLoaded(cocos2d::CCNode * pNode,  CCNodeLoader * pNodeLoader) {
	initView();
}

void LoadingView::initView()
{
    m_pLoadingCCLayer->setVisible(false);
    m_pLoadingCCNode->runAction(CCSequence::create(CCDelayTime::create(0.4f),CCCallFunc::create(this, callfunc_selector(LoadingView::showAnim)),NULL));
}

void LoadingView::showAnim()
{
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
    m_pLoadingCCNode->addChild(loading);
    loading->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    m_pLoadingCCLayer->setVisible(true);

}