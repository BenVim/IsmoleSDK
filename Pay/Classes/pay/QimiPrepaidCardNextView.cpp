//
//  QimiPrepaidCardNextView.cpp
//  Pay
//
//  Created by Ben on 6/25/13.
//
//

#include "QimiPrepaidCardNextView.h"
#include "GameUtils.h"
#include "Qimi.h"
#include "QimiUserModel.h"
#include "QimiPlatform.h"
#include "QimiMD5.h"
#include "QimiPlatformIOS.h"
#include "UIMaskLayerView.h"
#include "RequestLoadingView.h"


QimiPrepaidCardNextView::QimiPrepaidCardNextView()
{
    
}

QimiPrepaidCardNextView::~QimiPrepaidCardNextView()
{
    CC_SAFE_RELEASE(m_pButtonList);
}

bool QimiPrepaidCardNextView::init()
{
    UIMaskLayerView* mask = UIMaskLayerView::create();
    this->addChild(mask);
    
    CCSize m_size = CCDirector::sharedDirector()->getWinSize();
    
    CCNode* container = CCNode::create();
    this->addChild(container);
    container->setPosition(ccp(m_size.width/2, m_size.height/2-45));
    
    CCNode* topCCNode = CCNode::create();
    topCCNode->setPosition(ccp(m_size.width/2, m_size.height-45));
    this->addChild(topCCNode);
    
    m_pButtonList = CCArray::create();
    m_pButtonList->retain();
    
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
                                                 cccontrol_selector(QimiPrepaidCardNextView::backOnClick),
                                                 CCControlEventTouchUpInside);
    
    
    CCControlButton* helpBtn = CCControlButton::create(CCScale9Sprite::create("btn_bangzhu.png"));
    helpBtn->setPreferredSize(CCSizeMake(93, 51));
    helpBtn->setTouchPriority(-1000);
    topCCNode->addChild(helpBtn);
    helpBtn->setPosition(ccp(163, 0));
    helpBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(QimiPrepaidCardNextView::qimiHelp),
                                                 CCControlEventTouchUpInside);
    
    CCLabelTTF* topText = CCLabelTTF::create("奇米支付中心", "Helvetica", 28);
    topCCNode->addChild(topText);
    topText->setColor(ccc3(104, 67, 2));
    topText->setPosition(ccp(0, 0));
    
    /**TOP END*/

    
    
    ////////////公共部分结束
    
    
    CCRect form = CCRectMake(0, 0, 40, 40);
    CCRect capInset = CCRectMake(10, 10, 10, 10);
    CCScale9Sprite* scale9Sprite = CCScale9Sprite::create("bg_40x40.png", form, capInset);
    scale9Sprite->setContentSize(CCSizeMake(445, 580));
    scale9Sprite->setPosition(ccp(0, 12));
    container->addChild(scale9Sprite);
    
