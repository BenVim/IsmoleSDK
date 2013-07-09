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
#include "QimiPlatformIOS.h"
#include "UIMaskLayerView.h"
#include "RequestLoadingView.h"
#include "PlatformUtilityHelper.h"
#include "QimiAlipayDailog.h"
#include "StageScene.h"

QimiAlipayView::QimiAlipayView():isSelelcted(NULL)
{
    
}

QimiAlipayView::~QimiAlipayView()
{
    
}

bool QimiAlipayView::init()
{
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
                                                 cccontrol_selector(QimiAlipayView::backOnClick),
                                                 CCControlEventTouchUpInside);
    
    
    CCControlButton* helpBtn = CCControlButton::create(CCScale9Sprite::create("btn_bangzhu.png"));
    helpBtn->setPreferredSize(CCSizeMake(93, 51));
    helpBtn->setTouchPriority(-1000);
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
    
    CCNode* containerCCNode = CCNode::create();
    this->addChild(containerCCNode);
    containerCCNode->setPosition(ccp(6, 418));

    CCLabelTTF* txtTitle = CCLabelTTF::create("请选择充值金额（1元=10奇米币）", "Helvetica", 26);
    containerCCNode->addChild(txtTitle);
    txtTitle->setColor(ccc3(0, 0, 0));
    txtTitle->setPosition(ccp(27, 237));
    txtTitle->setAnchorPoint(ccp(0, 0.5));
    
    
    CCControlButton* m_pBtnCongzhi = CCControlButton::create(CCScale9Sprite::create("btn_querenchongzhi.png"));
    m_pBtnCongzhi->setPreferredSize(CCSizeMake(248, 74));
    m_pBtnCongzhi->setTouchPriority(-1000);
    containerCCNode->addChild(m_pBtnCongzhi);
    m_pBtnCongzhi->setPosition(ccp(233, -189));
    m_pBtnCongzhi->addTargetWithActionForControlEvents(this,
                                                         cccontrol_selector(QimiAlipayView::rechargeOnClick),
                                                         CCControlEventTouchUpInside);

    
    
    
    CCLabelTTF* label10 = CCLabelTTF::create("10元", "Helvetica", 18);
    label10->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn10Select = CCControlButton::create(label10, CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn10Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn10Select->setTouchPriority(-1000);
    containerCCNode->addChild(m_pBtn10Select);
    m_pBtn10Select->setPosition(ccp(127, 170));
    m_pBtn10Select->setTag(10);
    m_pBtn10Select->addTargetWithActionForControlEvents(this,
                                                    cccontrol_selector(QimiAlipayView::selected),
                                                    CCControlEventTouchUpInside);
    
   
    CCLabelTTF* label20 = CCLabelTTF::create("20元", "Helvetica", 18);
    label20->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn20Select = CCControlButton::create(label20, CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn20Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn20Select->setTouchPriority(-1000);
    containerCCNode->addChild(m_pBtn20Select);
    m_pBtn20Select->setPosition(ccp(338, 170));
    m_pBtn20Select->setTag(20);
    m_pBtn20Select->addTargetWithActionForControlEvents(this,
                                                        cccontrol_selector(QimiAlipayView::selected),
                                                        CCControlEventTouchUpInside);

    CCLabelTTF* label30 = CCLabelTTF::create("30元", "Helvetica", 18);
    label30->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn30Select = CCControlButton::create(label30,CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn30Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn30Select->setTouchPriority(-1000);
    containerCCNode->addChild(m_pBtn30Select);
    m_pBtn30Select->setPosition(ccp(127, 114));
    m_pBtn30Select->setTag(30);
    m_pBtn30Select->addTargetWithActionForControlEvents(this,
                                                        cccontrol_selector(QimiAlipayView::selected),
                                                        CCControlEventTouchUpInside);
    
    CCLabelTTF* label50 = CCLabelTTF::create("50元", "Helvetica", 18);
    label50->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn50Select = CCControlButton::create(label50, CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn50Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn50Select->setTouchPriority(-1000);
    containerCCNode->addChild(m_pBtn50Select);
    m_pBtn50Select->setPosition(ccp(338, 114));
    m_pBtn50Select->setTag(50);
    m_pBtn50Select->addTargetWithActionForControlEvents(this,
                                                        cccontrol_selector(QimiAlipayView::selected),
                                                        CCControlEventTouchUpInside);
    
    CCLabelTTF* label100 = CCLabelTTF::create("100元", "Helvetica", 18);
    label100->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn100Select = CCControlButton::create(label100,CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn100Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn100Select->setTouchPriority(-1000);
    containerCCNode->addChild(m_pBtn100Select);
    m_pBtn100Select->setPosition(ccp(127, 60));
    m_pBtn100Select->setTag(100);
    m_pBtn100Select->addTargetWithActionForControlEvents(this,
                                                        cccontrol_selector(QimiAlipayView::selected),
                                                        CCControlEventTouchUpInside);
    
    CCLabelTTF* label300 = CCLabelTTF::create("300元", "Helvetica", 18);
    label300->setColor(ccc3(0, 0, 0));
    CCControlButton* m_pBtn300Select = CCControlButton::create(label300, CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn300Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn300Select->setTouchPriority(-1000);
    containerCCNode->addChild(m_pBtn300Select);
    m_pBtn300Select->setPosition(ccp(338, 60));
    m_pBtn300Select->setTag(300);
    m_pBtn300Select->addTargetWithActionForControlEvents(this,
                                                         cccontrol_selector(QimiAlipayView::selected),
                                                         CCControlEventTouchUpInside);
    
    CCLabelTTF* label500 = CCLabelTTF::create("500元", "Helvetica", 18);
    label500->setColor(ccc3(0, 0, 0));
    
    CCControlButton* m_pBtn500Select = CCControlButton::create(label500, CCScale9Sprite::create("bg_40x40.png"));
    m_pBtn500Select->setPreferredSize(CCSizeMake(196, 47));
    m_pBtn500Select->setTouchPriority(-1000);
    containerCCNode->addChild(m_pBtn500Select);
    m_pBtn500Select->setPosition(ccp(127, 4));
    m_pBtn500Select->setTag(500);
    m_pBtn500Select->addTargetWithActionForControlEvents(this,
                                                         cccontrol_selector(QimiAlipayView::selected),
                                                         CCControlEventTouchUpInside);
    
    
    cocos2d::extension::CCScale9Sprite* m_pInputTxtBg = CCScale9Sprite::create("loginbg.png");
    CCSize editBoxSize = CCSizeMake(200, 45);
    m_pInputTxtBg->removeFromParentAndCleanup(false);
    m_pEditName = CCEditBox::create(editBoxSize, m_pInputTxtBg);
    m_pEditName->setPosition(ccp(133, 360));
    m_pEditName->setFontColor(ccc3(255, 0, 0));
    m_pEditName->setMaxLength(20);
    m_pEditName->setReturnType(kKeyboardReturnTypeDone);
    m_pEditName->setTouchPriority(-1000);
    m_pEditName->setText("10");
    addChild(m_pEditName);
    
    
    CCLabelTTF* yuan = CCLabelTTF::create("元", "Helvetica", 20);
    this->addChild(yuan);
    yuan->setColor(ccc3(0, 0, 0));
    yuan->setPosition(ccp(240, 359));
    yuan->setAnchorPoint(ccp(0, 0.5));
    
    CCLabelTTF* label01 = CCLabelTTF::create("您将充值", "Helvetica", 20);
    containerCCNode->addChild(label01);
    label01->setColor(ccc3(0, 0, 0));
    label01->setPosition(ccp(32, -105));
    label01->setAnchorPoint(ccp(0, 0.5));
    
    m_pMcashNumTxt = CCLabelTTF::create("1", "Helvetica", 20);
    m_pMcashNumTxt->setColor(ccc3(196, 9, 9));
    m_pMcashNumTxt->setPosition(ccp(115, -105));
    m_pMcashNumTxt->setAnchorPoint(ccp(0, 0.5));
    containerCCNode->addChild(m_pMcashNumTxt);
    
    m_pMcashNumLastTxt = CCLabelTTF::create("奇米币", "Helvetica", 20);
    containerCCNode->addChild(m_pMcashNumLastTxt);
    m_pMcashNumLastTxt->setColor(ccc3(0, 0, 0));
    m_pMcashNumLastTxt->setPosition(ccp(147, -105));
    m_pMcashNumLastTxt->setAnchorPoint(ccp(0, 0.5));
    return true;
}


void QimiAlipayView::initData(std::string uId, int sId, std::string key, int money, std::string appScheme, std::string productName)
{
    m_uId           = uId;
    m_sId           = sId;
    m_key           = key;
    m_money         = money;
    m_appScheme     = appScheme;
    m_productName   = productName;
    
    upDataView(money);
}

void QimiAlipayView::upDataView(int pay)
{
    m_money = pay;
    m_pEditName->setText(CCString::createWithFormat("%d", pay)->getCString());
    m_pMcashNumTxt->setString(CCString::createWithFormat("%d", pay*10)->getCString());
    float posX = m_pMcashNumTxt->getPosition().x + m_pMcashNumTxt->getContentSize().width;
    float posY = m_pMcashNumTxt->getPosition().y;
    
    m_pMcashNumLastTxt->setPosition(ccp(posX, posY));
}

void QimiAlipayView::selected(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    CCControlButton* btn = dynamic_cast<CCControlButton*>(pSender);
    int pay = btn->getTag();
    CCLog("%d", pay);
    upDataView(pay);
}

void QimiAlipayView::upSelectState(int index)
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

void QimiAlipayView::rechargeOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    m_money = atoi(m_pEditName->getText());
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://www.qimi.com/platform/addOrder.php");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, httpresponse_selector(QimiAlipayView::onLoadOrderSucssful));
    
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

void QimiAlipayView::onLoadOrderSucssful(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response)
{
    CCNode* node = this->getChildByTag(100000);
    if (node!=NULL)
    {
        node->removeFromParentAndCleanup(true);
    }
    
    Json::Value root = GameUtils::getResponseData(response);
    
    if (!root.isNull())
    {
        m_oderId= root["data"].asString();
    }
    loadAlixPay();
}

void QimiAlipayView::loadAlixPay()
{

    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    QimiPlatformIOS* pQimiPlatformIOS = QimiPlatformIOS::create();
    pQimiPlatformIOS->retain();
    pQimiPlatformIOS->alipayPay(m_oderId,
                                m_money,
                                m_productName,
                                "proDes",
                                m_appScheme,
                                QIMI_ALIAPAY_SID,
                                QIMI_ALIAPAY_USERNMAE,
                                "http://www.qimi.com/pay/alipay/notify_url.php",
                                QIMI_PRIVATE_KEY);
    pQimiPlatformIOS->release();
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    payJNI(m_oderId.c_str(),
           m_productName.c_str(),
           "proDes",
           m_appScheme.c_str(),
           QIMI_ALIAPAY_SID,
           QIMI_ALIAPAY_USERNMAE,
           "http://www.qimi.com/pay/alipay/notify_url.php",
           QIMI_PRIVATE_KEY,
           m_money);
#endif
    
    //弹出小窗口。
    QimiAlipayDailog* m_pQimiAlipayDailog = QimiAlipayDailog::create();
    m_pQimiAlipayDailog->setPositionY(m_pQimiAlipayDailog->getPositionY()+80);
    StageScene::shareStageScene()->m_DialogContainer->addChild(m_pQimiAlipayDailog);
    
    this->removeFromParentAndCleanup(true);
}

void QimiAlipayView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}









