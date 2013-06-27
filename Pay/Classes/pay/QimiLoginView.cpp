//
//  QimiLoginView.cpp
//  Pay
//
//  Created by Ben on 6/24/13.
//
//

#include "QimiLoginView.h"
#include "GameUtils.h"
#include "Qimi.h"
#include "QimiUserModel.h"
#include "QimiPlatform.h"
#include "QimiMD5.h"
#include "UIMaskLayerView.h"
#include "RequestLoadingView.h"

QimiLoginView::QimiLoginView():
isSelelcted(NULL),
m_pRememberSprite(NULL),
m_pNoRememberSprite(NULL),
m_pInputUserNameTxtBg(NULL),
m_pInputUserPassTxtBg(NULL),
m_pUserName(NULL),
m_pPassWorld(NULL)
{
    
}

QimiLoginView::~QimiLoginView()
{
    
    
}

bool QimiLoginView::init()
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
    backBtn->setTouchPriority(-1001);
    this->addChild(backBtn);
    backBtn->setPosition(ccp(63, 760));
    backBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(QimiLoginView::backOnClick),
                                                 CCControlEventTouchUpInside);

    
    CCControlButton* helpBtn = CCControlButton::create(CCScale9Sprite::create("btn_bangzhu.png"));
    helpBtn->setPreferredSize(CCSizeMake(93, 51));
    helpBtn->setTouchPriority(-1001);
    this->addChild(helpBtn);
    helpBtn->setPosition(ccp(420, 760));

    
    CCLabelTTF* topText = CCLabelTTF::create("奇米网", "Helvetica", 28);
    this->addChild(topText);
    topText->setPosition(ccp(240, 762));
    
    
    ////////////公共部分结束
    CCSprite* qimiLogo = CCSprite::create("logo.png");
    qimiLogo->setPosition(ccp(236,611));
    this->addChild(qimiLogo);
    
    CCSprite* userBg = CCSprite::create("bg_zhanghao.png");
    userBg->setPosition(ccp(242, 471));
    this->addChild(userBg);
    
    CCSprite* passBg = CCSprite::create("bg_mima.png");
    passBg->setPosition(ccp(242, 387));
    this->addChild(passBg);
    
    
    CCControlButton* m_pLoginBtn = CCControlButton::create(CCScale9Sprite::create("btn_denglu.png"));
    m_pLoginBtn->setPreferredSize(CCSizeMake(200, 75));
    m_pLoginBtn->setTouchPriority(-1001);
    this->addChild(m_pLoginBtn);
    m_pLoginBtn->setPosition(ccp(133, 221));
    m_pLoginBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(QimiLoginView::loginOnclick),
                                                 CCControlEventTouchUpInside);

    
    CCControlButton* m_pRegisterBtn = CCControlButton::create(CCScale9Sprite::create("btn_zhuce_small.png"));
    m_pRegisterBtn->setPreferredSize(CCSizeMake(200, 75));
    m_pRegisterBtn->setTouchPriority(-1001);
    this->addChild(m_pRegisterBtn);
    m_pRegisterBtn->setPosition(ccp(350, 221));
    m_pRegisterBtn->addTargetWithActionForControlEvents(this,
                                                     cccontrol_selector(QimiLoginView::registerOnClick),
                                                     CCControlEventTouchUpInside);

    m_pNoRememberSprite = CCSprite::create("btn_jizhumima_left.png");
    m_pNoRememberSprite->setPosition(ccp(168, 306));
    this->addChild(m_pNoRememberSprite);
    
    m_pRememberSprite = CCSprite::create("btn_jizhumima_right.png");
    m_pRememberSprite->setVisible(false);
    m_pRememberSprite->setPosition(ccp(168, 306));
    this->addChild(m_pRememberSprite);
    
    CCSize editBoxSize = CCSizeMake(300, 50);
    
    m_pInputUserNameTxtBg = CCScale9Sprite::create("loginbg.png");
    m_pInputUserPassTxtBg = CCScale9Sprite::create("loginbg.png");
    
    this->addChild(m_pInputUserNameTxtBg);
    this->addChild(m_pInputUserPassTxtBg);
    
    m_pInputUserNameTxtBg->removeFromParentAndCleanup(false);
    m_pUserName = CCEditBox::create(editBoxSize, m_pInputUserNameTxtBg);
    m_pUserName->setPosition(ccp(247, 472));
    m_pUserName->setFontColor(ccc3(178,178,178));
    m_pUserName->setMaxLength(50);
    m_pUserName->setReturnType(kKeyboardReturnTypeDone);
    m_pUserName->setTouchPriority(-1002);
    m_pUserName->setText("您的电子邮箱地址");
    m_pUserName->setInputMode(kEditBoxInputModeEmailAddr);
    addChild(m_pUserName);
    
    m_pInputUserPassTxtBg->removeFromParentAndCleanup(false);
    m_pPassWorld = CCEditBox::create(editBoxSize, m_pInputUserPassTxtBg);
    m_pPassWorld->setPosition(ccp(247, 391));
    m_pPassWorld->setFontColor(ccc3(178,178,178));
    m_pPassWorld->setMaxLength(50);
    m_pPassWorld->setText("您的登录密码");
    m_pPassWorld->setReturnType(kKeyboardReturnTypeDone);
    m_pPassWorld->setInputFlag(kEditBoxInputFlagPassword);
    m_pPassWorld->setTouchPriority(-1002);
    addChild(m_pPassWorld);
    
    //////
    isSelelcted = false;
    CCLabelTTF* label = CCLabelTTF::create("记住密码", "Helvetica", 25);
    label->setColor(ccc3(100, 100, 100));
    CCMenuItemLabel* pmenu=CCMenuItemLabel::create(label,this,menu_selector(QimiLoginView::remeberPassworld));
    pmenu->setPosition(ccp(0,0));

    CCMenu* menu = CCMenu::createWithItem(pmenu);
    menu->setTouchPriority(-1003);
    this->addChild(menu);
    menu->setPosition(ccp(85,308));
    
    //忘记密码
    CCLabelTTF* fogetPassTxt = CCLabelTTF::create("忘记密码？", "Helvetica", 25);
    fogetPassTxt->setColor(ccc3(100, 100, 100));
    
    
    CCMenuItemLabel* fogetPassMenuItem=CCMenuItemLabel::create(fogetPassTxt,this,menu_selector(QimiLoginView::fogetPassWorld));
    
    CCMenu* pFogetMenu = CCMenu::createWithItem(fogetPassMenuItem);
    this->addChild(pFogetMenu);
    pFogetMenu->setPosition(ccp(397,309));
    
    pFogetMenu->setTouchPriority(-1003);
    return true;
}