//    CCNode* containerCCNode = CCNode::create();
//    this->addChild(containerCCNode);
//    containerCCNode->setPosition(ccp(0, 0));
    
    CCLabelTTF* txtTitle = CCLabelTTF::create("请选择充值卡面额", "Helvetica", 26);
    container->addChild(txtTitle);
    txtTitle->setColor(ccc3(0, 0, 0));
    txtTitle->setPosition(ccp(-204, 259));
    txtTitle->setAnchorPoint(ccp(0, 0.5));
    
    CCControlButton* m_pBtnCongzhi = CCControlButton::create(CCScale9Sprite::create("btn_querenchongzhi.png"));
    m_pBtnCongzhi->setPreferredSize(CCSizeMake(248, 74));
    m_pBtnCongzhi->setTouchPriority(-1000);
    container->addChild(m_pBtnCongzhi);
    m_pBtnCongzhi->setPosition(ccp(0, -220));
    m_pBtnCongzhi->addTargetWithActionForControlEvents(this,
                                                       cccontrol_selector(QimiPrepaidCardNextView::rechargeOnClick),
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
                                                        cccontrol_selector(QimiPrepaidCardNextView::selected),
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
                                                        cccontrol_selector(QimiPrepaidCardNextView::selected),
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
                                                        cccontrol_selector(QimiPrepaidCardNextView::selected),
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
                                                        cccontrol_selector(QimiPrepaidCardNextView::selected),
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
                                                         cccontrol_selector(QimiPrepaidCardNextView::selected),
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
                                                         cccontrol_selector(QimiPrepaidCardNextView::selected),
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
                                                         cccontrol_selector(QimiPrepaidCardNextView::selected),
                                                         CCControlEventTouchUpInside);
    
    
    m_pButtonList->addObject(m_pBtn10Select);
    m_pButtonList->addObject(m_pBtn20Select);
    m_pButtonList->addObject(m_pBtn30Select);
    m_pButtonList->addObject(m_pBtn50Select);
    m_pButtonList->addObject(m_pBtn100Select);
    m_pButtonList->addObject(m_pBtn300Select);
    m_pButtonList->addObject(m_pBtn500Select);
    
    
    cocos2d::extension::CCScale9Sprite* m_pInputTxtBg = CCScale9Sprite::create("loginbg.png");
    
    
    m_pInputTxtBg->removeFromParentAndCleanup(false);
    m_denomination =0;
    CCSize editBoxSize = CCSizeMake(350, 45);
    
    m_pInputCarNumTxtBg = CCScale9Sprite::create("loginbg.png");
    
    m_pInputCarNumTxtBg->removeFromParentAndCleanup(false);
    m_pCardNum = CCEditBox::create(editBoxSize, m_pInputCarNumTxtBg);
    m_pCardNum->setPosition(ccp(30, -80));
    m_pCardNum->setFontColor(ccc3(255,0,0));
    m_pCardNum->setMaxLength(20);
    m_pCardNum->setReturnType(kKeyboardReturnTypeDone);
    m_pCardNum->setTouchPriority(-1000);
    m_pCardNum->setText("");
    m_pCardNum->setInputMode(kEditBoxInputModeNumeric);
    m_pCardNum->setDelegate(this);
    container->addChild(m_pCardNum);
    
    m_pInputCarPassTxtBg = CCScale9Sprite::create("loginbg.png");
    m_pInputCarPassTxtBg->removeFromParentAndCleanup(false);
    m_pCardPassword = CCEditBox::create(editBoxSize, m_pInputCarPassTxtBg);
    m_pCardPassword->setPosition(ccp(30, -140));
    m_pCardPassword->setFontColor(ccc3(255,0,0));
    m_pCardPassword->setMaxLength(20);
    m_pCardPassword->setReturnType(kKeyboardReturnTypeDone);
    m_pCardPassword->setTouchPriority(-1000);
    m_pCardPassword->setText("");
    m_pCardPassword->setInputMode(kEditBoxInputModeNumeric);
    m_pCardPassword->setDelegate(this);
    container->addChild(m_pCardPassword);
    
    CCLabelTTF* labe = CCLabelTTF::create("请输入充值卡信息：", "Helvetica", 20);
    container->addChild(labe);
    labe->setColor(ccc3(0, 0, 0));
    labe->setPosition(ccp(-200, -30));
    labe->setAnchorPoint(ccp(0, 0.5));
    

    
    CCLabelTTF* label02 = CCLabelTTF::create("卡号：", "Helvetica", 20);
    container->addChild(label02);
    label02->setColor(ccc3(0, 0, 0));
    label02->setPosition(ccp(-200, -80));
    label02->setAnchorPoint(ccp(0, 0.5));
    
    CCLabelTTF* label03 = CCLabelTTF::create("密码：", "Helvetica", 20);
    container->addChild(label03);
    label03->setColor(ccc3(0, 0, 0));
    label03->setPosition(ccp(-200, -140));
    label03->setAnchorPoint(ccp(0, 0.5));
    
    return true;
}

void QimiPrepaidCardNextView::initData(std::string uId, int sId, std::string key, int money, int kind)
{
    m_uId = uId;
    m_sId = sId;
    m_key = key;
    m_money = money;
}

