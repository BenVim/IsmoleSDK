//
//  PayHelpView.cpp
//  Navigations
//
//  Created by Ben on 5/7/13.
//
//

#include "PayHelpView.h"
#include "GameCCBLoader.h"

#include "stdio.h"



PayHelpView::PayHelpView():
m_pBtnZfb(NULL),
m_pBtnSz(NULL),
m_pBtnLt(NULL),
m_pBtnDx(NULL),
m_pPassThroughNumTxt(NULL),
m_pMcashNumTxt(NULL),
m_pProductNameTxt(NULL),
m_pGameNameTxt(NULL)
{
    
}

PayHelpView::~PayHelpView()
{
    CC_SAFE_RELEASE(m_pBackBtn);
    CC_SAFE_RELEASE(m_pBtnZfb);
    CC_SAFE_RELEASE(m_pBtnSz);
    CC_SAFE_RELEASE(m_pBtnLt);
    CC_SAFE_RELEASE(m_pBtnDx);
    
    CC_SAFE_RELEASE(m_pPassThroughNumTxt);
    CC_SAFE_RELEASE(m_pMcashNumTxt);
    CC_SAFE_RELEASE(m_pProductNameTxt);
    CC_SAFE_RELEASE(m_pGameNameTxt);
    
}

cocos2d::SEL_MenuHandler PayHelpView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler PayHelpView::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "backOnClickHandler:", PayView::backOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "ZfbOnClickHandler:", PayView::backOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "SzOnClickHandler:", PayView::backOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "LtOnClickHandler:", PayView::backOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "DxOnClickHandler:", PayView::backOnClick);
    return NULL;
}

bool PayHelpView::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "backBtn:", cocos2d::extension::CCControlButton*, m_pBackBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnZfb:", cocos2d::extension::CCControlButton*, m_pBtnZfb);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnSz:", cocos2d::extension::CCControlButton*, m_pBtnSz);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnLt:", cocos2d::extension::CCControlButton*, m_pBtnLt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnDx:", cocos2d::extension::CCControlButton*, m_pBtnDx);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "PassThroughNumTxt", cocos2d::CCLabelTTF*, m_pPassThroughNumTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "McashNumTxt", cocos2d::CCLabelTTF*, m_pMcashNumTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ProductNameTxt", cocos2d::CCLabelTTF*, m_pProductNameTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "GameNameTxt", cocos2d::CCLabelTTF*, m_pGameNameTxt);
    
    //PassThroughNumTxt:
    //McashNumTxt:
    //ProductNameTxt:
    //GameNameTxt:
    return true;
}

void PayHelpView::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pBackBtn->setTouchPriority(-130);
    m_pBtnZfb->setTouchPriority(-130);
    m_pBtnSz->setTouchPriority(-130);
    m_pBtnLt->setTouchPriority(-130);
    m_pBtnDx->setTouchPriority(-130);
}

void PayHelpView::initView()
{
    //先请求接口，得到数据
}

void PayHelpView::onRequestData()
{
    //数据请求成功的处理
    m_pPassThroughNumTxt;
    m_pMcashNumTxt;
    m_pProductNameTxt;
    m_pGameNameTxt;
    
}

void PayHelpView::onRequestFaild()
{
    //数据请求失败的处理。
}





void PayHelpView::ZfbOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    CCLog("ZfbOnClick");
}
void PayHelpView::SzOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    CCLog("SzOnClick");
}
void PayHelpView::LtOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    CCLog("LtOnClick");
}
void PayHelpView::DxOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    CCLog("DxOnClick");
}


void PayHelpView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    //this->unscheduleUpdate();
    this->removeFromParentAndCleanup(true);
}