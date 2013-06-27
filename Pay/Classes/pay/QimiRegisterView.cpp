//
//  QimiRegisterView.cpp
//  Pay
//
//  Created by Ben on 6/25/13.
//
//

#include "QimiRegisterView.h"

#include "GameUtils.h"
#include "Qimi.h"
#include "QimiUserModel.h"
#include "QimiPlatform.h"
#include "QimiMD5.h"
#include "StageScene.h"
#include "UIMaskLayerView.h"
#include "RequestLoadingView.h"

QimiRegisterView::QimiRegisterView():isSelelcted(NULL)
{
    
}

QimiRegisterView::~QimiRegisterView()
{
    
}

bool QimiRegisterView::init()
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
                                                 cccontrol_selector(QimiRegisterView::backOnClick),
                                                 CCControlEventTouchUpInside);
    
    
    CCControlButton* helpBtn = CCControlButton::create(CCScale9Sprite::create("btn_bangzhu.png"));
    helpBtn->setPreferredSize(CCSizeMake(93, 51));
    helpBtn->setTouchPriority(-1000);
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
    userBg->setPosition(ccp(242, 472));
    this->addChild(userBg);
    
    CCSprite* passBg = CCSprite::create("bg_zhuce_mima.png");
    passBg->setPosition(ccp(242, 385));
    this->addChild(passBg);
    
    CCSprite* passBg2 = CCSprite::create("bg_mima.png");
    passBg2->setPosition(ccp(242, 300));
    this->addChild(passBg2);
    
    
    CCControlButton* m_pRegisterBtn = CCControlButton::create(CCScale9Sprite::create("btn_zhuce.png"));
    m_pRegisterBtn->setPreferredSize(CCSizeMake(418, 75));
    m_pRegisterBtn->setTouchPriority(-1000);
    this->addChild(m_pRegisterBtn);
    m_pRegisterBtn->setPosition(ccp(240, 200));
    m_pRegisterBtn->addTargetWithActionForControlEvents(this,
                                                        cccontrol_selector(QimiRegisterView::registerOnClick),
                                                        CCControlEventTouchUpInside);
    
    
    CCSize editBoxSize = CCSizeMake(300, 50);
    
    m_pInputUserNameTxtBg = CCScale9Sprite::create("loginbg.png");
    m_pInputUserPassTxtBg = CCScale9Sprite::create("loginbg.png");
    m_pInputUserVerifyPassTxtBg = CCScale9Sprite::create("loginbg.png");
    this->addChild(m_pInputUserNameTxtBg);
    this->addChild(m_pInputUserPassTxtBg);
    this->addChild(m_pInputUserVerifyPassTxtBg);
    
    m_pInputUserNameTxtBg->removeFromParentAndCleanup(false);
    m_pEditUserName = CCEditBox::create(editBoxSize, m_pInputUserNameTxtBg);
    m_pEditUserName->setPosition(ccp(247, 472));
    m_pEditUserName->setFontColor(ccc3(175,175,175));
    m_pEditUserName->setMaxLength(60);
    m_pEditUserName->setReturnType(kKeyboardReturnTypeDone);
    m_pEditUserName->setInputMode(kEditBoxInputModeEmailAddr);
    m_pEditUserName->setTouchPriority(-1000);
    m_pEditUserName->setText("用户名");
    addChild(m_pEditUserName);
    
    m_pInputUserPassTxtBg->removeFromParentAndCleanup(false);
    m_pEditUserPass = CCEditBox::create(editBoxSize, m_pInputUserPassTxtBg);
    m_pEditUserPass->setPosition(ccp(247, 388));
    m_pEditUserPass->setFontColor(ccc3(175,175,175));
    m_pEditUserPass->setMaxLength(50);
    m_pEditUserPass->setReturnType(kKeyboardReturnTypeDone);
    m_pEditUserPass->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditUserPass->setTouchPriority(-1000);
    m_pEditUserPass->setText("用户密码");
    addChild(m_pEditUserPass);
    
    m_pInputUserVerifyPassTxtBg->removeFromParentAndCleanup(false);
    m_pEditVerifyPass = CCEditBox::create(editBoxSize, m_pInputUserVerifyPassTxtBg);
    m_pEditVerifyPass->setPosition(ccp(247, 306));
    m_pEditVerifyPass->setFontColor(ccc3(175,175,175));
    m_pEditVerifyPass->setMaxLength(50);
    m_pEditVerifyPass->setReturnType(kKeyboardReturnTypeDone);
    m_pEditVerifyPass->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditVerifyPass->setTouchPriority(-1000);
    m_pEditVerifyPass->setText("确认密码");
    addChild(m_pEditVerifyPass);
    //////
    
    return true;
}