void QimiPrepaidCardNextView::upDataView(int pay)
{
    
}

void QimiPrepaidCardNextView::selected(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    CCControlButton* btn = dynamic_cast<CCControlButton*>(pSender);
    m_denomination =btn->getTag();
    upSelectState(btn);
}

void QimiPrepaidCardNextView::upSelectState(cocos2d::extension::CCControlButton *btn)
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

void QimiPrepaidCardNextView::nextOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    
}

void QimiPrepaidCardNextView::rechargeOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    //充值。。。 调用接口
    //m_money 最终需要充值的数量
    if (m_denomination == 0)
    {
        CCLog("m_denomination number is 0");
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "请选择您的充值卡面额!");
        return;
    }
    
    std::string str = std::string(m_pCardNum->getText());
    if (str.empty())
    {
        CCLog("card number is NULL");
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "请输入充值卡号");
        return;
    }
    
    std::string strPass = std::string(m_pCardPassword->getText());
    if (strPass.empty())
    {
        CCLog("strPass number is NULL");
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "请输入充值卡密码");
        return;
    }
    
    
    
    requestOrder();
    CCLog("充值卡 money（分）= %d 种类 %d, 面额：%d", m_money , m_kind, m_denomination);
}

void QimiPrepaidCardNextView::requestOrder()
{
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://www.qimi.com/platform/addOrder.php");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, httpresponse_selector(QimiPrepaidCardNextView::requestSucssful));
    
    char sign[255];
    sprintf(sign, "%s%d%s",
            m_uId.c_str(),
            m_sId,
            m_key.c_str());
    QimiMD5 md5;
    md5.update(sign);
    
    CCLog("md5str==%s",sign);
    std::string md5tolower = md5.toString();
    
    
    std::string cardNum = m_pCardNum->getText();
    std::string cardPass = m_pCardPassword->getText();
    int denomination =  m_denomination;
    
    CCString* postDataStr = CCString::createWithFormat("uId=%s&sId=%d&sign=%s&carNum=%s&carPass=%s&denomination=%d&orderType=shenzhoufupay&type=%d&money=%d", m_uId.c_str(), m_sId, md5tolower.c_str(), cardNum.c_str(), cardPass.c_str(), denomination, m_kind, m_money);
    
    const char* postData = postDataStr->getCString();
    CCLog("postData=%s", postData);
    request->setRequestData(postData, strlen(postData));
    
    request->setTag("POST test1");
    CCHttpClient::getInstance()->send(request);
    request->release();
    
    RequestLoadingView* mask = RequestLoadingView::create();
    mask->setTag(100000);
    this->addChild(mask);
    
}


void QimiPrepaidCardNextView::requestSucssful(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response)
{
    CCNode* node = this->getChildByTag(100000);
    if (node!=NULL)
    {
        node->removeFromParentAndCleanup(true);
    }
    
    std::string oderId = "";
    std::string cardInfo = "";
    
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
    
    QimiMD5 md5;
    md5.update(md5str);
    
    CCLog("md5str==%s",md5str.c_str());
    
    std::string md5tolower = md5.toString();
    //GameUtils::getStringWithMd5(md5str);
    //std::transform(md5tolower.begin(), md5tolower.end(), md5tolower.begin(), ::tolower);
    pOder->setMd5String(md5tolower);
    reqeuestPay(pOder);
}

void QimiPrepaidCardNextView::reqeuestPay(PrepaidCardOrder *pOrder)
{
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://pay3.shenzhoufu.com/interface/version3/serverconnszx/entry-noxml.aspx");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, httpresponse_selector(QimiPrepaidCardNextView::requestPaySucssful));
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
    
    RequestLoadingView* mask = RequestLoadingView::create();
    mask->setTag(100001);
    this->addChild(mask);
    
}

