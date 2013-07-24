//
//  QimiMainView.cpp
//  Pay
//
//  Created by Ben on 6/24/13.
//
//

#include "QimiMainView.h"
#include "GameUtils.h"
#include "QimiAlipayView.h"
#include "StageScene.h"
#include "Qimi.h"
#include "QimiPrepaidCardView.h"
#include "QimiMD5.h"
#include "RequestLoadingView.h"
#include "UIMaskLayerView.h"
#include "QimiPlatform.h"
#include "QimiUserModel.h"
#include "QimiUserModel.h"
#include "QimiPlatformIOS.h"
#include "QimiPlatformAndroid.h"
#include "QimiAlipayDailog.h"
#include "QimiPrepaidCardNextView.h"
#include "PlatformUtilityHelper.h"

QimiMainView::QimiMainView()
{
    
}

QimiMainView::~QimiMainView()
{
    
}

bool QimiMainView::init()
{
    m_cash = 0;
    UIMaskLayerView* mask = UIMaskLayerView::create();
    this->addChild(mask);
    CCSize m_size = CCDirector::sharedDirector()->getWinSize();
    
        
    
    CCNode* container = CCNode::create();
    this->addChild(container);
    container->setPosition(ccp(m_size.width/2, m_size.height/2-20));
    
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
                                                cccontrol_selector(QimiMainView::backOnClick),
                                                CCControlEventTouchUpInside);

    
    CCControlButton* helpBtn = CCControlButton::create(CCScale9Sprite::create("btn_bangzhu.png"));
    helpBtn->setPreferredSize(CCSizeMake(93, 51));
    helpBtn->setTouchPriority(-1000);
    topCCNode->addChild(helpBtn);
    helpBtn->setPosition(ccp(163, 0));
    helpBtn->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiMainView::qimiHelp),
                                                    CCControlEventTouchUpInside);
    
    CCLabelTTF* topText = CCLabelTTF::create("奇米支付中心", "Helvetica", 28);
    topText->setColor(ccc3(104, 67, 2));
    topCCNode->addChild(topText);
    topText->setPosition(ccp(0, 0));
    
    /**TOP END**/
    
    
    
    CCLabelTTF* qimiCopy = CCLabelTTF::create("@2013 奇米网", "Helvetica", 20);
    this->addChild(qimiCopy);
    qimiCopy->setColor(ccc3(94, 94, 94));
    qimiCopy->setPosition(ccp(240, 50));
    
    CCLabelTTF* qimiUrl = CCLabelTTF::create("www.qimi.com", "Helvetica", 20);
    this->addChild(qimiUrl);
    qimiUrl->setColor(ccc3(94, 94, 94));
    qimiUrl->setPosition(ccp(240, 26));
    
    ////////////公共部分结束
    
    
    CCRect form = CCRectMake(0, 0, 40, 40);
    CCRect capInset = CCRectMake(10, 10, 10, 10);
    CCScale9Sprite* scale9Sprite = CCScale9Sprite::create("bg_40x40.png", form, capInset);
    scale9Sprite->setContentSize(CCSizeMake(445, 140));
    scale9Sprite->setPosition(ccp(0, 210));
    container->addChild(scale9Sprite);
    
    
    CCScale9Sprite* scale9Sprite1 = CCScale9Sprite::create("bg_40x40.png", form, capInset);
    scale9Sprite1->setContentSize(CCSizeMake(445, 380));
    scale9Sprite1->setPosition(ccp(0 , -70));
    container->addChild(scale9Sprite1);
    
    
