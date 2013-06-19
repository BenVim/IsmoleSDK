//
//  PrepaidCardNextStepView.cpp
//  PayPro
//
//  Created by Ben on 5/9/13.
//
//

#include "PrepaidCardNextStepView.h"
#include "GameCCBLoader.h"
#include "PrepaidCardOrder.h"

#include "stdio.h"
#include "StageScene.h"

#include "ProxyFilterManager.h"
#include "ProxyLoadingFilter.h"
#include "Proxy.h"
#include "GameUtils.h"
#include "md5.h"

PrepaidCardNextStepView::PrepaidCardNextStepView():
m_pBtnCongzhi(NULL),
m_pMcashNumTxt(NULL),
m_pMcashNumBackTxt(NULL),
m_pBtnCard10Select(NULL),
m_pBtnCard20Select(NULL),
m_pBtnCard30Select(NULL),
m_pBtnCard50Select(NULL),
m_pBtnCard100Select(NULL),
m_pBtnCard300Select(NULL),
m_pBtnCard500Select(NULL),
m_pCCEditBoxCardNumCCNode(NULL),
m_pCCEditBoxCardPassworldCCNode(NULL),
m_pInputCarNumTxtBg(NULL),
m_pInputCarPassTxtBg(NULL),
m_pBackBtn(NULL)
{
    
}

PrepaidCardNextStepView::~PrepaidCardNextStepView()
{
    CC_SAFE_RELEASE(m_pBtnCongzhi);
    CC_SAFE_RELEASE(m_pMcashNumTxt);
    CC_SAFE_RELEASE(m_pMcashNumBackTxt);
    
    CC_SAFE_RELEASE(m_pBtnCard10Select);
    CC_SAFE_RELEASE(m_pBtnCard20Select);
    CC_SAFE_RELEASE(m_pBtnCard30Select);
    CC_SAFE_RELEASE(m_pBtnCard50Select);
    CC_SAFE_RELEASE(m_pBtnCard100Select);
    CC_SAFE_RELEASE(m_pBtnCard300Select);
    CC_SAFE_RELEASE(m_pBtnCard500Select);
    
    CC_SAFE_RELEASE(m_pCCEditBoxCardNumCCNode);
    CC_SAFE_RELEASE(m_pCCEditBoxCardPassworldCCNode);
    
    CC_SAFE_RELEASE(m_pInputCarNumTxtBg);
    CC_SAFE_RELEASE(m_pInputCarPassTxtBg);
    CC_SAFE_RELEASE(m_pBackBtn);
    CC_SAFE_RELEASE(m_pButtonList);
}

cocos2d::SEL_MenuHandler PrepaidCardNextStepView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler PrepaidCardNextStepView::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "Card10SelectOnClickHandler:", PrepaidCardNextStepView::selectCard10OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "Card20SelectOnClickHandler:", PrepaidCardNextStepView::selectCard20OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "Card30SelectOnClickHandler:", PrepaidCardNextStepView::selectCard30OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "Card50SelectOnClickHandler:", PrepaidCardNextStepView::selectCard50OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "Card100SelectOnClickHandler:", PrepaidCardNextStepView::selectCard100OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "Card300SelectOnClickHandler:", PrepaidCardNextStepView::selectCard300OnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "Card500SelectOnClickHandler:", PrepaidCardNextStepView::selectCard500OnClick);
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "rechargeOnClickHandler:", PrepaidCardNextStepView::rechargeOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "backOnClickHandler:", PrepaidCardNextStepView::backOnClick);
    return NULL;
}


