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
    
    CCSprite* bg = CCSprite::create("bg_dabeijing_480x800.png");
    bg->setPosition(ccp(m_size.width/2, m_size.height/2));
    this->addChild(bg);
    
    
    CCSprite* bgTop = CCSprite::create("bg_top.png");
    this->addChild(bgTop);
    bgTop->setPosition(ccp(240, 755));
    
    
    CCControlButton* backBtn = CCControlButton::create(CCScale9Sprite::create("btn_fanhui.png"));
    backBtn->setPreferredSize(CCSizeMake(101, 51));
    backBtn->setTouchPriority(-1000);
    this->addChild(backBtn);
    backBtn->setPosition(ccp(63, 760));
    backBtn->addTargetWithActionForControlEvents(this,
                                                cccontrol_selector(QimiMainView::backOnClick),
                                                CCControlEventTouchUpInside);

    
    CCControlButton* helpBtn = CCControlButton::create(CCScale9Sprite::create("btn_bangzhu.png"));
    helpBtn->setPreferredSize(CCSizeMake(93, 51));
    helpBtn->setTouchPriority(-1000);
    this->addChild(helpBtn);
    helpBtn->setPosition(ccp(420, 760));
    
    CCLabelTTF* topText = CCLabelTTF::create("奇米支付中心", "Helvetica", 28);
    this->addChild(topText);
    topText->setPosition(ccp(240, 762));
    
    
    
    CCLabelTTF* qimiCopy = CCLabelTTF::create("@2013 奇米网", "Helvetica", 20);
    this->addChild(qimiCopy);
    qimiCopy->setColor(ccc3(94, 94, 94));
    qimiCopy->setPosition(ccp(240, 60));
    
    CCLabelTTF* qimiUrl = CCLabelTTF::create("www.qimi.com", "Helvetica", 20);
    this->addChild(qimiUrl);
    qimiUrl->setColor(ccc3(94, 94, 94));
    qimiUrl->setPosition(ccp(240, 36));
    
    ////////////公共部分结束
    
    
    CCRect form = CCRectMake(0, 0, 40, 40);
    CCRect capInset = CCRectMake(10, 10, 10, 10);
    CCScale9Sprite* scale9Sprite = CCScale9Sprite::create("bg_40x40.png", form, capInset);
    scale9Sprite->setContentSize(CCSizeMake(445, 230));
    scale9Sprite->setPosition(ccp(240, 568));
    this->addChild(scale9Sprite);
    
    
    CCScale9Sprite* scale9Sprite1 = CCScale9Sprite::create("bg_40x40.png", form, capInset);
    scale9Sprite1->setContentSize(CCSizeMake(445, 328));
    scale9Sprite1->setPosition(ccp(240 , 258));
    this->addChild(scale9Sprite1);
    
    
    CCLabelTTF* userInfoTitle = CCLabelTTF::create("个人帐户信息", "Helvetica", 26);
    this->addChild(userInfoTitle);
    userInfoTitle->setColor(ccc3(0, 0, 0));
    userInfoTitle->setPosition(ccp(33, 646));
    userInfoTitle->setAnchorPoint(ccp(0, 0.5));
    
    
    CCLabelTTF* txt_tongxinzheng = CCLabelTTF::create("通 行 证：", "Helvetica", 25);
    this->addChild(txt_tongxinzheng);
    txt_tongxinzheng->setColor(ccc3(0, 0, 0));
    txt_tongxinzheng->setPosition(ccp(33, 599));
    txt_tongxinzheng->setAnchorPoint(ccp(0, 0.5));
    
    
    
    CCLabelTTF* txt_zhanghuyuer = CCLabelTTF::create("充值金额：", "Helvetica", 25);
    this->addChild(txt_zhanghuyuer);
    txt_zhanghuyuer->setColor(ccc3(0, 0, 0));
    txt_zhanghuyuer->setPosition(ccp(33, 561));
    txt_zhanghuyuer->setAnchorPoint(ccp(0, 0.5));
    
    
    CCLabelTTF* txt_productName = CCLabelTTF::create("游戏名称：", "Helvetica", 25);
    this->addChild(txt_productName);
    txt_productName->setColor(ccc3(0, 0, 0));
    txt_productName->setPosition(ccp(33, 523));
    txt_productName->setAnchorPoint(ccp(0, 0.5));
    
    
    CCLabelTTF* txt_GameName = CCLabelTTF::create("充值说明：1人民币=10个游戏币", "Helvetica", 25);
    this->addChild(txt_GameName);
    txt_GameName->setColor(ccc3(0, 0, 0));
    txt_GameName->setPosition(ccp(33, 485));
    txt_GameName->setAnchorPoint(ccp(0, 0.5));
    
    CCLabelTTF* txt_select = CCLabelTTF::create("请选择充值方式：", "Helvetica", 26);
    this->addChild(txt_select);
    txt_select->setColor(ccc3(0, 0, 0));
    txt_select->setPosition(ccp(32, 394));
    txt_select->setAnchorPoint(ccp(0, 0.5));
    
    /////
    m_pPassThroughNumTxt = CCLabelTTF::create("0", "Helvetica",  24);
    this->addChild(m_pPassThroughNumTxt);
    m_pPassThroughNumTxt->setColor(ccc3(0, 0, 0));
    m_pPassThroughNumTxt->setPosition(ccp(150, 599));
    m_pPassThroughNumTxt->setAnchorPoint(ccp(0, 0.5));
    