//    CCLabelTTF* userInfoTitle = CCLabelTTF::create("个人帐户信息", "Helvetica", 26);
//    this->addChild(userInfoTitle);
//    userInfoTitle->setColor(ccc3(0, 0, 0));
//    userInfoTitle->setPosition(ccp(33, 646));
//    userInfoTitle->setAnchorPoint(ccp(0, 0.5));
    
    
    CCLabelTTF* txt_tongxinzheng = CCLabelTTF::create("当前帐户：", "Helvetica", 20);
    container->addChild(txt_tongxinzheng);
    txt_tongxinzheng->setColor(ccc3(0, 0, 0));
    txt_tongxinzheng->setPosition(ccp(-82, 250));
    txt_tongxinzheng->setAnchorPoint(ccp(1, 0.5));
    
    CCLabelTTF* txt_zhanghuyuer = CCLabelTTF::create("充值金额：", "Helvetica", 20);
    container->addChild(txt_zhanghuyuer);
    txt_zhanghuyuer->setColor(ccc3(0, 0, 0));
    txt_zhanghuyuer->setPosition(ccp(-82, 215));
    txt_zhanghuyuer->setAnchorPoint(ccp(1, 0.5));
    
    
    CCLabelTTF* txt_productName = CCLabelTTF::create("兑换说明：", "Helvetica", 20);
    container->addChild(txt_productName);
    txt_productName->setColor(ccc3(0, 0, 0));
    txt_productName->setPosition(ccp(-82, 180));
    txt_productName->setAnchorPoint(ccp(1, 0.5));
    
    
    /***top 2 end **/
    
    CCLabelTTF* txt_select = CCLabelTTF::create("请选择充值方式：", "Helvetica", 22);
    container->addChild(txt_select);
    txt_select->setColor(ccc3(0, 0, 0));
    txt_select->setPosition(ccp(-25, 83));
    txt_select->setAnchorPoint(ccp(1, 0.5));
    
    /////帐户
    m_pPassThroughNumTxt = CCLabelTTF::create("0", "Helvetica",  20);
    container->addChild(m_pPassThroughNumTxt);
    m_pPassThroughNumTxt->setColor(ccc3(214, 84, 84));
    m_pPassThroughNumTxt->setPosition(ccp(-75, 250));
    m_pPassThroughNumTxt->setAnchorPoint(ccp(0, 0.5));
    
    //充值金额
    m_pProductNameTxt = CCLabelTTF::create("0","Helvetica", 20);
    container->addChild(m_pProductNameTxt);
    m_pProductNameTxt->setColor(ccc3(214, 84, 84));
    m_pProductNameTxt->setPosition(ccp(-75, 215));
    m_pProductNameTxt->setAnchorPoint(ccp(0, 0.5));
    
    
    m_pProductNameLastTxt = CCLabelTTF::create("元", "Helvetica", 20);
    container->addChild(m_pProductNameLastTxt);
    m_pProductNameLastTxt->setColor(ccc3(0, 0, 0));
    m_pProductNameLastTxt->setPosition(ccp(-50, 185));
    m_pProductNameLastTxt->setAnchorPoint(ccp(0, 0.5));
    
    //奇米币数量
    m_pMcashNumTxt = CCLabelTTF::create("0", "Helvetica", 20);
    container->addChild(m_pMcashNumTxt);
    m_pMcashNumTxt->setColor(ccc3(214, 84, 84));
    m_pMcashNumTxt->setPosition(ccp(-75, 180));
    m_pMcashNumTxt->setAnchorPoint(ccp(0, 0.5));
    
    m_pMcashNumLastTxt = CCLabelTTF::create("", "Helvetica", 20);
    container->addChild(m_pMcashNumLastTxt);
    m_pMcashNumLastTxt->setColor(ccc3(0, 0, 0));
    m_pMcashNumLastTxt->setPosition(ccp(-50, 185));
    m_pMcashNumLastTxt->setAnchorPoint(ccp(0, 0.5));
    
    /////////////////
    
    CCControlButton* alixPayBtn = CCControlButton::create(CCScale9Sprite::create("img_zhifubao.png"));
    alixPayBtn->setPreferredSize(CCSizeMake(114, 114));
    alixPayBtn->setTouchPriority(-1000);
    container->addChild(alixPayBtn);
    alixPayBtn->setPosition(ccp(-147, 0));
    alixPayBtn->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiMainView::alipayOnClick),
                                                    CCControlEventTouchUpInside);
    
    CCLabelTTF* m_pzfbTxt = CCLabelTTF::create("支付宝", "Helvetica", 20);
    container->addChild(m_pzfbTxt);
    m_pzfbTxt->setColor(ccc3(0, 0, 0));
    m_pzfbTxt->setPosition(ccp(-147, -75));
    m_pzfbTxt->setAnchorPoint(ccp(0.5, 0.5));
    
    
    
    CCControlButton* sZXBtn = CCControlButton::create(CCScale9Sprite::create("img_shenzhouxing.png"));
    sZXBtn->setPreferredSize(CCSizeMake(114, 114));
    sZXBtn->setTouchPriority(-1000);
    container->addChild(sZXBtn);
    sZXBtn->setPosition(ccp(0, 0));
    sZXBtn->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiMainView::SzOnClick),
                                                    CCControlEventTouchUpInside);
    CCLabelTTF* m_szxTxt = CCLabelTTF::create("神州行", "Helvetica", 20);
    container->addChild(m_szxTxt);
    m_szxTxt->setColor(ccc3(0, 0, 0));
    m_szxTxt->setPosition(ccp(0, -75));
    m_szxTxt->setAnchorPoint(ccp(0.5, 0.5));
    
    
    CCControlButton* lTBtn = CCControlButton::create(CCScale9Sprite::create("img_liantong.png"));
    lTBtn->setPreferredSize(CCSizeMake(114, 114));
    lTBtn->setTouchPriority(-1000);
    container->addChild(lTBtn);
    lTBtn->setPosition(ccp(145, 0));
    lTBtn->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiMainView::LtOnClick),
                                                    CCControlEventTouchUpInside);
    CCLabelTTF* m_ltTxt = CCLabelTTF::create("联通", "Helvetica", 20);
    container->addChild(m_ltTxt);
    m_ltTxt->setColor(ccc3(0, 0, 0));
    m_ltTxt->setPosition(ccp(145, -75));
    m_ltTxt->setAnchorPoint(ccp(0.5, 0.5));
    
    
    CCControlButton* dXBtn = CCControlButton::create(CCScale9Sprite::create("img_dianxin.png"));
    dXBtn->setPreferredSize(CCSizeMake(114, 114));
    dXBtn->setTouchPriority(-1000);
    container->addChild(dXBtn);
    dXBtn->setPosition(ccp(-147, -154));
    dXBtn->addTargetWithActionForControlEvents(this,
                                               cccontrol_selector(QimiMainView::DxOnClick),
                                                    CCControlEventTouchUpInside);
    CCLabelTTF* m_dxTxt = CCLabelTTF::create("电信", "Helvetica", 20);
    container->addChild(m_dxTxt);
    m_dxTxt->setColor(ccc3(0, 0, 0));
    m_dxTxt->setPosition(ccp(-147, -229));
    m_dxTxt->setAnchorPoint(ccp(0.5, 0.5));
    
    
    CCControlButton* qimiBtn = CCControlButton::create(CCScale9Sprite::create("img_qimi.png"));
    qimiBtn->setPreferredSize(CCSizeMake(114, 114));
    qimiBtn->setTouchPriority(-1000);
    container->addChild(qimiBtn);
    qimiBtn->setPosition(ccp(0, -154));
    qimiBtn->addTargetWithActionForControlEvents(this,
                                               cccontrol_selector(QimiMainView::qimiCz),
                                               CCControlEventTouchUpInside);
    CCLabelTTF* m_qimiTxt = CCLabelTTF::create("奇米", "Helvetica", 20);
    container->addChild(m_qimiTxt);
    m_qimiTxt->setColor(ccc3(0, 0, 0));
    m_qimiTxt->setPosition(ccp(0, -229));
    m_qimiTxt->setAnchorPoint(ccp(0.5, 0.5));
    
    return true;
}