bool PrepaidCardNextStepView::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BackBtn:", cocos2d::extension::CCControlButton*, m_pBackBtn);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnCongzhi:", cocos2d::extension::CCControlButton*, m_pBtnCongzhi);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "McashNumTxt:", cocos2d::CCLabelTTF*, m_pMcashNumTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "McashNumLastTxt:", cocos2d::CCLabelTTF*, m_pMcashNumBackTxt);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "CCEditBoxCardNumCCNode:", cocos2d::CCNode*, m_pCCEditBoxCardNumCCNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "CCEditBoxCardPassworldCCNode:", cocos2d::CCNode*, m_pCCEditBoxCardPassworldCCNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "InputCarNumBgSprte:", cocos2d::extension::CCScale9Sprite*, m_pInputCarNumTxtBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "InputCarPassBgSprte:", cocos2d::extension::CCScale9Sprite*, m_pInputCarPassTxtBg);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnCard10Select:", CCControlButton*, m_pBtnCard10Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnCard20Select:",CCControlButton*, m_pBtnCard20Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnCard30Select:",CCControlButton*, m_pBtnCard30Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnCard50Select:",CCControlButton*, m_pBtnCard50Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnCard100Select:",CCControlButton*, m_pBtnCard100Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnCard300Select:",CCControlButton*, m_pBtnCard300Select);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "BtnCard500Select:",CCControlButton*, m_pBtnCard500Select);
    
    return true;
}

void PrepaidCardNextStepView::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pBtnCongzhi->setDefaultTouchPriority(-130);
    m_pBackBtn->setDefaultTouchPriority(-130);
    m_pBtnCard10Select->setDefaultTouchPriority(-130);
    m_pBtnCard20Select->setDefaultTouchPriority(-130);
    m_pBtnCard30Select->setDefaultTouchPriority(-130);
    m_pBtnCard50Select->setDefaultTouchPriority(-130);
    m_pBtnCard100Select->setDefaultTouchPriority(-130);
    m_pBtnCard300Select->setDefaultTouchPriority(-130);
    m_pBtnCard500Select->setDefaultTouchPriority(-130);
    
    m_pButtonList = CCArray::create();
    m_pButtonList->retain();
    
    m_pButtonList->addObject(m_pBtnCard10Select);
    m_pButtonList->addObject(m_pBtnCard20Select);
    m_pButtonList->addObject(m_pBtnCard30Select);
    m_pButtonList->addObject(m_pBtnCard50Select);
    m_pButtonList->addObject(m_pBtnCard100Select);
    m_pButtonList->addObject(m_pBtnCard300Select);
    m_pButtonList->addObject(m_pBtnCard500Select);
    
    
    initView();
}

void PrepaidCardNextStepView::initView()
{
    m_denomination =0;
    CCSize editBoxSize = CCSizeMake(350, 45);
    
    m_pInputCarNumTxtBg->removeFromParentAndCleanup(false);
    m_pCardNum = CCEditBox::create(editBoxSize, m_pInputCarNumTxtBg);
    m_pCardNum->setPosition(m_pCCEditBoxCardNumCCNode->getPosition());
    m_pCardNum->setFontColor(ccc3(255,0,0));
    m_pCardNum->setMaxLength(20);
    m_pCardNum->setReturnType(kKeyboardReturnTypeDone);
    m_pCardNum->setTouchPriority(-130);
    m_pCardNum->setText("");
    addChild(m_pCardNum);
    
    m_pInputCarPassTxtBg->removeFromParentAndCleanup(false);
    m_pCardPassword = CCEditBox::create(editBoxSize, m_pInputCarPassTxtBg);
    m_pCardPassword->setPosition(m_pCCEditBoxCardPassworldCCNode->getPosition());
    m_pCardPassword->setFontColor(ccc3(255,0,0));
    m_pCardPassword->setMaxLength(20);
    m_pCardPassword->setReturnType(kKeyboardReturnTypeDone);
    m_pCardPassword->setTouchPriority(-130);
    m_pCardPassword->setText("");
    addChild(m_pCardPassword);
    
}

void PrepaidCardNextStepView::initData(int uId, int sId, std::string key, int money, int kind)
{
    m_kind = kind;//充值卡种类
    m_uId = uId;
    m_sId = sId;
    m_key = key;
    m_money = money;
    
    //0:移动;1:联通;2:电信
    if (m_kind == 0)
    {
        //m_pCardNum->setText("12305150275877926");
        //m_pCardPassword->setText("151219200875874025");
    }
    else if (m_kind == 1)
    {
        //m_pCardNum->setText("1107211916734934176");
        //m_pCardPassword->setText("111201316848305");
    }
    else
    {
        //m_pCardNum->setText("");
        //m_pCardPassword->setText("");
    }
}


