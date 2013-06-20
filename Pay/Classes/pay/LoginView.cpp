//
//  LoginView.cpp
//  Pay
//
//  Created by Ben on 5/13/13.
//
//

#include "LoginView.h"
#include "StageScene.h"
#include "GameCCBLoader.h"
#include "ProxyFilterManager.h"
#include "ProxyLoadingFilter.h"
#include "Proxy.h"
#include "ObjCalls.h"
#include "QimiPlatform.h"
#include "QimiUserModel.h"

USING_NS_CC;
USING_NS_CC_EXT;

LoginView::LoginView():
m_pBackBtn(NULL),
m_pLoginBtn(NULL),
m_pRegisterBtn(NULL),
m_pCCEditBoxUserCCNode(NULL),
m_pCCEditBoxPassCCNode(NULL),
m_pFogetMenuCCNode(NULL),
m_pRememberSprite(NULL),
m_pNoRememberSprite(NULL),
m_pInputUserNameTxtBg(NULL),
m_pInputUserPassTxtBg(NULL),
m_pRememberMenuCCNode(NULL)
{
    
}

LoginView::~LoginView()
{
    CC_SAFE_RELEASE(m_pBackBtn);
    CC_SAFE_RELEASE(m_pLoginBtn);
    CC_SAFE_RELEASE(m_pRegisterBtn);
    CC_SAFE_RELEASE(m_pCCEditBoxUserCCNode);
    CC_SAFE_RELEASE(m_pCCEditBoxPassCCNode);
    CC_SAFE_RELEASE(m_pFogetMenuCCNode);
    CC_SAFE_RELEASE(m_pRememberSprite);
    CC_SAFE_RELEASE(m_pNoRememberSprite);
    CC_SAFE_RELEASE(m_pInputUserNameTxtBg);
    CC_SAFE_RELEASE(m_pInputUserPassTxtBg);
    CC_SAFE_RELEASE(m_pRememberMenuCCNode);
}

SEL_MenuHandler LoginView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    
	return NULL;
}

SEL_CCControlHandler LoginView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "backOnClickHandler:", LoginView::onBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "loginOnClickHandler:", LoginView::loginOnclick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "registerOnClickhandler:", LoginView::registerOnClick);
	return NULL;
}

bool LoginView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "backBtn:", cocos2d::extension::CCControlButton*, this->m_pBackBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "LoginBtn:", cocos2d::extension::CCControlButton *, this->m_pLoginBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "RegisterBtn:", cocos2d::extension::CCControlButton *, this->m_pRegisterBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "CCEditBoxUserCCNode:", cocos2d::CCNode *, this->m_pCCEditBoxUserCCNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "CCEditBoxPassCCNode:", cocos2d::CCNode *, this->m_pCCEditBoxPassCCNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "FogetMenuCCNode:", cocos2d::CCNode *, this->m_pFogetMenuCCNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "RememberSprite:", cocos2d::CCSprite *, this->m_pRememberSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "NoRememberSprite:", cocos2d::CCSprite *, this->m_pNoRememberSprite);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "InputUserNameTxtBg:", cocos2d::extension::CCScale9Sprite*, this->m_pInputUserNameTxtBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "InputUserPassTxtBg:", cocos2d::extension::CCScale9Sprite*, this->m_pInputUserPassTxtBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "RememberMenuCCNode:", cocos2d::CCNode*, m_pRememberMenuCCNode);
	return false;
}