void QimiMainView::initView(std::string uId, int sId, std::string key, int money)
{
    
    setTouchPriority(-1000);
    m_uId = uId;
    m_sId = sId;
    m_key = key;
    m_money = money; 
    onRequestData();
    
    ////////////////
}

void QimiMainView::onRequestData()
{
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://qimi.com/platform/getUser.php");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, httpresponse_selector(QimiMainView::onLoadRequestSucssful));
    
    
    char sign[255];
    sprintf(sign, "%s%d%s",
            m_uId.c_str(),
            m_sId,
            m_key.c_str());
    QimiMD5 md5;
    md5.update(sign);
    
    CCLog("md5str==%s",sign);
    std::string md5tolower = md5.toString();
    
    CCString* postDataStr = CCString::createWithFormat("uId=%s&sId=%d&sign=%s", m_uId.c_str(), m_sId, md5tolower.c_str());
    const char* postData = postDataStr->getCString();
    CCLog("GETUSERINFO【postData=%s】", postData);
    request->setRequestData(postData, strlen(postData));
    request->setTag("POST test1");
    CCHttpClient::getInstance()->send(request);
    request->release();
    RequestLoadingView* mask = RequestLoadingView::create();
    mask->setTag(100000);
    this->addChild(mask);
}

void QimiMainView::onLoadRequestSucssful(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response)
{
    CCNode* node = this->getChildByTag(100000);
    if (node!=NULL)
    {
        node->removeFromParentAndCleanup(true);
    }
    Json::Value root = GameUtils::getResponseData(response);
    if (root !=NULL && !root.isNull())
    {
        
        if (root["s"].isInt() == 1)
        {
            CCLog("%s", root["msg"].asString().c_str());
        }
        
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
    else
    {
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "服务器异常，请稍后再试");
    }
    onUpdataView();
    
}
void QimiMainView::onUpdataView()
{
    m_pPassThroughNumTxt->setString(QimiPlatform::shareQimiPlatform()->getQimiUserModel()->getEmail().c_str());
    
    m_pMcashNumTxt->setString("1元=10元宝");
    m_pProductNameTxt->setString(CCString::createWithFormat("%d", m_money)->getCString());
    float posXxx = m_pMcashNumTxt->getPosition().x + m_pMcashNumTxt->getContentSize().width+10;
    float posYyy = m_pMcashNumTxt->getPosition().y;
    m_pMcashNumLastTxt->setPosition(ccp(posXxx, posYyy));
    
    float posX = m_pProductNameTxt->getPosition().x + m_pProductNameTxt->getContentSize().width+10;
    float posY = m_pProductNameTxt->getPosition().y;
    m_pProductNameLastTxt->setPosition(ccp(posX, posY));
    
}