void PrepaidCardNextStepView::rechargeOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    //充值。。。 调用接口
    //m_money 最终需要充值的数量
    
    
    std::string str = std::string(m_pCardNum->getText());
    if (str.empty())
    {
        CCLog("card number is NULL");
        return;
    }
    
    std::string strPass = std::string(m_pCardPassword->getText());
    if (strPass.empty())
    {
        CCLog("strPass number is NULL");
        return;
    }
    
    if (m_denomination == 0)
    {
        CCLog("m_denomination number is 0");
        return;
    }

    requestOrder();
    CCLog("充值卡 money %d 种类 %d, 面额：%d", m_money , m_kind, m_denomination);
}

void PrepaidCardNextStepView::selectCard10OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    m_denomination = 10;
    upSelectState(0);
}
void PrepaidCardNextStepView::selectCard20OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    m_denomination = 20;
    upSelectState(1);
}
void PrepaidCardNextStepView::selectCard30OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    m_denomination = 30;
    upSelectState(2);
}
void PrepaidCardNextStepView::selectCard50OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    m_denomination = 50;
    upSelectState(3);
}
void PrepaidCardNextStepView::selectCard100OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    m_denomination = 100;
    upSelectState(4);
}
void PrepaidCardNextStepView::selectCard300OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    m_denomination = 300;
    upSelectState(5);
}
void PrepaidCardNextStepView::selectCard500OnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    m_denomination = 500;
    upSelectState(6);
}

void PrepaidCardNextStepView::upSelectState(int index)
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



void PrepaidCardNextStepView::upDataView(int pay)
{
    
}

void PrepaidCardNextStepView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    PrepaidCardView* pPrepaidCardView = GameCCBLoader::sharedLoader()->createCCBNode<PrepaidCardView>("PrepaidCardView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pPrepaidCardView);
    pPrepaidCardView->setPosition(ccp(0, 0));
    pPrepaidCardView->initData(m_uId, m_sId, m_key, m_money, m_kind);
    this->removeFromParentAndCleanup(true);
}

void PrepaidCardNextStepView::requestOrder()
{
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://www.qimi.com/platform/addOrder.php");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, callfuncND_selector(PrepaidCardNextStepView::requestSucssful));

    std::string sign = "e7d4b2571e2d1fd80c19a048b18a529e";//游戏参数传入的
    std::string msign = GameUtils::getStringWithMd5(CCString::createWithFormat("%d%d%s",m_uId, m_sId, sign.c_str())->getCString());
    
    std::transform(msign.begin(), msign.end(), msign.begin(), ::tolower);
    std::string cardNum = m_pCardNum->getText();
    std::string cardPass = m_pCardPassword->getText();
    int denomination =  m_denomination;
    
    CCString* postDataStr = CCString::createWithFormat("uId=%d&sId=%d&sign=%s&carNum=%s&carPass=%s&denomination=%d&orderType=shenzhoufupay&type=%d&money=%d", m_uId, m_sId, msign.c_str(), cardNum.c_str(), cardPass.c_str(), denomination, m_kind, m_money);
    
    const char* postData = postDataStr->getCString();
    CCLog("postData=%s", postData);
    request->setRequestData(postData, strlen(postData));
    
    request->setTag("POST test1");
    CCHttpClient::getInstance()->send(request);
    request->release();

    
}


