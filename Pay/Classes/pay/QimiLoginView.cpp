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
isSelelcted(true),
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
    
    CCNode* container = CCNode::create();
    this->addChild(container);
    container->setPosition(ccp(m_size.width/2, 1000));
    container->runAction(CCSequence::create(CCEaseBackOut::create(CCMoveTo::create(0.5f, ccp(m_size.width/2, m_size.height/2))),NULL));
    
    CCSprite* bg = CCSprite::create("bg_small_denglu.png");
    bg->setPosition(ccp(3,16));
    container->addChild(bg);
    
    CCSprite* logo = CCSprite::create("bg_small_btnlgogo.png");
    logo->setPosition(ccp(-58, 148));
    container->addChild(logo);
    
    
    CCLabelTTF* titleTxt = CCLabelTTF::create("奇米帐号登录", "Helvetica", 22);
    titleTxt->setColor(ccc3(0, 0, 0));
    titleTxt->setPosition(ccp(36, 145));
    container->addChild(titleTxt);
    
    
    
    CCControlButton* backBtn = CCControlButton::create(CCScale9Sprite::create("btn_small_close.png"));
    backBtn->setPreferredSize(CCSizeMake(32, 32));
    backBtn->setTouchPriority(-1001);
    container->addChild(backBtn);
    backBtn->setPosition(ccp(184, 158));
    backBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(QimiLoginView::backOnClick),
                                                 CCControlEventTouchUpInside);



    
    
    
    
    ////////////公共部分结束

    
    CCSprite* userBg = CCSprite::create("bg_small_btnbg.png");
    userBg->setPosition(ccp(6, 82));
    container->addChild(userBg);
    
    CCSprite* passBg = CCSprite::create("bg_small_btnbg.png");
    passBg->setPosition(ccp(6, 17));
    container->addChild(passBg);
    
    
    
    CCControlButton* m_pLoginBtn = CCControlButton::create(CCScale9Sprite::create("btn_small_denglu.png"));
    m_pLoginBtn->setPreferredSize(CCSizeMake(176, 59));
    m_pLoginBtn->setTouchPriority(-1001);
    container->addChild(m_pLoginBtn);
    m_pLoginBtn->setPosition(ccp(-86, -93));
    m_pLoginBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(QimiLoginView::loginOnclick),
                                                 CCControlEventTouchUpInside);

    
    CCControlButton* m_pRegisterBtn = CCControlButton::create(CCScale9Sprite::create("btn_small_zhuce_denglu.png"));
    m_pRegisterBtn->setPreferredSize(CCSizeMake(176, 59));
    m_pRegisterBtn->setTouchPriority(-1001);
    container->addChild(m_pRegisterBtn);
    m_pRegisterBtn->setPosition(ccp(99, -93));
    m_pRegisterBtn->addTargetWithActionForControlEvents(this,
                                                     cccontrol_selector(QimiLoginView::registerOnClick),
                                                     CCControlEventTouchUpInside);
    
    
    

    m_pNoRememberSprite = CCSprite::create("btn_jizhumima_left.png");
    m_pNoRememberSprite->setPosition(ccp(-149, -37));
    container->addChild(m_pNoRememberSprite);
    
    m_pRememberSprite = CCSprite::create("btn_jizhumima_right.png");
    m_pRememberSprite->setVisible(false);
    m_pRememberSprite->setPosition(ccp(-149, -37));
    container->addChild(m_pRememberSprite);
    
    
    CCSize editBoxSize = CCSizeMake(270, 30);
    
    m_pInputUserNameTxtBg = CCScale9Sprite::create("loginbg.png");
    m_pInputUserPassTxtBg = CCScale9Sprite::create("loginbg.png");
    
    container->addChild(m_pInputUserNameTxtBg);
    container->addChild(m_pInputUserPassTxtBg);
    
    m_pInputUserNameTxtBg->removeFromParentAndCleanup(false);
    m_pUserName = CCEditBox::create(editBoxSize, m_pInputUserNameTxtBg);
    m_pUserName->setPosition(ccp(60, 80));
    m_pUserName->setFontColor(ccc3(0,0,0));
    m_pUserName->setMaxLength(50);
    m_pUserName->setReturnType(kKeyboardReturnTypeDone);
    m_pUserName->setTouchPriority(-1002);
    m_pUserName->setText("您的电子邮箱地址");
    m_pUserName->setInputMode(kEditBoxInputModeEmailAddr);
    container->addChild(m_pUserName);
    
    m_pInputUserPassTxtBg->removeFromParentAndCleanup(false);
    m_pPassWorld = CCEditBox::create(editBoxSize, m_pInputUserPassTxtBg);
    m_pPassWorld->setPosition(ccp(60,20));
    m_pPassWorld->setFontColor(ccc3(0,0,0));
    m_pPassWorld->setMaxLength(50);
    
    m_pPassWorld->setReturnType(kKeyboardReturnTypeDone);
    m_pPassWorld->setInputFlag(kEditBoxInputFlagPassword);
    m_pPassWorld->setTouchPriority(-1002);
    container->addChild(m_pPassWorld);
    m_pPassWorld->setText("您的登录密码");
    
    std::string n = CCUserDefault::sharedUserDefault()->getStringForKey("QimiSDKUserName");
    std::string p = CCUserDefault::sharedUserDefault()->getStringForKey("QimiSDKUserPass");
    
    if(!n.empty() && !p.empty())
    {
        m_pUserName->setText(n.c_str());
        m_pPassWorld->setText(p.c_str());
    }
    
    //////
    isSelelcted = false;
    CCLabelTTF* label = CCLabelTTF::create("记住密码", "Helvetica", 18);
    label->setColor(ccc3(100, 100, 100));
    CCMenuItemLabel* pmenu=CCMenuItemLabel::create(label,this,menu_selector(QimiLoginView::remeberPassworld));
    pmenu->setPosition(ccp(0,0));

    CCMenu* menu = CCMenu::createWithItem(pmenu);
    menu->setTouchPriority(-1003);
    container->addChild(menu);
    menu->setPosition(ccp(-84,-37));
    
    //忘记密码
    CCLabelTTF* fogetPassTxt = CCLabelTTF::create("忘记密码？", "Helvetica", 18);
    fogetPassTxt->setColor(ccc3(100, 100, 100));
    
    
    CCMenuItemLabel* fogetPassMenuItem=CCMenuItemLabel::create(fogetPassTxt,this,menu_selector(QimiLoginView::fogetPassWorld));
    
    CCMenu* pFogetMenu = CCMenu::createWithItem(fogetPassMenuItem);
    container->addChild(pFogetMenu);
    pFogetMenu->setPosition(ccp(140,-37));
    pFogetMenu->setTouchPriority(-1003);
    
    
    CCLabelTTF* userNameLabel = CCLabelTTF::create("帐  号:", "Helvetica", 18);
    userNameLabel->setColor(ccc3(0, 0, 0));
    userNameLabel->setAnchorPoint(ccp(0, 0.5f));
    userNameLabel->setPosition(ccp(-151, 81));
    container->addChild(userNameLabel);
    
    CCLabelTTF* userPassLable = CCLabelTTF::create("密  码：", "Helvetica", 18);
    userPassLable->setColor(ccc3(0, 0, 0));
    userPassLable->setPosition(ccp(-151, 19));
    userPassLable->setAnchorPoint(ccp(0, 0.5f));
    container->addChild(userPassLable);
    
    remeberPassworld(NULL);
    
    return true;
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
            
            //登录成功后会保存帐号和密码。
            if (isSelelcted)
            {
                std::string userName = m_pUserName->getText();
                std::string userpass = m_pPassWorld->getText();
                
                CCUserDefault::sharedUserDefault()->setStringForKey("QimiSDKUserName", userName.c_str());
                CCUserDefault::sharedUserDefault()->setStringForKey("QimiSDKUserPass", userpass.c_str());
                CCUserDefault::sharedUserDefault()->flush();
            }
            
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
    m_pNoRememberSprite->setVisible(!isSelelcted);
}

void QimiLoginView::fogetPassWorld(cocos2d::CCObject *obj)
{
    QimiPlatform::shareQimiPlatform()->openGameWeb(QIMI_FOGET);
}

void QimiLoginView::backOnClick(cocos2d::CCNode *pSender, cocos2d::extension::CCControlEvent *pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}

//////

