//
//  QimiAlipayDailog.cpp
//  Pay
//
//  Created by Ben on 7/5/13.
//
//

#include "QimiAlipayDailog.h"
#include "GameUtils.h"
#include "Qimi.h"
#include "QimiPlatform.h"
#include "UIMaskLayerView.h"

QimiAlipayDailog::QimiAlipayDailog()
{
    
}

QimiAlipayDailog::~QimiAlipayDailog()
{
    
}

bool QimiAlipayDailog::init()
{
    UIMaskLayerView* mask = UIMaskLayerView::create();
    this->addChild(mask);
    
    CCSize m_size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create("bg_372x301.png");
    bg->setPosition(ccp(m_size.width/2, m_size.height/2));
    this->addChild(bg);
    
    CCControlButton* m_pSussfulBtn = CCControlButton::create(CCScale9Sprite::create("btn_zhifuwancheng.png"));
    m_pSussfulBtn->setPreferredSize(CCSizeMake(135, 47));
    m_pSussfulBtn->setTouchPriority(-1000);
    this->addChild(m_pSussfulBtn);
    m_pSussfulBtn->setPosition(ccp(m_size.width/2-85, m_size.height/2-100));
    m_pSussfulBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(QimiAlipayDailog::paySucssfuly),
                                                 CCControlEventTouchUpInside);
    
    CCControlButton* m_pFialdBtn = CCControlButton::create(CCScale9Sprite::create("btn_zhifushibai.png"));
    m_pFialdBtn->setPreferredSize(CCSizeMake(135, 47));
    m_pFialdBtn->setTouchPriority(-1000);
    this->addChild(m_pFialdBtn);
    m_pFialdBtn->setPosition(ccp(m_size.width/2+85, m_size.height/2-100));
    m_pFialdBtn->addTargetWithActionForControlEvents(this,
                                                       cccontrol_selector(QimiAlipayDailog::backOnClick),
                                                       CCControlEventTouchUpInside);
    
    CCLabelTTF* txt = CCLabelTTF::create("完成付款后请根据您的情况点击下面的按钮！", "Helvetica", 24,CCSizeMake(300, 60), kCCTextAlignmentLeft);
    txt->setColor(ccc3(0, 0, 0));
    this->addChild(txt);
    txt->setPosition(ccp(m_size.width/2, m_size.height/2));
    
    return true;
}

void QimiAlipayDailog::paySucssfuly(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    CCInteger* pObj = CCInteger::create(1);
    QimiPlatform::shareQimiPlatform()->callPayBack(pObj);
    backOnClick(NULL, NULL);
}

void QimiAlipayDailog::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}





