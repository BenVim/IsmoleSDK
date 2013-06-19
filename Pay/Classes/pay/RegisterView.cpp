//
//  RegisterView.cpp
//  Pay
//
//  Created by Ben on 5/13/13.
//
//

#include "RegisterView.h"
#include "StageScene.h"
#include "ProxyFilterManager.h"
#include "ProxyLoadingFilter.h"
#include "Proxy.h"


USING_NS_CC;
USING_NS_CC_EXT;

RegisterView::RegisterView():
m_pBackBtn(NULL),
m_pRegisterBtn(NULL),
m_pCCEditBoxUserCCNode(NULL),
m_pCCEditBoxPassCCNode(NULL),
m_pCCEditBoxVerifyPassCCNode(NULL),
m_pInputUserNameTxtBg(NULL),
m_pInputUserPassTxtBg(NULL),
m_pInputUserVerifyPassTxtBg(NULL)
{
    
}

RegisterView::~RegisterView()
{
    CC_SAFE_RELEASE(m_pBackBtn);
    CC_SAFE_RELEASE(m_pRegisterBtn);
    CC_SAFE_RELEASE(m_pCCEditBoxUserCCNode);
    CC_SAFE_RELEASE(m_pCCEditBoxPassCCNode);
    CC_SAFE_RELEASE(m_pCCEditBoxVerifyPassCCNode);
    CC_SAFE_RELEASE(m_pInputUserNameTxtBg);
    CC_SAFE_RELEASE(m_pInputUserPassTxtBg);
    CC_SAFE_RELEASE(m_pInputUserVerifyPassTxtBg);
}

SEL_MenuHandler RegisterView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
	return NULL;
}

SEL_CCControlHandler RegisterView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName){
    
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onClickRegisterHandler:", RegisterView::registerOnClick);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "backOnClickHandler:", RegisterView::onBack);

	return NULL;
}

bool RegisterView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "backBtn:", cocos2d::extension::CCControlButton*, m_pBackBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "RegisterBtn:", cocos2d::extension::CCControlButton*, m_pRegisterBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "CCEditBoxUserCCNode:", cocos2d::CCNode*, m_pCCEditBoxUserCCNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "CCEditBoxPassCCNode:", cocos2d::CCNode*, m_pCCEditBoxPassCCNode);//CCEditBoxPassCCNode:
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "CCEditBoxVerifyPassCCNode:", cocos2d::CCNode*, m_pCCEditBoxVerifyPassCCNode);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "InputUserNameTxtBg:", cocos2d::extension::CCScale9Sprite*, m_pInputUserNameTxtBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "InputUserPassTxtBg:", cocos2d::extension::CCScale9Sprite*, m_pInputUserPassTxtBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "InputUserVerifyPassTxtBg:", cocos2d::extension::CCScale9Sprite*, m_pInputUserVerifyPassTxtBg);
	return false;
}

void RegisterView::onNodeLoaded(cocos2d::CCNode * pNode,  CCNodeLoader * pNodeLoader) {
	initView();
}

void RegisterView::initView()
{
    CCSize editBoxSize = CCSizeMake(300, 50);
    
    m_pInputUserNameTxtBg->removeFromParentAndCleanup(false);
    m_pEditUserName = CCEditBox::create(editBoxSize, m_pInputUserNameTxtBg);
    m_pEditUserName->setPosition(m_pCCEditBoxUserCCNode->getPosition());
    m_pEditUserName->setFontColor(ccc3(175,175,175));
    m_pEditUserName->setMaxLength(50);
    m_pEditUserName->setReturnType(kKeyboardReturnTypeDone);
    m_pEditUserName->setTouchPriority(-130);
    m_pEditUserName->setText("用户名");
    addChild(m_pEditUserName);
    
    m_pInputUserPassTxtBg->removeFromParentAndCleanup(false);
    m_pEditUserPass = CCEditBox::create(editBoxSize, m_pInputUserPassTxtBg);
    m_pEditUserPass->setPosition(m_pCCEditBoxPassCCNode->getPosition());
    m_pEditUserPass->setFontColor(ccc3(175,175,175));
    m_pEditUserPass->setMaxLength(50);
    m_pEditUserPass->setReturnType(kKeyboardReturnTypeDone);
    m_pEditUserPass->setTouchPriority(-130);
    m_pEditUserPass->setText("用户密码");
    addChild(m_pEditUserPass);
    
    m_pInputUserVerifyPassTxtBg->removeFromParentAndCleanup(false);
    m_pEditVerifyPass = CCEditBox::create(editBoxSize, m_pInputUserVerifyPassTxtBg);
    m_pEditVerifyPass->setPosition(m_pCCEditBoxVerifyPassCCNode->getPosition());
    m_pEditVerifyPass->setFontColor(ccc3(175,175,175));
    m_pEditVerifyPass->setMaxLength(50);
    m_pEditVerifyPass->setReturnType(kKeyboardReturnTypeDone);
    m_pEditVerifyPass->setTouchPriority(-130);
    m_pEditVerifyPass->setText("确认密码");
    addChild(m_pEditVerifyPass);
}

void RegisterView::registerOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    std::string userName = m_pEditUserName->getText();
    std::string userPass = m_pEditUserPass->getText();
    std::string userVerifyPass = m_pEditVerifyPass->getText();
    
    if (!userName.empty() && !userPass.empty() && !userVerifyPass.empty())
    {
        std::string userEmail = "";//m_pUserName->getText();
        std::string userpass = "";//m_pPassWorld->getText();

        if (userPass == userVerifyPass)
        {
            std::string url = std::string("http://www.qimi.com/platform/addOrder.php");
            Json::Value homeData;
            homeData["sign"] = "";
            homeData["appid"] = "";
            homeData["mod"] = "User";
            homeData["do"] = "reg";
            homeData["email"] = userEmail;
            homeData["password"] = userPass;
            homeData["name"] = "";
            homeData["sex"] = "";
            homeData["birthday"] = "";
            
            SingleProxy *proxy = SingleProxy::create(homeData);
            proxy->addTargetWithActionFromProxyEvents(this,
                                                      proxy_selector(RegisterView::registerSucceed),
                                                      ProxyEventResponseSucceed);
            proxy->addTargetWithActionFromProxyEvents(this,
                                                      proxy_selector(RegisterView::registerloginFiled),
                                                      ProxyEventResponseError);
            proxy->load(url);
        }
        else
        {
            CCLog("两次密码不一致！");
        }
    }
    else
    {
        CCLog("用户名和密码不能为空！");
    }
    
}

void RegisterView::onBack(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent)
{
    LoginView* pLoginView = GameCCBLoader::sharedLoader()->createCCBNode<LoginView>("LoginView.ccbi");
    StageScene::shareStageScene()->m_DialogContainer->addChild(pLoginView);
    this->removeFromParentAndCleanup(true);
}

void RegisterView::registerSucceed(Proxy* pro, ProxyEvent proxyEvent)
{
    
}

void RegisterView::registerloginFiled(Proxy* pro, ProxyEvent proxyEvent)
{
    
}










