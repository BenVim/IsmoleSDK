//
//  PrepaidCardView.cpp
//  Navigations
//
//  Created by Ben on 5/7/13.
//
//

#include "PrepaidCardView.h"
#include "GameCCBLoader.h"
#include "stdio.h"
#include "GameScrollView.h"
#include "StageScene.h"


PrepaidCardView::PrepaidCardView():
m_pBackBtn(NULL),
m_pBtnCongzhi(NULL),
m_pMcashNumTxt(NULL),
m_pMcashNumBackTxt(NULL),
m_pCCEditBoxCCNode(NULL),
m_pInputTxtBg(NULL),
m_pBtn10Select(NULL),
m_pBtn20Select(NULL),
m_pBtn30Select(NULL),
m_pBtn50Select(NULL),
m_pBtn100Select(NULL),
m_pBtn300Select(NULL),
m_pBtn500Select(NULL)
{
    
}

PrepaidCardView::~PrepaidCardView()
{
    CC_SAFE_RELEASE(m_pBackBtn);
    CC_SAFE_RELEASE(m_pInputTxtBg);
    CC_SAFE_RELEASE(m_pBtnCongzhi);
    CC_SAFE_RELEASE(m_pButtonList);
    CC_SAFE_RELEASE(m_pMcashNumTxt);
    CC_SAFE_RELEASE(m_pBtn10Select);
    CC_SAFE_RELEASE(m_pBtn20Select);
    CC_SAFE_RELEASE(m_pBtn30Select);
    CC_SAFE_RELEASE(m_pBtn50Select);
    CC_SAFE_RELEASE(m_pBtn100Select);
    CC_SAFE_RELEASE(m_pBtn300Select);
    CC_SAFE_RELEASE(m_pBtn500Select);
    CC_SAFE_RELEASE(m_pMcashNumBackTxt);
    CC_SAFE_RELEASE(m_pCCEditBoxCCNode);
    
    
}

cocos2d::SEL_MenuHandler PrepaidCardView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler PrepaidCardView::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "backOnClickHandler:", PrepaidCardView::backOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "10SelectOnClickHandler:", PrepaidCardView::select10OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "20SelectOnClickHandler:", PrepaidCardView::select20OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "30SelectOnClickHandler:", PrepaidCardView::select30OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "50SelectOnClickHandler:", PrepaidCardView::select50OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "100SelectOnClickHandler:", PrepaidCardView::select100OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "300SelectOnClickHandler:", PrepaidCardView::select300OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "500SelectOnClickHandler:", PrepaidCardView::select500OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "rechargeOnClickHandler:", PrepaidCardView::nextOnClick);// next step
    return NULL;
}

bool PrepaidCardView::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BackBtn:", cocos2d::extension::CCControlButton*, m_pBackBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnCongzhi:", cocos2d::extension::CCControlButton*, m_pBtnCongzhi);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "McashNumTxt:", cocos2d::CCLabelTTF*, m_pMcashNumTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "McashNumLastTxt:", cocos2d::CCLabelTTF*, m_pMcashNumBackTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "CCEditBoxCCNode:", cocos2d::CCNode*, m_pCCEditBoxCCNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "InputBgSprte:", cocos2d::extension::CCScale9Sprite*, m_pInputTxtBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn10Select:", CCControlButton*, m_pBtn10Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn20Select:",CCControlButton*, m_pBtn20Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn30Select:",CCControlButton*, m_pBtn30Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn50Select:",CCControlButton*, m_pBtn50Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn100Select:",CCControlButton*, m_pBtn100Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn300Select:",CCControlButton*, m_pBtn300Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "Btn500Select:",CCControlButton*, m_pBtn500Select);
    
    return true;
}