void QimiLoginView::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1000, true);
}

void QimiLoginView::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


void QimiLoginView::loginOnclick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    std::string userName = m_pUserName->getText();
    std::string userpass = m_pPassWorld->getText();
    
    if (!userName.empty() && !userpass.empty())
    {
        char sign[255];
        sprintf(sign, "appid=%ddo=loginemail=%smod=Userpassword=%s%s",
                QimiPlatform::shareQimiPlatform()->getQimiGameAppId(),
                userName.c_str(),
                userpass.c_str(),
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
        request->setResponseCallback(this, httpresponse_selector(QimiLoginView::loginSucceed));

        CCString* postDataStr = CCString::createWithFormat("sign=%s&appid=%d&mod=User&do=login&email=%s&password=%s",
                                                           md5tolower.c_str(),
                                                           QimiPlatform::shareQimiPlatform()->getQimiGameAppId(),
                                                           userName.c_str(),
                                                           userpass.c_str());
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

}

void QimiLoginView::loginSucceed(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response)
{
    CCNode* node = this->getChildByTag(100000);
    if (node!=NULL)
    {
        node->removeFromParentAndCleanup(true);
    }
    
    Json::Value root = GameUtils::getResponseData(response);
    if (root!=NULL && !root.isNull())
    {
        root["status"];
        int status;
        CC_GAME_JSON_ADD(root, isInt, status, "status", asInt);
        //CCLog("status%d", status);
        
        if (status == 100)
        {
            Json::Value data = root["data"];
            if (!data.isNull())
            {
                QimiUserModel* pQimiUserModel = QimiUserModel::create();
                pQimiUserModel->initData(data);
                pQimiUserModel->retain();
                QimiPlatform::shareQimiPlatform()->setQimiUserModel(pQimiUserModel);
            }
            QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "登录成功");
            
            CCInteger* obj = CCInteger::create(1);
            QimiPlatform::shareQimiPlatform()->callLoginBack(obj);
            this->removeFromParentAndCleanup(true);
        }
        else
        {
            int errCode;
            std::string msg;
            if (!root.isNull())
            {
                CC_GAME_JSON_ADD(root, isInt, errCode, "status", asInt);
                CC_GAME_JSON_ADD(root, isString, msg, "error", asString);
            }
            QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", msg);
        }
    }
}

void QimiLoginView::registerOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    QimiPlatform::shareQimiPlatform()->QimiRegister();
    backOnClick(NULL, NULL);
    //注册
}

void QimiLoginView::remeberPassworld(CCObject* obj)
{
    isSelelcted = !isSelelcted;
    m_pRememberSprite->setVisible(isSelelcted);
}

void QimiLoginView::fogetPassWorld(cocos2d::CCObject *obj)
{
    QimiPlatform::shareQimiPlatform()->openGameWeb(QIMI_FORUM);
}

void QimiLoginView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}

//////

