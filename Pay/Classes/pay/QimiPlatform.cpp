//
//  QimiPlatform.cpp
//  Pay
//
//  Created by Ben on 6/18/13.
//
//

#include "QimiPlatform.h"
#include "QimiParamInfo.h"
#include "StageScene.h"
#include "IntObject.h"
#include "QimiMainView.h"
#include "QimiLoginView.h"
#include "QimiRegisterView.h"
#include "QimiUserModel.h"
#include "QimiMD5.h"
#include "md5c.h"
#include "RequestLoadingView.h"
#include "GameUtils.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "QimiPlatformIOS.h"

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "QimiPlatformAndroid.h"

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID


static QimiPlatform* s_pQimiPlatform = NULL;

QimiPlatform* QimiPlatform::shareQimiPlatform()
{
    if (s_pQimiPlatform == NULL)
    {
        s_pQimiPlatform = new QimiPlatform();
        s_pQimiPlatform->initialize();
    }
    return s_pQimiPlatform;
}

bool QimiPlatform::initialize()
{   
    m_appid         = 0;
    m_sId           = 0;
    m_key           = "";
    m_uId           = "";
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pQimiPlatformIOS = QimiPlatformIOS::create();
    m_pQimiPlatformIOS->retain();
    #endif

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_pQimiPlatformAndroid = QimiPlatformAndroid::create();
    m_pQimiPlatformAndroid->retain();
    #endif
    return true;
}

void QimiPlatform::setParamInfo(QimiParamInfo *pQimiParamInfo)
{
    m_appid = pQimiParamInfo->getAppID();
    m_sId   = pQimiParamInfo->getSID();
    m_key   = pQimiParamInfo->getAppKey();
}


void QimiPlatform::openGameWeb(std::string webUrl)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pQimiPlatformIOS->openWeb(webUrl);
    #endif
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_pQimiPlatformAndroid->openWeb(webUrl);
    #endif
}

void QimiPlatform::openAlertDailog(std::string title, std::string msg)
{
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_pQimiPlatformIOS->openAlert(title, msg);
    #endif
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_pQimiPlatformAndroid->openAlertDailog(title, msg);
    #endif
}

void QimiPlatform::openPayDailog(std::string uId, int sId, std::string key, int money)
{
    QimiMainView* qimiManView = QimiMainView::create();
    StageScene::shareStageScene()->m_DialogContainer->addChild(qimiManView);
    qimiManView->initView(uId, sId, key, money);
}

void QimiPlatform::QimiRegister()
{
    QimiRegisterView* pRegisterView = QimiRegisterView::create();
    StageScene::shareStageScene()->m_DialogContainer->addChild(pRegisterView);
    pRegisterView->setPosition(ccp(0, 0));
}

void QimiPlatform::QimiLogin()
{
    QimiLoginView* pLoginView = QimiLoginView::create();
    StageScene::shareStageScene()->m_DialogContainer->addChild(pLoginView);
    pLoginView->setPosition(ccp(0, 0));
}

void QimiPlatform::QimiLogin(std::string userName, std::string pass)
{
    if (!isLogined())
    {
        qimiUserLogin(userName, pass);
    }
    else
    {
        //已经登录
    }
}

void QimiPlatform::loginOut()
{
    if (m_pQimiUserModel !=NULL) {
        m_pQimiUserModel->release();
        m_pQimiUserModel = NULL;
    }
    QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "退出登录成功！");
}

void QimiPlatform::registerPayCallBack(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO call)
{
    m_PayTarget = target;
    m_payCall   = call;
}

void QimiPlatform::registerLoginCallBack(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO call)
{
    m_LoginTarget = target;
    m_LoginCall   = call;
}

void QimiPlatform::registerRegCallBack(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO call)
{
    m_RegTarget = target;
    m_RegCall = call;
}

void QimiPlatform::registerLoginAPICallback(cocos2d::CCObject* target, cocos2d::SEL_CallFuncO call)
{
    m_LoginAPITarget = target;
    m_LoginAPICall = call;
}

void QimiPlatform::callPayBack(CCObject* obj)
{
    if (m_payCall && m_PayTarget)
    {
        (m_PayTarget->* m_payCall)(obj);
    }
}

void QimiPlatform::callLoginBack(cocos2d::CCObject*obj)
{
    if (m_LoginCall && m_LoginTarget)
    {
        (m_LoginTarget->* m_LoginCall)(obj);
    }
}

void QimiPlatform::callRegBack(cocos2d::CCObject* obj)
{
    if (m_RegCall && m_RegTarget)
    {
        (m_RegTarget->* m_RegCall)(obj);
    }
}

void QimiPlatform::callLoginAPIBack(cocos2d::CCObject *obj)
{
    if (m_LoginAPITarget && m_LoginAPICall)
    {
        (m_LoginAPITarget->* m_LoginAPICall)(obj);
    }
}

/*检测是否已登录*/
bool QimiPlatform::isLogined()
{
    if (m_pQimiUserModel!=NULL && !m_pQimiUserModel->getuID().empty())
    {
        return true;
    }
    return false;
}

bool QimiPlatform::isCheckAppId()
{
    return m_appid ? true : false;
}
//检查是否获得APP ID

bool QimiPlatform::isCheckAppKey()
{
    return m_key.empty() ? false : true;
}//检查是否已获得APP KEY

void QimiPlatform::qimiUserLogin(std::string userName, std::string userpass)
{
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
        request->setResponseCallback(this, httpresponse_selector(QimiPlatform::loginSucceed));
        
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
        StageScene::shareStageScene()->m_DialogContainer->addChild(mask);
    }

}

void QimiPlatform::loginSucceed(cocos2d::extension::CCHttpClient *sender, cocos2d::extension::CCHttpResponse *response)
{
    CCNode* node = StageScene::shareStageScene()->m_DialogContainer->getChildByTag(100000);
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
            //QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "登录成功");
            
            CCInteger* obj = CCInteger::create(1);
            QimiPlatform::shareQimiPlatform()->callLoginBack(obj);
            
            //登录成功后会保存帐号和密码。
            CCInteger* pObj = CCInteger::create(1);
            callLoginAPIBack(pObj);
            //this->removeFromParentAndCleanup(true);
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
            CCInteger* pObj = CCInteger::create(0);
            callLoginAPIBack(pObj);
            
        }
    }

}


