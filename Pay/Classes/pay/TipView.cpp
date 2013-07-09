//
//  TipView.cpp
//  Navigations
//
//  Created by Ben on 6/3/13.
//
//

#include "TipView.h"

TipView::TipView()
{
    
}
TipView::~TipView()
{
    
}

TipView* TipView::create(const char* msg, CCNode* parent, CCPoint pt, float daleyTimer, bool bIsFadeOut)
{
    TipView* pRet = new TipView();
    if (pRet && pRet->init(msg, parent, pt, daleyTimer, bIsFadeOut))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool TipView::init(const char* msg, CCNode* parent, CCPoint pt, float daleyTimer, bool bIsFadeOut)
{
    m_msg = std::string(msg);
    m_parent = parent;
    m_pt = CCPointMake(pt.x, pt.y) ;
    m_daleyTimer = daleyTimer;
    m_bIsFadeOut = bIsFadeOut;
    show();
    return true;
}


void TipView::show()
{
    m_label = CCLabelTTF::create(m_msg.c_str(), "Helvetica", 22);
    m_label->setColor(ccc3(255, 255, 255));
    m_label->setOpacity(0);
    CCLog("m_msg%s",m_msg.c_str());
    
    CCSize mSize = m_label->getContentSize();
    CCRect imgRect = CCRectMake(0, 0, 40, 40);
    CCRect rect = CCRectMake(0, 0, mSize.width+40, mSize.height+40);//根据文字长度
    CCRect rectInsets = CCRectMake(8,8,24,24);
    cocos2d::extension::CCScale9Sprite* m_pScale9Sprite;
    m_pScale9Sprite = cocos2d::extension::CCScale9Sprite::create("bg_112x46.png", imgRect, rectInsets);
    m_pScale9Sprite->setContentSize(CCSizeMake(rect.size.width, rect.size.height));
    this->addChild(m_pScale9Sprite);
    this->addChild(m_label);
    this->setPosition(m_pt);
    
    m_parent->addChild(this);
    CCMoveBy *moveBy = CCMoveBy::create(2, ccp(0, 120));
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(TipView::onActionEnd));
    CCSequence *sequence = (CCSequence *)CCSequence::create(moveBy, call, NULL);
    this->runAction(sequence);
    
    if (m_bIsFadeOut)
    {
        CCFadeIn* pFadeIn = CCFadeIn::create(0.6);
        CCDelayTime* pDelay = CCDelayTime::create(0.6);
        CCFadeOut* pFadeOut = CCFadeOut::create(0.8);
        CCSequence* pSeq = CCSequence::create(pFadeIn,pDelay,pFadeOut,NULL);
        m_pScale9Sprite->runAction(pSeq);
        
        CCFadeTo* pFadeTo = CCFadeTo::create(0.6, 255);
        CCDelayTime* pFadeToTime = CCDelayTime::create(0.6);
        CCFadeTo* pFadeToOut = CCFadeTo::create(0.8, 0);
        pSeq = CCSequence::create(pFadeTo,pFadeToTime,pFadeToOut,NULL);
        m_label->runAction(pSeq);
        
        /*CCFadeTo* fadeTo = CCFadeTo::create(1.0, 0);
        m_label->runAction(fadeTo);
        CCFadeOut* fadeOut = CCFadeOut::create(1.1);
        m_pScale9Sprite->runAction(fadeOut);*/
    }
}

void TipView::onActionEnd()
{
    this->removeFromParentAndCleanup(true);
}



