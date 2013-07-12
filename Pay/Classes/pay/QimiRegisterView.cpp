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
    
    CCNode* container = CCNode::create();
    this->addChild(container);
    container->setTag(100000);
    container->setPosition(ccp(m_size.width/2, m_size.height/2));
    
    
    
    CCSprite* bg = CCSprite::create("bg_small_zhuce.png");
    bg->setPosition(ccp(5, 4));
    container->addChild(bg);
    
    CCSprite* logo = CCSprite::create("bg_small_btnlgogo.png");
    logo->setPosition(ccp(-67, 147));
    container->addChild(logo);
    
    
    CCLabelTTF* titleTxt = CCLabelTTF::create("奇米帐号登录", "Helvetica", 22);
    titleTxt->setColor(ccc3(0, 0, 0));
    titleTxt->setPosition(ccp(28, 145));
    container->addChild(titleTxt);
    
    
    
    CCControlButton* backBtn = CCControlButton::create(CCScale9Sprite::create("btn_small_close.png"));
    backBtn->setPreferredSize(CCSizeMake(32, 32));
    backBtn->setTouchPriority(-1001);
    container->addChild(backBtn);
    backBtn->setPosition(ccp(184, 158));
    backBtn->addTargetWithActionForControlEvents(this,
                                                 cccontrol_selector(QimiRegisterView::backOnClick),
                                                 CCControlEventTouchUpInside);
    ////////////公共部分结束

    
    CCSprite* userBg = CCSprite::create("bg_small_btnbg.png");
    userBg->setPosition(ccp(6, 82));
    container->addChild(userBg);
    
    CCSprite* passBg = CCSprite::create("bg_small_btnbg.png");
    passBg->setPosition(ccp(6, 16));
    container->addChild(passBg);
    
    CCSprite* passBg2 = CCSprite::create("bg_small_btnbg.png");
    passBg2->setPosition(ccp(6, -49));
    container->addChild(passBg2);
    
    
    CCControlButton* m_pRegisterBtn = CCControlButton::create(CCScale9Sprite::create("btn_small_zhuce.png"));
    m_pRegisterBtn->setPreferredSize(CCSizeMake(361, 59));
    m_pRegisterBtn->setTouchPriority(-1000);
    container->addChild(m_pRegisterBtn);
    m_pRegisterBtn->setPosition(ccp(5, -122));
    m_pRegisterBtn->addTargetWithActionForControlEvents(this,
                                                        cccontrol_selector(QimiRegisterView::registerOnClick),
                                                        CCControlEventTouchUpInside);
    
    
    CCSize editBoxSize = CCSizeMake(270, 30);
    
    m_pInputUserNameTxtBg = CCScale9Sprite::create("loginbg.png");
    m_pInputUserPassTxtBg = CCScale9Sprite::create("loginbg.png");
    m_pInputUserVerifyPassTxtBg = CCScale9Sprite::create("loginbg.png");
    container->addChild(m_pInputUserNameTxtBg);
    container->addChild(m_pInputUserPassTxtBg);
    container->addChild(m_pInputUserVerifyPassTxtBg);
    
    m_pInputUserNameTxtBg->removeFromParentAndCleanup(false);
    m_pEditUserName = CCEditBox::create(editBoxSize, m_pInputUserNameTxtBg);
    m_pEditUserName->setPosition(ccp(70, 82));
    m_pEditUserName->setFontColor(ccc3(0,0,0));
    m_pEditUserName->setMaxLength(60);
    m_pEditUserName->setReturnType(kKeyboardReturnTypeDone);
    m_pEditUserName->setInputMode(kEditBoxInputModeEmailAddr);
    m_pEditUserName->setTouchPriority(-1000);
    m_pEditUserName->setText("用户名");
    m_pEditUserName->setTag(101);
    m_pEditUserName->setDelegate(this);
    container->addChild(m_pEditUserName);
    
    m_pInputUserPassTxtBg->removeFromParentAndCleanup(false);
    m_pEditUserPass = CCEditBox::create(editBoxSize, m_pInputUserPassTxtBg);
    m_pEditUserPass->setPosition(ccp(70, 16));
    m_pEditUserPass->setFontColor(ccc3(0,0,0));
    m_pEditUserPass->setMaxLength(50);
    m_pEditUserPass->setReturnType(kKeyboardReturnTypeDone);
    m_pEditUserPass->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditUserPass->setTouchPriority(-1000);
    m_pEditUserPass->setText("用户密码");
    m_pEditUserPass->setTag(102);
    m_pEditUserPass->setDelegate(this);
    container->addChild(m_pEditUserPass);
    
    m_pInputUserVerifyPassTxtBg->removeFromParentAndCleanup(false);
    m_pEditVerifyPass = CCEditBox::create(editBoxSize, m_pInputUserVerifyPassTxtBg);
    m_pEditVerifyPass->setPosition(ccp(70, -49));
    m_pEditVerifyPass->setFontColor(ccc3(0,0,0));
    m_pEditVerifyPass->setMaxLength(50);
    m_pEditVerifyPass->setReturnType(kKeyboardReturnTypeDone);
    m_pEditVerifyPass->setInputFlag(kEditBoxInputFlagPassword);
    m_pEditVerifyPass->setTouchPriority(-1000);
    m_pEditVerifyPass->setText("确认密码");
    m_pEditVerifyPass->setTag(103);
    m_pEditVerifyPass->setDelegate(this);
    container->addChild(m_pEditVerifyPass);
    //////
    
    CCLabelTTF* userNameLabel = CCLabelTTF::create("帐    号:", "Helvetica", 18);
    userNameLabel->setColor(ccc3(0, 0, 0));
    userNameLabel->setAnchorPoint(ccp(1, 0.5f));
    userNameLabel->setPosition(ccp(-80, 82));
    container->addChild(userNameLabel);
    
    CCLabelTTF* userPassLable = CCLabelTTF::create("密    码:", "Helvetica", 18);
    userPassLable->setColor(ccc3(0, 0, 0));
    userPassLable->setPosition(ccp(-80, 16));
    userPassLable->setAnchorPoint(ccp(1, 0.5f));
    container->addChild(userPassLable);
    
    CCLabelTTF* vUserPassLable = CCLabelTTF::create("确认密码:", "Helvetica", 18);
    vUserPassLable->setColor(ccc3(0, 0, 0));
    vUserPassLable->setPosition(ccp(-80, -49));
    vUserPassLable->setAnchorPoint(ccp(1, 0.5f));
    container->addChild(vUserPassLable);
    
   
    
    
    container->setVisible(false);
    CCFiniteTimeAction* actionMoveDone = cocos2d::CCCallFunc::create(this, callfunc_selector(QimiRegisterView::showWin));
    container->runAction(CCSequence::create(CCDelayTime::create(0.01),actionMoveDone,CCMoveTo::create(0.01f, ccp(m_size.width/2, 1000)),CCEaseBackOut::create(CCMoveTo::create(0.5f, ccp(m_size.width/2, m_size.height/2))),NULL));
    return true;
}

void QimiRegisterView::showWin()
{
    this->getChildByTag(100000)->setVisible(true);;
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
            mask->setTag(1000000);
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
    CCNode* node = this->getChildByTag(1000000);
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
            GameUtils::showNewTip("注册成功并且已经登录！", StageScene::shareStageScene()->m_DialogContainer, ccp(240,400), 1.0, true);
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

void QimiRegisterView::editBoxEditingDidBegin(CCEditBox *editBox)
{
    std::string str = editBox->getText();
    int index = editBox->getTag();
    switch (index) {
        case 101:
            if (!strcmp(str.c_str(), "用户名"))
            {
                editBox->setText("");
            }
            break;
        case 102:
            if (!strcmp(str.c_str(), "用户密码"))
            {
                editBox->setText("");
            }
            
            break;
        case 103:
            if (!strcmp(str.c_str(), "确认密码"))
            {
                editBox->setText("");
            }
            break;
            
        default:
            break;
    }
    
    
}

void QimiRegisterView::editBoxEditingDidEnd(CCEditBox *editBox)
{
    
}

void QimiRegisterView::editBoxTextChanged(CCEditBox *editBox,const std::string &text)
{
    
}

void QimiRegisterView::editBoxReturn(CCEditBox *editBox)
{
    
}