void QimiMainView::alipayOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    rechargeOnClick();
//    std::string appScheme = QimiPlatform::shareQimiPlatform()->getAppScheme();
//    
//    QimiAlipayView* pQimiAlipayView = QimiAlipayView::create();
//    pQimiAlipayView->initData(m_uId, m_sId, m_key, m_money, appScheme, m_gameInfo); //std::string appScheme, std::string productName);
//    StageScene::shareStageScene()->m_DialogContainer->addChild(pQimiAlipayView);
}

void QimiMainView::qimiPay(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    if (m_cash <= 0)
    {
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "您的帐户奇米币余额不足，请充值！");
    }
    else if (m_cash < m_money)
    {
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "您的帐户奇米币余额不足，请充值！");
    }
    else
    {
        //使用奇米币支付
        char sign[255];
        sprintf(sign, "amt=%dappid=%ddes=%sdo=consumeMcashmod=Paysession_key=%s%s",
                m_money,
                QimiPlatform::shareQimiPlatform()->getQimiGameAppId(),
                "game_pay",
                QimiPlatform::shareQimiPlatform()->getQimiUserModel()->getSessionKey().c_str(),
                QimiPlatform::shareQimiPlatform()->getQimiGameKey().c_str()
                );
        QimiMD5 md5;
        md5.update(sign);
        CCLog("md5str==%s",sign);
        std::string md5tolower = md5.toString();
        std::string url = std::string(QIMI_API);
        
        CCHttpRequest* request = new CCHttpRequest();
        request->setUrl(url.c_str());
        request->setRequestType(CCHttpRequest::kHttpPost);
        request->setResponseCallback(this, httpresponse_selector(QimiMainView::qimiConsumeMcashRequestSucssful));
        
        CCString* postDataStr = CCString::createWithFormat("sign=%s&amt=%d&appid=%d&mod=Pay&do=consumeMcash&des=%s&session_key=%s",
                                                           md5tolower.c_str(),
                                                           m_money,
                                                           QimiPlatform::shareQimiPlatform()->getQimiGameAppId(),
                                                           "game_pay",
                                                           QimiPlatform::shareQimiPlatform()->getQimiUserModel()->getSessionKey().c_str());
        const char* postData = postDataStr->getCString();
        CCLog("postData=%s", postData);
        request->setRequestData(postData, strlen(postData));
        request->setTag("POST test1");
        CCHttpClient::getInstance()->send(request);
        request->release();

        RequestLoadingView* mask = RequestLoadingView::create();
        mask->setTag(100000);
        this->addChild(mask);
        /*
         sign	true	string	签名，由当前所有参数计算得出

         amt	true	int	消费奇米币数量
         appid	true	int	应用id，申请应用时分配的应用唯一标识
         des	true	string	描述消费奇米币做了什
         do	true	string	请求方法：consumeMcash
         mod	true	string	请求对象：Pay
         session_key	true	string	用户登录后获取的认证密钥，session_key内包括了用户信息
         */
    }
}

void QimiMainView::qimiConsumeMcashRequestSucssful(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response)
{
    CCNode* node = this->getChildByTag(100000);
    if (node!=NULL)
    {
        node->removeFromParentAndCleanup(true);
    }
    
    Json::Value root = GameUtils::getResponseData(response);
    if (root !=NULL && !root.isNull())
    {
        int status;
        CC_GAME_JSON_ADD(root, isInt, status, "status", asInt);
        
        if (status == 100)
        {
            Json::Value data = root["data"];
            if (!data.isNull())
            {
                CC_GAME_JSON_ADD(data, isInt, m_cash, "mcash", asInt);
                onUpdataView();
                
                QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "支付成功!");
                CCInteger* pobj = CCInteger::create(1);
                QimiPlatform::shareQimiPlatform()->callPayBack(pobj);
            }
        }
        else
        {
            QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "支付失败!");
            CCInteger* pobj = CCInteger::create(0);
            QimiPlatform::shareQimiPlatform()->callPayBack(pobj);
        }
    }
    else
    {
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "服务器异常，请稍后再试");
    }
}