void QimiRegisterView::registerOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    std::string userName = m_pEditUserName->getText();
    std::string userPass = m_pEditUserPass->getText();
    std::string userVerifyPass = m_pEditVerifyPass->getText();
    time_t t;
    time(&t);
    char tchar[255];
    sprintf(tchar, "%ld%d", t, int(GameUtils::getRandom(1, 1000)));
    //CCLog("tchar%s", tchar);
    
    std::string name = tchar;
    if (!userName.empty() && !userPass.empty() && !userVerifyPass.empty())
    {
        if (userPass == userVerifyPass)
        {
            std::string url = std::string(QIMI_API);
            char sign[255];
            sprintf(sign, "appid=%dbirthday=2000-10-10do=regemail=%smod=Username=%spassword=%ssex=1%s",
                    QimiPlatform::shareQimiPlatform()->getQimiGameAppId(),
                    userName.c_str(),
                    name.c_str(),
                    userPass.c_str(),
                    QimiPlatform::shareQimiPlatform()->getQimiGameKey().c_str());
            
            QimiMD5 md5;
            md5.update(sign);
            //CCLog("md5str==%s",sign);
            std::string md5tolower = md5.toString();
            
            CCHttpRequest* request = new CCHttpRequest();
            request->setUrl(url.c_str());
            request->setRequestType(CCHttpRequest::kHttpPost);
            request->setResponseCallback(this, httpresponse_selector(QimiRegisterView::registerSucceed));
            
            CCString* postDataStr = CCString::createWithFormat("sign=%s&appid=%d&mod=User&do=reg&email=%s&password=%s&name=%s&sex=1&birthday=2000-10-10",
                                                               md5tolower.c_str(),
                                                               QimiPlatform::shareQimiPlatform()->getQimiGameAppId(),
                                                               userName.c_str(),
                                                               userPass.c_str(),
                                                               name.c_str());
            const char* postData = postDataStr->getCString();
            //CCLog("postData==%s", postData);
            request->setRequestData(postData, strlen(postData));
            request->setTag("POST test1");
            CCHttpClient::getInstance()->send(request);
            request->release();
            
            RequestLoadingView* mask = RequestLoadingView::create();
            mask->setTag(100000);
            this->addChild(mask);
        }
        else
        {
            //CCLog("两次密码不一致！");
            QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "两次输入的密码不一致！");
        }
    }
    else
    {   
        //CCLog("用户名和密码不能为空！");
        QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "用户名或密码不能为空！");
    }
}

void QimiRegisterView::backOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}

void QimiRegisterView::registerSucceed(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response)
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
        CCLog("status%d", status);
        
        if (status == 100)
        {
            Json::Value data = root["data"];
            std::string userId;
            if (!data.isNull())
            {
                QimiUserModel* pQimiUserModel = QimiUserModel::create();
                pQimiUserModel->initData(data);
                pQimiUserModel->retain();
                QimiPlatform::shareQimiPlatform()->setQimiUserModel(pQimiUserModel);
                userId = pQimiUserModel->getuID();
            }
            //QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "注册成功");
            
            
            CCInteger* obj = CCInteger::create(1);
            QimiPlatform::shareQimiPlatform()->callRegBack(obj);
            
            char msg[255];
            printf(msg, "%s 注册成功并且已经登录！", userId.c_str());
            GameUtils::showNewTip(msg, StageScene::shareStageScene()->m_DialogContainer, ccp(240,400), 1.0, true);
            
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