void PrepaidCardView::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pBackBtn->setDefaultTouchPriority(-130);
    m_pBtnCongzhi->setDefaultTouchPriority(-130);
    m_pBtn10Select->setDefaultTouchPriority(-130);
    m_pBtn20Select->setDefaultTouchPriority(-130);
    m_pBtn30Select->setDefaultTouchPriority(-130);
    m_pBtn50Select->setDefaultTouchPriority(-130);
    m_pBtn100Select->setDefaultTouchPriority(-130);
    m_pBtn300Select->setDefaultTouchPriority(-130);
    m_pBtn500Select->setDefaultTouchPriority(-130);
    m_pButtonList = CCArray::create();
    m_pButtonList->retain();
    m_pButtonList->addObject(m_pBtn10Select);
    m_pButtonList->addObject(m_pBtn20Select);
    m_pButtonList->addObject(m_pBtn30Select);
    m_pButtonList->addObject(m_pBtn50Select);
    m_pButtonList->addObject(m_pBtn100Select);
    m_pButtonList->addObject(m_pBtn300Select);
    m_pButtonList->addObject(m_pBtn500Select);
    initView();
}

void PrepaidCardView::initView()
{
    //先请求接口，得到数据
    CCSize editBoxSize = CCSizeMake(200, 45);
    m_pInputTxtBg->removeFromParentAndCleanup(false);
    m_pEditName = CCEditBox::create(editBoxSize, m_pInputTxtBg);
    m_pEditName->setPosition(m_pCCEditBoxCCNode->getPosition());
    m_pEditName->setFontColor(ccc3(255,0,0));
    m_pEditName->setMaxLength(20);
    m_pEditName->setReturnType(kKeyboardReturnTypeDone);
    m_pEditName->setTouchPriority(-130);
    addChild(m_pEditName);
}

void PrepaidCardView::initData(int uId, int sId, std::string key, int money, int kind)
{
    m_uId = uId;
    m_sId = sId;
    m_key = key;
    m_money = money;
    m_kind = kind;
    upDataView(money);
}

void PrepaidCardView::select10OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(10);
    upSelectState(0);
}
void PrepaidCardView::select20OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(20);
    upSelectState(1);
}
void PrepaidCardView::select30OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(30);
    upSelectState(2);
}
void PrepaidCardView::select50OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(50);
    upSelectState(3);
}
void PrepaidCardView::select100OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(100);
    upSelectState(4);
}
void PrepaidCardView::select300OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(300);
    upSelectState(5);
}
void PrepaidCardView::select500OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    upDataView(500);
    upSelectState(6);
}

void PrepaidCardView::nextOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    PrepaidCardNextStepView* pPrepaidCardNextStepView = GameCCBLoader::sharedLoader()->createCCBNode<PrepaidCardNextStepView>("PrepaidCardNextStepView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pPrepaidCardNextStepView);
    pPrepaidCardNextStepView->setPosition(ccp(0, 0));
    pPrepaidCardNextStepView->initData(m_uId, m_sId, m_key, atoi(m_pEditName->getText()), m_kind);
    this->removeFromParentAndCleanup(true);
}

void PrepaidCardView::upDataView(int pay)
{
    m_money = pay;
    m_pEditName->setText(CCString::createWithFormat("%d", pay)->getCString());
    m_pMcashNumTxt->setString(CCString::createWithFormat("%d", pay*10)->getCString());
    float posX = m_pMcashNumTxt->getPosition().x + m_pMcashNumTxt->getContentSize().width;
    float posY = m_pMcashNumTxt->getPosition().y;
    
    m_pMcashNumBackTxt->setPosition(ccp(posX, posY));
}

void PrepaidCardView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    std::string money = m_pEditName->getText();
    m_money = atoi(money.c_str());
    PayView* pPayView = GameCCBLoader::sharedLoader()->createCCBNode<PayView>("PayView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pPayView);
    pPayView->setPosition(ccp(0, 0));
    pPayView->initView(m_uId, m_sId, m_key, m_money);
    this->removeFromParentAndCleanup(true);
}

void PrepaidCardView::upSelectState(int index)
{
    for (int i =0; i < m_pButtonList->count(); i++) {
        CCControlButton* btn = dynamic_cast<CCControlButton* >(m_pButtonList->objectAtIndex(i));
        if (index == i)
        {
             btn->setEnabled(false);
        }
        else
        {
            btn->setEnabled(true);
        }
    }
}