void PrepaidCardNextStepView::requestSucssful(cocos2d::CCNode *sender, void *data)
{
    
    std::string oderId = "";
    std::string cardInfo = "";
    
    
    CCHttpResponse *response = (CCHttpResponse*)data;
    
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
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
        if (!root["data"].isNull() && root["data"].isString())
        {
            oderId = root["data"].asString();
            CCLog("订单号：%s", oderId.c_str());
        }
        
        
        if (!root["cardInfo"].isNull() && root["cardInfo"].isString())
        {
            cardInfo = root["cardInfo"].asString();
            CCLog("cardInfo = %s",cardInfo.c_str());
        }
    }
    
    PrepaidCardOrder * pOder = PrepaidCardOrder::create();
    pOder->retain();
    
    pOder->setVersion(3);
    pOder->setMerId("183278");
    pOder->setPayMoney(m_money);
    pOder->setOrderId(oderId);
    pOder->setReturnUrl("http://www.qimi.com/platform/shenzhoufupay/notify_url.php");
    pOder->setCardInfo(cardInfo);
    pOder->setMerUserName("");
    pOder->setMerUserMail("");
    pOder->setPrivateField("");
    pOder->setVerifyType(1);
    pOder->setCardTypeCombine(m_kind);//充值卡类型；
    
    std::string privateKey ="wv4GscMNAIzXJ2nWWCXz";//wv4GscMNAIzXJ2nWWCXz
    
    std::string md5str;
    char p[32];
    sprintf(p,"%d",pOder->getVersion());
    md5str+=p;
    md5str+=pOder->getMerId();

    char moneyChar[32];
    sprintf(moneyChar, "%d", pOder->getPayMoney());
    md5str+=moneyChar;
    md5str+=pOder->getOrderId();
    md5str+=pOder->getReturnUrl();
    md5str+=pOder->getCardInfo();
    md5str+=pOder->getPrivateField();
    char pt[32];
    sprintf(pt, "%d", pOder->getVerifyType());
    md5str+=pt;
    md5str+=privateKey;
    
    MD5 md5;
    md5.update(md5str);
    
    CCLog("md5str==%s",md5str.c_str());
    
    std::string md5tolower = md5.toString();
    //GameUtils::getStringWithMd5(md5str);
    //std::transform(md5tolower.begin(), md5tolower.end(), md5tolower.begin(), ::tolower);
    pOder->setMd5String(md5tolower);
    reqeuestPay(pOder);
}

void PrepaidCardNextStepView::requestFaild(Proxy *pro, ProxyEvent proxyEvent)
{
    
}

void PrepaidCardNextStepView::reqeuestPay(PrepaidCardOrder *pOrder)
{
    
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://pay3.shenzhoufu.com/interface/version3/serverconnszx/entry-noxml.aspx");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, callfuncND_selector(PrepaidCardNextStepView::requestPaySucssful));
    CCString* postDataStr = CCString::createWithFormat("version=%d&merId=%s&payMoney=%d&orderId=%s&returnUrl=%s&cardInfo=%s&merUserName=%s&merUserMail=%s&privateField=%s&verifyType=%d&cardTypeCombine=%d&md5String=%s",
                                                       pOrder->getVersion(),
                                                       pOrder->getMerId().c_str(),
                                                       pOrder->getPayMoney(),
                                                       pOrder->getOrderId().c_str(),
                                                       pOrder->getReturnUrl().c_str(),
                                                       pOrder->getCardInfo().c_str(),
                                                       pOrder->getMerUserName().c_str(),
                                                       pOrder->getMerUserMail().c_str(),
                                                       pOrder->getPrivateField().c_str(),
                                                       pOrder->getVerifyType(),
                                                       pOrder->getCardTypeCombine(),
                                                       pOrder->getMd5String().c_str());
    
    
    const char* postData = postDataStr->getCString();
    CCLog("postData=%s", postData);
    request->setRequestData(postData, strlen(postData));
    
    request->setTag("POST test1");
    CCHttpClient::getInstance()->send(request);
    request->release();
}

void PrepaidCardNextStepView::requestPaySucssful(cocos2d::CCNode *sender, void *data)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
    
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
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
    
    switch (statusCode) {
        case 200:
            CCLog("充值已成功！");
            break;
            case 101:
            CCLog("异常错误");
            
        default:
            break;
    }
    
}



void PrepaidCardNextStepView::requestPayFaild(Proxy *pro, ProxyEvent proxyEvent)
{
    CCLog("requestPayFaild");
}