void LoginView::onNodeLoaded(cocos2d::CCNode * pNode,  CCNodeLoader * pNodeLoader)
{
    m_pBackBtn->setDefaultTouchPriority(-130);
    m_pLoginBtn->setDefaultTouchPriority(-130);
    m_pRegisterBtn->setDefaultTouchPriority(-130);
    
    m_pRememberSprite->setVisible(false);
    CCSize editBoxSize = CCSizeMake(300, 50);
    
    m_pInputUserNameTxtBg->removeFromParentAndCleanup(false);
    m_pUserName = CCEditBox::create(editBoxSize, m_pInputUserNameTxtBg);
    m_pUserName->setPosition(m_pCCEditBoxUserCCNode->getPosition());
    m_pUserName->setFontColor(ccc3(178,178,178));
    m_pUserName->setMaxLength(50);
    m_pUserName->setReturnType(kKeyboardReturnTypeDone);
    m_pUserName->setTouchPriority(-130);
    m_pUserName->setText("您的电子邮箱地址");
    m_pUserName->setInputMode(kEditBoxInputModeEmailAddr);
    addChild(m_pUserName);
    
    m_pInputUserPassTxtBg->removeFromParentAndCleanup(false);
    m_pPassWorld = CCEditBox::create(editBoxSize, m_pInputUserPassTxtBg);
    m_pPassWorld->setPosition(m_pCCEditBoxPassCCNode->getPosition());
    m_pPassWorld->setFontColor(ccc3(178,178,178));
    m_pPassWorld->setMaxLength(50);
    m_pPassWorld->setText("您的登录密码");
    m_pPassWorld->setReturnType(kKeyboardReturnTypeDone);
    m_pPassWorld->setInputFlag(kEditBoxInputFlagPassword);
    m_pPassWorld->setTouchPriority(-130);
    addChild(m_pPassWorld);
    
    //////
    isSelelcted = false;
    CCLabelTTF* label = CCLabelTTF::create("记住密码", "Helvetica", 25);
    label->setColor(ccc3(100, 100, 100));
    CCMenuItemLabel* pmenu=CCMenuItemLabel::create(label,this,menu_selector(LoginView::remeberPassworld));
    pmenu->setPosition(ccp(0,0));
    CCMenu* menu = CCMenu::createWithItem(pmenu);
    m_pRememberMenuCCNode->addChild(menu);
    menu->setPosition(ccp(0,0));
    
    //忘记密码
    CCLabelTTF* fogetPassTxt = CCLabelTTF::create("忘记密码？", "Helvetica", 25);
    fogetPassTxt->setColor(ccc3(100, 100, 100));
    
    CCMenuItemLabel* fogetPassMenuItem=CCMenuItemLabel::create(fogetPassTxt,this,menu_selector(LoginView::fogetPassWorld));
    fogetPassMenuItem->setPosition(ccp(0,0));
    CCMenu* pFogetMenu = CCMenu::createWithItem(fogetPassMenuItem);
    m_pFogetMenuCCNode->addChild(pFogetMenu);
    pFogetMenu->setPosition(ccp(0,0));
    
}

void LoginView::initView()
{
   
}

void LoginView::registerOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    RegisterView* pRegisterView = GameCCBLoader::sharedLoader()->createCCBNode<RegisterView>("RegisterView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pRegisterView);
    this->removeFromParentAndCleanup(true);
}

void LoginView::loginOnclick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    std::string userName = m_pUserName->getText();
    std::string userpass = m_pPassWorld->getText();
    
    if (!userName.empty() && !userpass.empty())
    {
        char sign[255];
        sprintf(sign, "appid=%ddo=loginemail=%smode=Userpassword=%s", QimiPlatform::shareQimiPlatform()->getQimiGameAppId(), userName.c_str(),userpass.c_str());
        
        //登录
        std::string url = std::string("http://api.qimi.com/api.php");
        Json::Value homeData;
        homeData["sign"] = sign;
        homeData["appid"] = QimiPlatform::shareQimiPlatform()->getQimiGameAppId();
        homeData["mode"] = "User";
        homeData["do"] = "login";
        homeData["email"] = userName; //还需要验证邮箱地址
        homeData["password"]= userpass;
        
        SingleProxy *proxy = SingleProxy::create(homeData);
        proxy->addTargetWithActionFromProxyEvents(this,
                                                  proxy_selector(LoginView::loginSucceed),
                                                  ProxyEventResponseSucceed);
        proxy->addTargetWithActionFromProxyEvents(this,
                                                  proxy_selector(LoginView::loginFiled),
                                                  ProxyEventResponseError);
        proxy->load(url);
        
    }
}

void LoginView::remeberPassworld(cocos2d::CCObject *obj)
{
    isSelelcted = !isSelelcted;
    m_pRememberSprite->setVisible(isSelelcted);
}

void LoginView::fogetPassWorld(cocos2d::CCObject *obj)
{
    QimiPlatform::shareQimiPlatform()->openGameWeb("http://www.qimi.com/index.php?mod=User&do=backPwd");
}


void LoginView::onBack(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    this->removeFromParentAndCleanup(true);
}

void LoginView::loginSucceed(Proxy* pro, ProxyEvent proxyEvent)
{
    //登录成功
    Json::Value root = pro->getResponseData();
    if (!root.isNull())
    {
        QimiUserModel* pQimiUserModel = QimiUserModel::create();
        pQimiUserModel->initData(root["data"]);
        pQimiUserModel->retain();
        QimiPlatform::shareQimiPlatform()->setQimiUserModel(pQimiUserModel);
    }
    QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", "登录成功");
    this->removeFromParentAndCleanup(true);
}

void LoginView::loginFiled(Proxy* pro, ProxyEvent proxyEvent)
{
    Json::Value root = pro->getResponseData();
    int errCode;
    std::string msg;
    if (!root.isNull())
    {
        CC_GAME_JSON_ADD(root, isInt, errCode, "status", asInt);
        CC_GAME_JSON_ADD(root, isString, msg, "error", asString);
    }
    
    QimiPlatform::shareQimiPlatform()->openAlertDailog("系统提示", msg);
}








