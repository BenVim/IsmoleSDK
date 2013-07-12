//
//  QimiPrepaidCardView.cpp
//  Pay
//
//  Created by Ben on 6/25/13.
//
//

#include "QimiPrepaidCardView.h"
#include "GameUtils.h"
#include "Qimi.h"
#include "QimiUserModel.h"
#include "QimiPlatform.h"
#include "QimiMD5.h"
#include "QimiPlatformIOS.h"
#include "QimiPrepaidCardNextView.h"
#include "StageScene.h"

#include "UIMaskLayerView.h"


QimiPrepaidCardView::QimiPrepaidCardView()
{
    
}

QimiPrepaidCardView::~QimiPrepaidCardView()
{
    CC_SAFE_RELEASE(m_pButtonList);
}

bool QimiPrepaidCardView::init()
{
    m_pButtonList = CCArray::create();
    m_pButtonList->retain();
    
    UIMaskLayerView* mask = UIMaskLayerView::create();
    this->addChild(mask);
    
    CCSize m_size = CCDirector::sharedDirector()->getWinSize();
    
    
    CCNode* container = CCNode::create();
    this->addChild(container);
    container->setTag(100);
    container->setPosition(ccp(m_size.width/2, m_size.height/2-45));
    
    CCNode* topCCNode = CCNode::create();
    topCCNode->setPosition(ccp(m_size.width/2, m_size.height-45));
    this->addChild(topCCNode);
    
    
    
    CCSprite* bg = CCSprite::create("bg_dabeijing_480x800.png");
    bg->setPosition(ccp(0, 0));
    container->addChild(bg);
    
    /****top****/
    
    CCSprite* bgTop = CCSprite::create("bg_top.png");
    topCCNode->addChild(bgTop);
    bgTop->setPosition(ccp(0, 0));
    
    
    CCControlButton* backBtn = CCControlButton::create(CCScale9Sprite::create("btn_fanhui.png"));
    backBtn->setPreferredSize(CCSizeMake(101, 51));
    backBtn->setTouchPriority(-1000);
    topCCNode->addChild(backBtn);
    backBtn->setPosition(ccp(-163, 0));
    backBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(QimiPrepaidCardView::backOnClick),
                                                 CCControlEventTouchUpInside);
    
    
    CCControlButton* helpBtn = CCControlButton::create(CCScale9Sprite::create("btn_bangzhu.png"));
    helpBtn->setPreferredSize(CCSizeMake(93, 51));
    helpBtn->setTouchPriority(-1000);
    topCCNode->addChild(helpBtn);
    helpBtn->setPosition(ccp(163, 0));
    helpBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(QimiPrepaidCardView::qimiHelp),
                                                 CCControlEventTouchUpInside);
    
    CCLabelTTF* topText = CCLabelTTF::create("奇米支付中心", "Helvetica", 28);
    topText->setColor(ccc3(104, 67, 2));
    topCCNode->addChild(topText);
    topText->setPosition(ccp(0, 0));
    
    /**TOP END*/
    
    
    ////////////公共部分结束
    
    
    CCRect form = CCRectMake(0, 0, 40, 40);
    CCRect capInset = CCRectMake(10, 10, 10, 10);
    CCScale9Sprite* scale9Sprite = CCScale9Sprite::create("bg_40x40.png", form, capInset);
    scale9Sprite->setContentSize(CCSizeMake(445, 560));
    scale9Sprite->setPosition(ccp(0, 12));
    container->addChild(scale9Sprite);
    
    
    