void QimiMainView::SzOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    openPrepaidCard(0);
}

void QimiMainView::LtOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    openPrepaidCard(1);
}

void QimiMainView::DxOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    openPrepaidCard(2);
}

void QimiMainView::qimiCz(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    QimiPlatform::shareQimiPlatform()->openGameWeb(QIMI_CZ, false);
}

void QimiMainView::openPrepaidCard(int kind)
{
//    QimiPrepaidCardView* pQimiPrepaidCardView = QimiPrepaidCardView::create();
//    StageScene::shareStageScene()->m_DialogContainer->addChild(pQimiPrepaidCardView);
//    pQimiPrepaidCardView->initData(m_uId, m_sId, m_key, m_money, kind);
    
    
    //m_money = atoi(money.c_str())*100;
    //m_money =1;//测试数据
    
    QimiPrepaidCardNextView* pQimiPrepaidCardNextView = QimiPrepaidCardNextView::create();
    pQimiPrepaidCardNextView->initData(m_uId, m_sId, m_key, m_money*100, kind);
    StageScene::shareStageScene()->m_DialogContainer->addChild(pQimiPrepaidCardNextView);
    this->removeFromParentAndCleanup(true);
    
}

void QimiMainView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}

void QimiMainView::qimiHelp(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    QimiPlatform::shareQimiPlatform()->openGameWeb(QIMI_HELP, false);
}

///*************需求修改，跳过修改充值金额的页面****************///
void QimiMainView::rechargeOnClick()
{
    //m_money = atoi(m_pEditName->getText());
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://www.qimi.com/platform/addOrder.php");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, httpresponse_selector(QimiMainView::onLoadOrderSucssful));
    
    char sign[255];
    sprintf(sign, "%s%d%s",
            m_uId.c_str(),
            m_sId,
            m_key.c_str());
    QimiMD5 md5;
    md5.update(sign);
    
    CCLog("md5str==%s",sign);
    std::string md5tolower = md5.toString();
    
    CCString* postDataStr = CCString::createWithFormat("uId=%s&sId=%d&sign=%s&money=%d&orderType=alipay&type=0", m_uId.c_str(), m_sId, md5tolower.c_str(), m_money);
    CCLog("addOrder string ===%s", postDataStr->getCString());
    const char* postData =postDataStr->getCString();
    request->setRequestData(postData, strlen(postData));
    
    request->setTag("POST test1");
    CCHttpClient::getInstance()->send(request);
    request->release();
    
    RequestLoadingView* mask = RequestLoadingView::create();
    mask->setTag(100000);
    this->addChild(mask);
    
}

void QimiMainView::onLoadOrderSucssful(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response)
{
    CCNode* node = this->getChildByTag(100000);
    if (node!=NULL)
    {
        node->removeFromParentAndCleanup(true);
    }
    
    Json::Value root = GameUtils::getResponseData(response);
    
    if (root !=NULL && !root.isNull())
    {
        m_oderId= root["data"].asString();
    }
    else
    {
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "服务器异常，请稍后再试");
    }
    loadAlixPay();
}

void QimiMainView::loadAlixPay()
{
std::string appScheme = QimiPlatform::shareQimiPlatform()->getAppScheme();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    QimiPlatformIOS* pQimiPlatformIOS = QimiPlatformIOS::create();
    pQimiPlatformIOS->retain();
    pQimiPlatformIOS->alipayPay(m_oderId,
                                m_money,
                                m_gameInfo.c_str(),
                                "proDes",
                                appScheme.c_str(),
                                QIMI_ALIAPAY_SID,
                                QIMI_ALIAPAY_USERNMAE,
                                QIMI_ALIAPLY_NOTIFY_URL,
                                QIMI_PRIVATE_KEY);
    pQimiPlatformIOS->release();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    payJNI(m_oderId.c_str(),
           m_gameInfo.c_str(),
           "proDes",
           appScheme.c_str(),
           QIMI_ALIAPAY_SID,
           QIMI_ALIAPAY_USERNMAE,
           QIMI_ALIAPLY_NOTIFY_URL,
           QIMI_PRIVATE_KEY,
           m_money);
#endif
    
    //弹出小窗口。
    QimiAlipayDailog* m_pQimiAlipayDailog = QimiAlipayDailog::create();
    m_pQimiAlipayDailog->setPositionY(m_pQimiAlipayDailog->getPositionY()+80);
    StageScene::shareStageScene()->m_DialogContainer->addChild(m_pQimiAlipayDailog);
    
    this->removeFromParentAndCleanup(true);
}

/////*******end********************/





