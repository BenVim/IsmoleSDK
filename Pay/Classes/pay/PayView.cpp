//
//  PayView.cpp
//  Navigations
//
//  Created by Ben on 5/6/13.
//
//

#include "PayView.h"
#include "GameCCBLoader.h"
#include "stdio.h"
#include "ProxyFilterManager.h"
#include "ProxyLoadingFilter.h"
#include "Proxy.h"
#include "StageScene.h"
#include "QimiPlatform.h"
#include <string.h>

PayView::PayView():
m_pBtnZfb(NULL),
m_pBtnSz(NULL),
m_pBtnLt(NULL),
m_pBtnDx(NULL),
m_pPassThroughNumTxt(NULL),
m_pMcashNumTxt(NULL),
m_pProductNameTxt(NULL),
m_pGameNameTxt(NULL),
m_pProductNameLastTxt(NULL),
m_pMcashNumLastTxt(NULL),
m_pBackBtn(NULL)
{
    
}

PayView::~PayView()
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
    CC_SAFE_RELEASE(m_pProductNameLastTxt);
    CC_SAFE_RELEASE(m_pMcashNumLastTxt);
}

cocos2d::SEL_MenuHandler PayView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler PayView::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "backOnClickHandler:", PayView::backOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "ZfbOnClickHandler:", PayView::alipayOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "SzOnClickHandler:", PayView::SzOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "LtOnClickHandler:", PayView::LtOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "DxOnClickHandler:", PayView::DxOnClick);
    return NULL;
}

bool PayView::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "backBtn:", cocos2d::extension::CCControlButton*, m_pBackBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnZfb:", cocos2d::extension::CCControlButton*, m_pBtnZfb);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnSz:", cocos2d::extension::CCControlButton*, m_pBtnSz);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnLt:", cocos2d::extension::CCControlButton*, m_pBtnLt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnDx:", cocos2d::extension::CCControlButton*, m_pBtnDx);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "PassThroughNumTxt:", cocos2d::CCLabelTTF*, m_pPassThroughNumTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "McashNumTxt:", cocos2d::CCLabelTTF*, m_pMcashNumTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ProductNameTxt:", cocos2d::CCLabelTTF*, m_pProductNameTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "GameNameTxt:", cocos2d::CCLabelTTF*, m_pGameNameTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "ProductNameLastTxt:", cocos2d::CCLabelTTF*, m_pProductNameLastTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "McashNumLastTxt:", cocos2d::CCLabelTTF*, m_pMcashNumLastTxt);
    return true;
}

void PayView::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pBackBtn->setDefaultTouchPriority(-130);
    m_pBtnZfb->setDefaultTouchPriority(-130);
    m_pBtnSz->setDefaultTouchPriority(-130);
    m_pBtnLt->setDefaultTouchPriority(-130);
    m_pBtnDx->setDefaultTouchPriority(-130);
}

void PayView::initView(int uId, int sId, std::string key, int money)
{
    m_uId = uId;
    m_sId = sId;
    m_key = key;
    m_money = money;
    onRequestData();
    //先请求接口，得到数据
}

/*
 * 获取用户信息，请求获取用户信息的接口，参数uId,sId,sign,其中sign是uId+sId+key(游戏KEY)的md5值。
 */
void PayView::onRequestData()
{
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://qimi.com/platform/getUser.php");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, callfuncND_selector(PayView::onLoadRequestSucssful));
    
    CCString* postDataStr = CCString::createWithFormat("uId=%d&sId=%d&sign=%s", m_uId, m_sId, m_key.c_str());
    const char* postData = postDataStr->getCString();
    //CCLog("GETUSERINFO【postData=%s】", postData);
    request->setRequestData(postData, strlen(postData));
    request->setTag("POST test1");
    CCHttpClient::getInstance()->send(request);
    request->release();
}

void PayView::onLoadRequestSucssful(cocos2d::CCNode *sender, void *data)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
    if (!response)
    {
        //调用弹窗口。输出用户信息获取失败。请检查网络。
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "输出用户信息获取失败。请检查网络");
        return;
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    std::vector<char> *buffer = response->getResponseData();
    std::string responseData;
    char buff[24];
    printf("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        printf("%c", (*buffer)[i]);
        sprintf(buff, "%c", (*buffer)[i]);
        responseData.append(buff);
    }
    printf("\n");

    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(responseData, root);
    if (!parsingSuccessful)
    {
        return;
    }
    
    if (!root.isNull())
    {
        if (root["mcash"].isInt())
        {
            m_cash = root["mcash"].asInt();
        }
        else
        {
            CCLog("类型不正确");
        }
        m_gameInfo = root["gameInfo"].asString();
    }
    onUpdataView();
}

void PayView::onUpdataView()
{
    m_pPassThroughNumTxt->setString(CCString::createWithFormat("%d", m_uId)->getCString());
    m_pMcashNumTxt->setString(CCString::createWithFormat("%d", m_cash)->getCString());
    m_pProductNameTxt->setString(CCString::createWithFormat("%d", m_money)->getCString());
    m_pGameNameTxt->setString(m_gameInfo.c_str());
    float posX = m_pMcashNumTxt->getPosition().x + m_pMcashNumTxt->getContentSize().width;
    float posY = m_pMcashNumTxt->getPosition().y;
    m_pMcashNumLastTxt->setPosition(ccp(posX, posY));
    posX = m_pProductNameTxt->getPosition().x + m_pProductNameTxt->getContentSize().width;
    posY = m_pProductNameTxt->getPosition().y;
    m_pProductNameLastTxt->setPosition(ccp(posX, posY));
}

void PayView::alipayOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    PayZhifubaoView* pPayZhifubaoView = GameCCBLoader::sharedLoader()->createCCBNode<PayZhifubaoView>("PayZhifubaoView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pPayZhifubaoView);
    pPayZhifubaoView->initData(m_uId, m_sId, m_key, m_money);
    this->removeFromParentAndCleanup(true);
}

void PayView::SzOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    openPrepaidCard(0);
}
void PayView::LtOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    openPrepaidCard(1);
}

void PayView::DxOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    openPrepaidCard(2);
}

void PayView::openPrepaidCard(int kind)
{
    PrepaidCardView* pPrepaidCardView = GameCCBLoader::sharedLoader()->createCCBNode<PrepaidCardView>("PrepaidCardView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pPrepaidCardView);
    pPrepaidCardView->initData(m_uId, m_sId, m_key, m_money, kind);
    this->removeFromParentAndCleanup(true);
}

void PayView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}
