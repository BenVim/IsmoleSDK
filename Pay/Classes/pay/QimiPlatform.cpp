//
//  QimiPlatform.cpp
//  Pay
//
//  Created by Ben on 6/18/13.
//
//

#include "QimiPlatform.h"
#include "QimiPlatformIOS.h"
#include "QimiPlatformAndroid.h"
#include "QimiParamInfo.h"
#include "GameCCBLoader.h"
#include "StageScene.h"

#include "md5c.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)


#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


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
    m_appid = 0;
    m_sId   = 0;
    m_key   = "";
    m_uId   = 0;
    
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

void QimiPlatform::openPayDailog(int uId, int sId, std::string key, int money)
{
    PayView* pPayView = GameCCBLoader::sharedLoader()->createCCBNode<PayView>("PayView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pPayView);
    pPayView->setPosition(ccp(0, 0));
    pPayView->initView(uId, sId, key, money);
}

void QimiPlatform::QimiRegister()
{
    RegisterView* pRegisterView = GameCCBLoader::sharedLoader()->createCCBNode<RegisterView>("RegisterView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pRegisterView);
    pRegisterView->setPosition(ccp(0, 0));
}

void QimiPlatform::QimiLogin()
{
    LoginView* pLoginView = GameCCBLoader::sharedLoader()->createCCBNode<LoginView>("LoginView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pLoginView);
    pLoginView->setPosition(ccp(0, 0));
}

void QimiPlatform::loginOut()
{
    
}

/*检测是否已登录*/
bool QimiPlatform::isLogined()
{
    return m_uId ? true : false;
}

bool QimiPlatform::isCheckAppId()
{
    return m_appid ? true : false;
}//检查是否获得APP ID

bool QimiPlatform::isCheckAppKey()
{
    return m_key.empty() ? false : true;
}//检查是否已获得APP KEY