void QimiPrepaidCardNextView::requestPaySucssful(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response)
{
    CCNode* node = this->getChildByTag(100001);
    if (node!=NULL)
    {
        node->removeFromParentAndCleanup(true);
    }
    
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
    
//    switch (statusCode) {
//        case 200:
//        {
//            QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "充值已成功！");//CCLog("充值已成功！");
//            CCInteger* obj = CCInteger::create(1);
//            QimiPlatform::shareQimiPlatform()->callPayBack(obj);
//        }
//            break;
//        case 101:
//            QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "异常错误！");//CCLog("异常错误");
//            break;
//        default:
//            break;
//    }
    
    int errCode = atoi(responseData.c_str());
    std::string errMsg = "";
    switch (errCode) {
        case 101:
            errMsg = "md5 验证失败";
            break;
        case 102:
            errMsg = "订单号重复";
            break;
        case 103:
            errMsg = "恶意用户";
            break;
        case 104:
            errMsg = "序列号,密码简单验证失败或之前曾提交过的卡密已验证失败";
            break;
        case 105:
            errMsg = "密码正在处理中";
            break;
        case 106:
            errMsg = "系统繁忙,暂停提交";
            break;
        case 107:
            errMsg = "卡内余额不足";//多次支付时卡内余额不足
            break;
        case 109:
            errMsg = "des 解密失败";
            break;
        case 201:
            errMsg = "证书验证失败";
            break;
        case 501:
            errMsg = "插入数据库失败";
            break;
        case 502:
            errMsg = "插入数据库失败";
            break;
        case 200:
            errMsg = "支付成功，请刷新";//请求成功,神州付收单(非订单支付成功)
            break;
        case 902:
            errMsg = "商户参数不全";
            break;
        case 903:
            errMsg = "商户 ID 不存在";
            break;
        case 904:
            errMsg = "商户没有激活";
            break;
        case 905:
            errMsg = "商户没有使用该接口的权限";
            break;
        case 906:
            errMsg = "商户没有设置 密钥(privateKey)";
            break;
        case 907:
            errMsg = "商户没有设置 DES 密钥";
            break;
        case 908:
            errMsg = "该笔订单已经处理完成";//该笔订单已经处理完成(订单状态已经为确定的状态:成功 或 者 失败)
            break;
        case 909:
            errMsg = "该笔订单不符合重复支付的条件";
            break;
        case 910:
            errMsg = "服务器返回地址,不符合规范";
            break;
        case 911:
            errMsg = "订单号,不符合规范";
            break;
        case 912:
            errMsg = "非法订单";
            break;
        case 913:
            errMsg = "该地方卡暂时不支持";
            break;
        case 914:
            errMsg = "支付金额非法";
            break;
        case 915:
            errMsg = "卡面额非法";
            break;
        case 916:
            errMsg = "商户不支持该充值卡的支付";
            break;
        case 917:
            errMsg = "参数格式不正确";
            break;
            case 0:
            errMsg = "网络连接失败";
            break;
            
        default:
            break;
    }
    
    QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", errMsg);//CCLog("充值已成功！");
    if (errCode == 200)
    {
        CCInteger* obj = CCInteger::create(1);
        QimiPlatform::shareQimiPlatform()->callPayBack(obj);
    }
    else
    {
        CCInteger* obj = CCInteger::create(0);
        QimiPlatform::shareQimiPlatform()->callPayBack(obj);
    }
    this->removeFromParentAndCleanup(true);
}


void QimiPrepaidCardNextView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}

void QimiPrepaidCardNextView::qimiHelp(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    QimiPlatform::shareQimiPlatform()->openGameWeb(QIMI_HELP);
}


void QimiPrepaidCardNextView::editBoxEditingDidBegin(CCEditBox *editBox)
{
    if (m_denomination == 0)
    {
        CCLog("m_denomination number is 0");
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "请选择您的充值卡面额!");
        return;
    }
}

void QimiPrepaidCardNextView::editBoxEditingDidEnd(CCEditBox *editBox)
{
    
}

void QimiPrepaidCardNextView::editBoxTextChanged(CCEditBox *editBox,const std::string &text)
{
    
}

void QimiPrepaidCardNextView::editBoxReturn(CCEditBox *editBox)
{

}





