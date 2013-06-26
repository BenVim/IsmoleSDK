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

QimiMainView::QimiMainView()
{
    
}

QimiMainView::~QimiMainView()
{
    
}

bool QimiMainView::init()
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
                                                cccontrol_selector(QimiMainView::backOnClick),
                                                CCControlEventTouchUpInside);

    
    CCControlButton* helpBtn = CCControlButton::create(CCScale9Sprite::create("btn_bangzhu.png"));
    helpBtn->setPreferredSize(CCSizeMake(93, 51));
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
    
    CCLabelTTF* txt_zhanghuyuer = CCLabelTTF::create("帐户余额：", "Helvetica", 25);
    this->addChild(txt_zhanghuyuer);
    txt_zhanghuyuer->setColor(ccc3(0, 0, 0));
    txt_zhanghuyuer->setPosition(ccp(33, 561));
    txt_zhanghuyuer->setAnchorPoint(ccp(0, 0.5));
    
    
    CCLabelTTF* txt_productName = CCLabelTTF::create("产品名称：", "Helvetica", 25);
    this->addChild(txt_productName);
    txt_productName->setColor(ccc3(0, 0, 0));
    txt_productName->setPosition(ccp(33, 523));
    txt_productName->setAnchorPoint(ccp(0, 0.5));
    
    
    CCLabelTTF* txt_GameName = CCLabelTTF::create("游戏名称：", "Helvetica", 25);
    this->addChild(txt_GameName);
    txt_GameName->setColor(ccc3(0, 0, 0));
    txt_GameName->setPosition(ccp(33, 485));
    txt_GameName->setAnchorPoint(ccp(0, 0.5));
    
    CCLabelTTF* txt_select = CCLabelTTF::create("请选择充值方式：", "Helvetica", 26);
    this->addChild(txt_select);
    txt_select->setColor(ccc3(0, 0, 0));
    txt_select->setPosition(ccp(32, 394));
    txt_select->setAnchorPoint(ccp(0, 0.5));
    
    
    CCControlButton* alixPayBtn = CCControlButton::create(CCScale9Sprite::create("img_zhifubao.png"));
    alixPayBtn->setPreferredSize(CCSizeMake(114, 114));
    this->addChild(alixPayBtn);
    alixPayBtn->setPosition(ccp(94, 307));
    alixPayBtn->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiMainView::alipayOnClick),
                                                    CCControlEventTouchUpInside);
    
    
    CCControlButton* sZXBtn = CCControlButton::create(CCScale9Sprite::create("img_shenzhouxing.png"));
    sZXBtn->setPreferredSize(CCSizeMake(114, 114));
    this->addChild(sZXBtn);
    sZXBtn->setPosition(ccp(241, 307));
    sZXBtn->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiMainView::SzOnClick),
                                                    CCControlEventTouchUpInside);
    
    CCControlButton* lTBtn = CCControlButton::create(CCScale9Sprite::create("img_liantong.png"));
    lTBtn->setPreferredSize(CCSizeMake(114, 114));
    this->addChild(lTBtn);
    lTBtn->setPosition(ccp(386, 307));
    lTBtn->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiMainView::LtOnClick),
                                                    CCControlEventTouchUpInside);
    
    CCControlButton* dXBtn = CCControlButton::create(CCScale9Sprite::create("img_dianxin.png"));
    dXBtn->setPreferredSize(CCSizeMake(114, 114));
    this->addChild(dXBtn);
    dXBtn->setPosition(ccp(94, 175));
    dXBtn->addTargetWithActionForControlEvents(this,
                                               cccontrol_selector(QimiMainView::DxOnClick),
                                                    CCControlEventTouchUpInside);
    
    return true;
}

void QimiMainView::initView(std::string uId, int sId, std::string key, int money)
{
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
    request->setResponseCallback(this, callfuncND_selector(QimiMainView::onLoadRequestSucssful));
    
    
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
}

void QimiMainView::onLoadRequestSucssful(cocos2d::CCNode *sender, void *data)
{
    CCHttpResponse *response = (CCHttpResponse*)data;
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
    CCLabelTTF* m_pPassThroughNumTxt = CCLabelTTF::create(CCString::createWithFormat("%s", m_uId.c_str())->getCString(),
                                                          "Helvetica",
                                                          24);
    this->addChild(m_pPassThroughNumTxt);
    m_pPassThroughNumTxt->setColor(ccc3(0, 0, 0));
    m_pPassThroughNumTxt->setPosition(ccp(150, 599));
    m_pPassThroughNumTxt->setAnchorPoint(ccp(0, 0.5));
    
    CCLabelTTF* m_pMcashNumTxt = CCLabelTTF::create(CCString::createWithFormat("%d", m_cash)->getCString(),
                                                          "Helvetica",
                                                          24);
    this->addChild(m_pMcashNumTxt);
    m_pMcashNumTxt->setColor(ccc3(0, 0, 0));
    m_pMcashNumTxt->setPosition(ccp(150, 561));
    m_pMcashNumTxt->setAnchorPoint(ccp(0, 0.5));
    
    CCLabelTTF* m_pProductNameTxt = CCLabelTTF::create(CCString::createWithFormat("%d", m_money)->getCString(),
                                                    "Helvetica",
                                                    24);
    this->addChild(m_pProductNameTxt);
    m_pProductNameTxt->setColor(ccc3(0, 0, 0));
    m_pProductNameTxt->setPosition(ccp(150, 523));
    m_pProductNameTxt->setAnchorPoint(ccp(0, 0.5));
    
    
    CCLabelTTF* m_pGameNameTxt = CCLabelTTF::create(m_gameInfo.c_str(), "Helvetica", 24);
    this->addChild(m_pGameNameTxt);
    m_pGameNameTxt->setColor(ccc3(0, 0, 0));
    m_pGameNameTxt->setPosition(ccp(150, 485));
    m_pGameNameTxt->setAnchorPoint(ccp(0, 0.5));
    
    
    CCLabelTTF* m_pMcashNumLastTxt = CCLabelTTF::create("个奇米币", "Helvetica", 24);
    this->addChild(m_pMcashNumLastTxt);
    m_pMcashNumLastTxt->setColor(ccc3(0, 0, 0));
    m_pMcashNumLastTxt->setPosition(ccp(211, 561));
    m_pMcashNumLastTxt->setAnchorPoint(ccp(0, 0.5));
    
    
    CCLabelTTF* m_pProductNameLastTxt = CCLabelTTF::create("个奇米币", "Helvetica", 24);
    this->addChild(m_pProductNameLastTxt);
    m_pProductNameLastTxt->setColor(ccc3(0, 0, 0));
    m_pProductNameLastTxt->setPosition(ccp(211, 523));
    m_pProductNameLastTxt->setAnchorPoint(ccp(0, 0.5));
    
    
    float posX = m_pMcashNumTxt->getPosition().x + m_pMcashNumTxt->getContentSize().width;
    float posY = m_pMcashNumTxt->getPosition().y;
    m_pMcashNumLastTxt->setPosition(ccp(posX, posY));
    posX = m_pProductNameTxt->getPosition().x + m_pProductNameTxt->getContentSize().width;
    posY = m_pProductNameTxt->getPosition().y;
    m_pProductNameLastTxt->setPosition(ccp(posX, posY));
}

void QimiMainView::alipayOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    //QimiAlipayView
    QimiAlipayView* pQimiAlipayView = QimiAlipayView::create();
    pQimiAlipayView->initData(m_uId, m_sId, m_key, m_money);
    StageScene::shareStageScene()->m_DialogContainer->addChild(pQimiAlipayView);
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