//    CCNode* containerCCNode = CCNode::create();
//    this->addChild(containerCCNode);
//    containerCCNode->setPosition(ccp(0, 0));
    
    CCLabelTTF* txtTitle = CCLabelTTF::create("请选择充值金额（1元=10元宝）", "Helvetica", 26);
    container->addChild(txtTitle);
    txtTitle->setColor(ccc3(0, 0, 0));
    txtTitle->setPosition(ccp(-204, 259));
    txtTitle->setAnchorPoint(ccp(0, 0.5));
    
    
    CCControlButton* m_pBtnCongzhi = CCControlButton::create(CCScale9Sprite::create("btn_xiayibu.png"));
    m_pBtnCongzhi->setPreferredSize(CCSizeMake(93, 51));
    m_pBtnCongzhi->setTouchPriority(-1000);
    container->addChild(m_pBtnCongzhi);
    m_pBtnCongzhi->setPosition(ccp(0, -167));
    m_pBtnCongzhi->addTargetWithActionForControlEvents(this,
                                                       cccontrol_selector(QimiPrepaidCardView::nextOnClick),
                                                       CCControlEventTouchUpInside);
    
    
    
    
    CCLabelTTF* label10 = CCLabelTTF::create("10元", "Helvetica", 18);
    label10->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn10Select = CCControlButton::create(label10, CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn10Select->setBackgroundSpriteForState(CCScale9Sprite::create("bg_seleceted.png"), CCControlStateDisabled);
    m_pBtn10Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn10Select->setTouchPriority(-1000);
    container->addChild(m_pBtn10Select);
    m_pBtn10Select->setPosition(ccp(-104, 192));
    m_pBtn10Select->setTag(10);
    m_pBtn10Select->addTargetWithActionForControlEvents(this,
                                                        cccontrol_selector(QimiPrepaidCardView::selected),
                                                        CCControlEventTouchUpInside);
    
    
    CCLabelTTF* label20 = CCLabelTTF::create("20元", "Helvetica", 18);
    label20->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn20Select = CCControlButton::create(label20, CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn20Select->setBackgroundSpriteForState(CCScale9Sprite::create("bg_seleceted.png"), CCControlStateDisabled);
    m_pBtn20Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn20Select->setTouchPriority(-1000);
    container->addChild(m_pBtn20Select);
    m_pBtn20Select->setPosition(ccp(107, 192));
    m_pBtn20Select->setTag(20);
    m_pBtn20Select->addTargetWithActionForControlEvents(this,
                                                        cccontrol_selector(QimiPrepaidCardView::selected),
                                                        CCControlEventTouchUpInside);
    
    CCLabelTTF* label30 = CCLabelTTF::create("30元", "Helvetica", 18);
    label30->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn30Select = CCControlButton::create(label30,CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn30Select->setBackgroundSpriteForState(CCScale9Sprite::create("bg_seleceted.png"), CCControlStateDisabled);
    m_pBtn30Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn30Select->setTouchPriority(-1000);
    container->addChild(m_pBtn30Select);
    m_pBtn30Select->setPosition(ccp(-104, 136));
    m_pBtn30Select->setTag(30);
    m_pBtn30Select->addTargetWithActionForControlEvents(this,
                                                        cccontrol_selector(QimiPrepaidCardView::selected),
                                                        CCControlEventTouchUpInside);
    
    CCLabelTTF* label50 = CCLabelTTF::create("50元", "Helvetica", 18);
    label50->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn50Select = CCControlButton::create(label50, CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn50Select->setBackgroundSpriteForState(CCScale9Sprite::create("bg_seleceted.png"), CCControlStateDisabled);
    m_pBtn50Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn50Select->setTouchPriority(-1000);
    container->addChild(m_pBtn50Select);
    m_pBtn50Select->setPosition(ccp(107, 136));
    m_pBtn50Select->setTag(50);
    m_pBtn50Select->addTargetWithActionForControlEvents(this,
                                                        cccontrol_selector(QimiPrepaidCardView::selected),
                                                        CCControlEventTouchUpInside);
    
    CCLabelTTF* label100 = CCLabelTTF::create("100元", "Helvetica", 18);
    label100->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn100Select = CCControlButton::create(label100,CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn100Select->setBackgroundSpriteForState(CCScale9Sprite::create("bg_seleceted.png"), CCControlStateDisabled);
    m_pBtn100Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn100Select->setTouchPriority(-1000);
    container->addChild(m_pBtn100Select);
    m_pBtn100Select->setPosition(ccp(-104, 83));
    m_pBtn100Select->setTag(100);
    m_pBtn100Select->addTargetWithActionForControlEvents(this,
                                                         cccontrol_selector(QimiPrepaidCardView::selected),
                                                         CCControlEventTouchUpInside);
    
    CCLabelTTF* label300 = CCLabelTTF::create("300元", "Helvetica", 18);
    label300->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn300Select = CCControlButton::create(label300, CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn300Select->setBackgroundSpriteForState(CCScale9Sprite::create("bg_seleceted.png"), CCControlStateDisabled);
    m_pBtn300Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn300Select->setTouchPriority(-1000);
    container->addChild(m_pBtn300Select);
    m_pBtn300Select->setPosition(ccp(107, 82));
    m_pBtn300Select->setTag(300);
    m_pBtn300Select->addTargetWithActionForControlEvents(this,
                                                         cccontrol_selector(QimiPrepaidCardView::selected),
                                                         CCControlEventTouchUpInside);
    
    CCLabelTTF* label500 = CCLabelTTF::create("500元", "Helvetica", 18);
    label500->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn500Select = CCControlButton::create(label500, CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn500Select->setBackgroundSpriteForState(CCScale9Sprite::create("bg_seleceted.png"), CCControlStateDisabled);
    m_pBtn500Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn500Select->setTouchPriority(-1000);
    container->addChild(m_pBtn500Select);
    m_pBtn500Select->setPosition(ccp(-104, 26));
    m_pBtn500Select->setTag(500);
    m_pBtn500Select->addTargetWithActionForControlEvents(this,
                                                         cccontrol_selector(QimiPrepaidCardView::selected),
                                                         CCControlEventTouchUpInside);
    
    
    cocos2d::extension::CCScale9Sprite* m_pInputTxtBg = CCScale9Sprite::create("loginbg.png");
    CCSize editBoxSize = CCSizeMake(200, 45);
    m_pInputTxtBg->removeFromParentAndCleanup(false);
    m_pEditName = CCEditBox::create(editBoxSize, m_pInputTxtBg);
    m_pEditName->setPosition(ccp(-100, -35));
    m_pEditName->setFontColor(ccc3(255, 0, 0));
    m_pEditName->setMaxLength(20);
    m_pEditName->setReturnType(kKeyboardReturnTypeDone);
    m_pEditName->setTouchPriority(-1000);
    m_pEditName->setText("");
    m_pEditName->setDelegate(this);
    container->addChild(m_pEditName);
    
    
    CCLabelTTF* yuan = CCLabelTTF::create("元", "Helvetica", 20);
    container->addChild(yuan);
    yuan->setColor(ccc3(0, 0, 0));
    yuan->setPosition(ccp(10, -35));
    yuan->setAnchorPoint(ccp(0, 0.5));
    
    CCLabelTTF* label01 = CCLabelTTF::create("您将充值", "Helvetica", 20);
    container->addChild(label01);
    label01->setColor(ccc3(0, 0, 0));
    label01->setPosition(ccp(-199, -83));
    label01->setAnchorPoint(ccp(0, 0.5));
    
    m_pMcashNumTxt = CCLabelTTF::create("1", "Helvetica", 20);
    m_pMcashNumTxt->setColor(ccc3(196, 9, 9));
    m_pMcashNumTxt->setPosition(ccp(-116, -84));
    m_pMcashNumTxt->setAnchorPoint(ccp(0, 0.5));
    container->addChild(m_pMcashNumTxt);
    
    m_pMcashNumLastTxt = CCLabelTTF::create("元宝", "Helvetica", 20);
    container->addChild(m_pMcashNumLastTxt);
    m_pMcashNumLastTxt->setColor(ccc3(0, 0, 0));
    m_pMcashNumLastTxt->setPosition(ccp(-84, -84));
    m_pMcashNumLastTxt->setAnchorPoint(ccp(0, 0.5));
    
    
    m_pButtonList->addObject(m_pBtn10Select);
    m_pButtonList->addObject(m_pBtn20Select);
    m_pButtonList->addObject(m_pBtn30Select);
    m_pButtonList->addObject(m_pBtn50Select);
    m_pButtonList->addObject(m_pBtn100Select);
    m_pButtonList->addObject(m_pBtn300Select);
    m_pButtonList->addObject(m_pBtn500Select);
    
    
    return true;
}

void QimiPrepaidCardView::initData(std::string uId, int sId, std::string key, int money, int kind)
{
    m_uId = uId;
    m_sId = sId;
    m_key = key;
    m_money = money*100;
    upDataView(money);
}


void QimiPrepaidCardView::upDataView(int pay)
{
    m_money = pay*100;
    m_pEditName->setText(CCString::createWithFormat("%d", pay)->getCString());
    m_pMcashNumTxt->setString(CCString::createWithFormat("%d", pay*10)->getCString());
    float posX = m_pMcashNumTxt->getPosition().x + m_pMcashNumTxt->getContentSize().width;
    float posY = m_pMcashNumTxt->getPosition().y;
    
    m_pMcashNumLastTxt->setPosition(ccp(posX, posY));
}

void QimiPrepaidCardView::selected(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    CCControlButton* btn = dynamic_cast<CCControlButton*>(pSender);
    int pay = btn->getTag();
    upDataView(pay);
    upSelectState(btn);
}

void QimiPrepaidCardView::upSelectState(cocos2d::extension::CCControlButton *btn)
{
    for (int i =0; i < m_pButtonList->count(); i++) {
        CCControlButton* b = dynamic_cast<CCControlButton* >(m_pButtonList->objectAtIndex(i));
        if (b == btn)
        {
            b->setEnabled(false);
            b->setTitleColorForState(ccc3(255, 255, 255), CCControlStateDisabled);
        }
        else
        {
            b->setEnabled(true);
        }
    }
}

void QimiPrepaidCardView::nextOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    std::string money =std::string(m_pEditName->getText());
    m_money = atoi(money.c_str())*100;
    //m_money =1;//测试数据
    QimiPrepaidCardNextView* pQimiPrepaidCardNextView = QimiPrepaidCardNextView::create();
    pQimiPrepaidCardNextView->initData(m_uId, m_sId, m_key, m_money, m_kind);
    StageScene::shareStageScene()->m_DialogContainer->addChild(pQimiPrepaidCardNextView);
    this->removeFromParentAndCleanup(true);
}

void QimiPrepaidCardView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}

void QimiPrepaidCardView::qimiHelp(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    QimiPlatform::shareQimiPlatform()->openGameWeb(QIMI_HELP);
}

void QimiPrepaidCardView::editBoxEditingDidBegin(CCEditBox *editBox)
{
    CCLog("editBoxEditingDidBegin");
}
void QimiPrepaidCardView::editBoxEditingDidEnd(CCEditBox *editBox)
{
    CCLog("editBoxEditingDidEnd");
}
void QimiPrepaidCardView::editBoxTextChanged(CCEditBox *editBox,const std::string &text)
{
    CCLog("editBoxTextChanged");
}
void QimiPrepaidCardView::editBoxReturn(CCEditBox *editBox)
{
    CCLog("editBoxReturn");
    changePrie();
}

void QimiPrepaidCardView::changePrie()
{
    std::string p = m_pEditName->getText();
    int price = atoi(p.c_str());
    for (int i =0; i < m_pButtonList->count() ; i++) {
        CCControlButton* b = dynamic_cast<CCControlButton*>(m_pButtonList->objectAtIndex(i));
        b->setEnabled(true);
    }
    CCControlButton* btn = dynamic_cast<CCControlButton*>(this->getChildByTag(100)->getChildByTag(price));
    if (btn!=NULL)
    {
        btn->setEnabled(false);
    }
    upDataView(price);
}









