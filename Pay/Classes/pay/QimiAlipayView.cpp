//
//  QimiAlipayView.cpp
//  Pay
//
//  Created by Ben on 6/25/13.
//
//

#include "QimiAlipayView.h"
#include "GameUtils.h"
#include "Qimi.h"
#include "QimiUserModel.h"
#include "QimiPlatform.h"
#include "QimiMD5.h"


QimiAlipayView::QimiAlipayView():isSelelcted(NULL)
{
    
}

QimiAlipayView::~QimiAlipayView()
{
    
}

bool QimiAlipayView::init()
{
    CCSize m_size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* bg = CCSprite::create("bg_dabeijing_480x800.png");
    bg->setPosition(ccp(m_size.width/2, m_size.height/2));
    this->addChild(bg);
    
    CCSprite* bgTop = CCSprite::create("bg_top.png");
    this->addChild(bgTop);
    bgTop->setPosition(ccp(m_size.width/2, m_size.height-bgTop->getContentSize().height/2));
    
    
    CCControlButton* backBtn = CCControlButton::create(CCScale9Sprite::create("btn_fanhui.png"));
    backBtn->setPreferredSize(CCSizeMake(101, 51));
    this->addChild(backBtn);
    backBtn->setPosition(ccp(63, 760));
    backBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(QimiAlipayView::backOnClick),
                                                 CCControlEventTouchUpInside);
    
    
    CCControlButton* helpBtn = CCControlButton::create(CCScale9Sprite::create("btn_bangzhu.png"));
    helpBtn->setPreferredSize(CCSizeMake(93, 51));
    this->addChild(helpBtn);
    helpBtn->setPosition(ccp(420, 760));
    
    CCLabelTTF* topText = CCLabelTTF::create("奇米网支付中心", "Helvetica", 28);
    this->addChild(topText);
    topText->setPosition(ccp(240, 762));
    
    
    ////////////公共部分结束
    
    
    CCRect form = CCRectMake(0, 0, 40, 40);
    CCRect capInset = CCRectMake(10, 10, 10, 10);
    CCScale9Sprite* scale9Sprite = CCScale9Sprite::create("bg_40x40.png", form, capInset);
    scale9Sprite->setContentSize(CCSizeMake(445, 580));
    scale9Sprite->setPosition(ccp(240, 400));
    this->addChild(scale9Sprite);
    

    CCLabelTTF* txtTitle = CCLabelTTF::create("请选择充值金额（1元=10奇米币）", "Helvetica", 26);
    this->addChild(txtTitle);
    txtTitle->setColor(ccc3(0, 0, 0));
    txtTitle->setPosition(ccp(27, 237));
    txtTitle->setAnchorPoint(ccp(0, 0.5));
    
    
    
    
    CCControlButton* m_pBtnCongzhi;
    
    CCControlButton* m_pBtn20Select;
    CCControlButton* m_pBtn30Select;
    CCControlButton* m_pBtn50Select;
    CCControlButton* m_pBtn100Select;
    CCControlButton* m_pBtn300Select;
    CCControlButton* m_pBtn500Select;
    
    
    CCControlButton* m_pBtn10Select = CCControlButton::create(CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn10Select->setPreferredSize(CCSizeMake(418, 75));
    this->addChild(m_pBtn10Select);
    m_pBtn10Select->setPosition(ccp(240, 200));
    m_pBtn10Select->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiAlipayView::backOnClick),
                                                    CCControlEventTouchUpInside);
   
    
    
    
    
    
    return true;
}