//    m_pMcashNumTxt = CCLabelTTF::create("0","Helvetica", 24);
//    this->addChild(m_pMcashNumTxt);
//    m_pMcashNumTxt->setColor(ccc3(0, 0, 0));
//    m_pMcashNumTxt->setPosition(ccp(150, 561));
//    m_pMcashNumTxt->setAnchorPoint(ccp(0, 0.5));
    
    m_pProductNameTxt = CCLabelTTF::create("0","Helvetica", 24);
    this->addChild(m_pProductNameTxt);
    m_pProductNameTxt->setColor(ccc3(0, 0, 0));
    m_pProductNameTxt->setPosition(ccp(150, 561));
    m_pProductNameTxt->setAnchorPoint(ccp(0, 0.5));
    
    
    m_pGameNameTxt = CCLabelTTF::create(m_gameInfo.c_str(), "Helvetica", 24);
    this->addChild(m_pGameNameTxt);
    m_pGameNameTxt->setColor(ccc3(0, 0, 0));
    m_pGameNameTxt->setPosition(ccp(150, 523));
    m_pGameNameTxt->setAnchorPoint(ccp(0, 0.5));
    
    
//    m_pMcashNumLastTxt = CCLabelTTF::create("个奇米币", "Helvetica", 24);
//    this->addChild(m_pMcashNumLastTxt);
//    m_pMcashNumLastTxt->setColor(ccc3(0, 0, 0));
//    m_pMcashNumLastTxt->setPosition(ccp(211, 561));
//    m_pMcashNumLastTxt->setAnchorPoint(ccp(0, 0.5));
    
    
//    m_pQimiPayBtn = CCControlButton::create(CCScale9Sprite::create("btn_qimizf.png"));
//    m_pQimiPayBtn->setPreferredSize(CCSizeMake(125, 40));
//    m_pQimiPayBtn->setTouchPriority(-1000);
//    this->addChild(m_pQimiPayBtn);
//    m_pQimiPayBtn->setPosition(ccp(m_pMcashNumLastTxt->getPositionX()+m_pMcashNumLastTxt->getContentSize().width+10, 565));
//    m_pQimiPayBtn->addTargetWithActionForControlEvents(this,
//                                                    cccontrol_selector(QimiMainView::qimiPay),
//                                                    CCControlEventTouchUpInside);
    
    
    
    m_pProductNameLastTxt = CCLabelTTF::create("游戏币", "Helvetica", 24);
    this->addChild(m_pProductNameLastTxt);
    m_pProductNameLastTxt->setColor(ccc3(0, 0, 0));
    m_pProductNameLastTxt->setPosition(ccp(211, 523));
    m_pProductNameLastTxt->setAnchorPoint(ccp(0, 0.5));
    
    
    
    /////////////////
    
    CCControlButton* alixPayBtn = CCControlButton::create(CCScale9Sprite::create("img_zhifubao.png"));
    alixPayBtn->setPreferredSize(CCSizeMake(114, 114));
    alixPayBtn->setTouchPriority(-1000);
    this->addChild(alixPayBtn);
    alixPayBtn->setPosition(ccp(94, 307));
    alixPayBtn->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiMainView::alipayOnClick),
                                                    CCControlEventTouchUpInside);
    
    
    CCControlButton* sZXBtn = CCControlButton::create(CCScale9Sprite::create("img_shenzhouxing.png"));
    sZXBtn->setPreferredSize(CCSizeMake(114, 114));
    sZXBtn->setTouchPriority(-1000);
    this->addChild(sZXBtn);
    sZXBtn->setPosition(ccp(241, 307));
    sZXBtn->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiMainView::SzOnClick),
                                                    CCControlEventTouchUpInside);
    
    CCControlButton* lTBtn = CCControlButton::create(CCScale9Sprite::create("img_liantong.png"));
    lTBtn->setPreferredSize(CCSizeMake(114, 114));
    lTBtn->setTouchPriority(-1000);
    this->addChild(lTBtn);
    lTBtn->setPosition(ccp(386, 307));
    lTBtn->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiMainView::LtOnClick),
                                                    CCControlEventTouchUpInside);
    
    CCControlButton* dXBtn = CCControlButton::create(CCScale9Sprite::create("img_dianxin.png"));
    dXBtn->setPreferredSize(CCSizeMake(114, 114));
    dXBtn->setTouchPriority(-1000);
    this->addChild(dXBtn);
    dXBtn->setPosition(ccp(94, 175));
    dXBtn->addTargetWithActionForControlEvents(this,
                                               cccontrol_selector(QimiMainView::DxOnClick),
                                                    CCControlEventTouchUpInside);
    
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
    if (!root.isNull())
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
    onUpdataView();
    
}
void QimiMainView::onUpdataView()
{
    m_pPassThroughNumTxt->setString(CCString::createWithFormat("%s", m_uId.c_str())->getCString());
    //m_pMcashNumTxt->setString(CCString::createWithFormat("%d", m_cash)->getCString());
    m_pProductNameTxt->setString(CCString::createWithFormat("%d", m_money)->getCString());
    m_pGameNameTxt->setString(m_gameInfo.c_str());
    //float posX = m_pMcashNumTxt->getPosition().x + m_pMcashNumTxt->getContentSize().width;
    //float posY = m_pMcashNumTxt->getPosition().y;
    //m_pMcashNumLastTxt->setPosition(ccp(posX, posY));
    float posX = m_pProductNameTxt->getPosition().x + m_pProductNameTxt->getContentSize().width;
    float posY = m_pProductNameTxt->getPosition().y;
    m_pProductNameLastTxt->setPosition(ccp(posX, posY));
    
    //m_pQimiPayBtn->setPosition(ccp(m_pMcashNumLastTxt->getPositionX()+m_pMcashNumLastTxt->getContentSize().width+75, 565));
}

void QimiMainView::alipayOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    std::string appScheme = QimiPlatform::shareQimiPlatform()->getAppScheme();
    
    QimiAlipayView* pQimiAlipayView = QimiAlipayView::create();
    pQimiAlipayView->initData(m_uId, m_sId, m_key, m_money, appScheme, m_gameInfo); //std::string appScheme, std::string productName);
    StageScene::shareStageScene()->m_DialogContainer->addChild(pQimiAlipayView);
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
    if (!root.isNull())
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

void QimiMainView::openPrepaidCard(int kind)
{
    QimiPrepaidCardView* pQimiPrepaidCardView = QimiPrepaidCardView::create();
    StageScene::shareStageScene()->m_DialogContainer->addChild(pQimiPrepaidCardView);
    pQimiPrepaidCardView->initData(m_uId, m_sId, m_key, m_money, kind);
}

void QimiMainView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}









