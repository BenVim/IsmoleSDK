//
//  LoginView.h
//  Pay
//
//  Created by Ben on 5/13/13.
//
//

#ifndef __Pay__LoginView__
#define __Pay__LoginView__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SingleProxy.h"
#include "json.h"

USING_NS_CC_EXT;

class LoginView :public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCNodeLoaderListener{
public:
    LoginView();
    ~LoginView();
    
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LoginView, create);
    void initView();
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
    virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);
    
    void loginOnclick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void registerOnClick(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
    void onBack(cocos2d::CCNode* pSender, cocos2d::extension::CCControlEvent* pCCControlEvent);
private:
    cocos2d::extension::CCControlButton* m_pBackBtn;
    cocos2d::extension::CCControlButton* m_pLoginBtn;
    cocos2d::extension::CCControlButton* m_pRegisterBtn;

    cocos2d::CCNode* m_pCCEditBoxUserCCNode;
    cocos2d::CCNode* m_pCCEditBoxPassCCNode;
    cocos2d::CCNode* m_pFogetMenuCCNode;//忘记密码的容器；
    cocos2d::CCNode* m_pRememberMenuCCNode;
    
    cocos2d::CCSprite* m_pRememberSprite;
    cocos2d::CCSprite* m_pNoRememberSprite;

    cocos2d::extension::CCScale9Sprite* m_pInputUserNameTxtBg;
    cocos2d::extension::CCScale9Sprite* m_pInputUserPassTxtBg;
    
    cocos2d::extension::CCEditBox* m_pUserName;
    cocos2d::extension::CCEditBox* m_pPassWorld;
    
    bool isSelelcted;
private:
    
    void fogetPassWorld(CCObject* obj);
    void remeberPassworld(CCObject* obj);
    void loginSucceed(cocos2d::CCNode *sender, void *data);
    
};

class LoginViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LoginViewLoader, loader);
    
protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LoginView);
};


#endif /* defined(__Pay__LoginView__) */
